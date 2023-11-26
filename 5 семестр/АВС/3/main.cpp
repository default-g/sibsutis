#include <ios>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include <cmath>


typedef unsigned long long ull;
typedef std::vector<std::pair<ull,ull> > time_measures;


std::string get_command_line_argument(std::string flag, char* argv[]) {
    int i = 0;
    while(argv[i]) {
        if (std::string(flag) == std::string(argv[i])) {
            return std::string(argv[i + 1]);
        }
        i++;
    }
    return "";
}


std::chrono::steady_clock::time_point get_time() {
    return std::chrono::steady_clock::now();
}


ull calculate_time(std::chrono::steady_clock::time_point begin, std::chrono::steady_clock::time_point end) {
    return std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count();
}

ull calculate_size(std::string size_from_command_line_argument) {
    ull result_calculated_size = stoull(size_from_command_line_argument);
    if (size_from_command_line_argument.find("Mb")) {
        result_calculated_size *= 1024 * 1024;
    } else if (size_from_command_line_argument.find("Kb")) {
        result_calculated_size *= 1024;
    }
    return result_calculated_size;
}


ull calculate_bandwidth(ull block_size, long double average_time) {
    return (block_size / average_time);
}


long double calculate_average(std::vector<ull> values) {
    ull sum = 0;
    for (auto value: values) {
        sum += value;
    } 
    return (long double)sum / (long double)values.size();
}


void calculate_and_write_statistic_into_file(time_measures test_results, std::string mode, ull block_size, ull launch_count) {
    std::vector<ull> write_times;
    std::vector<ull> read_times;

    for(auto result : test_results) {
        write_times.push_back(result.first);
        read_times.push_back(result.second);
    }

    auto average_write_time = calculate_average(write_times);
    auto average_read_time = calculate_average(read_times);

    auto write_bandwidth = calculate_bandwidth(block_size, average_write_time);
    auto read_bandwidth = calculate_bandwidth(block_size, average_read_time);

    ull dispersion = 0;
    for (ull i = 0; i < write_times.size(); i++) {
        dispersion += pow(write_times[i] - average_write_time, 2);
    }
    auto abs_error_write = sqrt(dispersion / write_times.size());
    auto rel_error_write = (abs_error_write / average_write_time) * 100;

    dispersion = 0;
    for (ull i = 0; i < read_times.size(); i++) {
        dispersion += pow(read_times[i] - average_read_time, 2);
    }
    auto abs_error_read = sqrt(dispersion / read_times.size());
    auto rel_error_read = (abs_error_read / average_read_time) * 100;


    std::string result_string = "";
    result_string += mode + ";"; // MEMORY TYPE
    result_string += std::to_string(block_size) + ";"; //BLOCK_SIZE
    result_string += "char;";   //ELEMENT_TYPE
    result_string += std::to_string(block_size) + ";"; //BUFFER_SIZE
    result_string += std::to_string(launch_count) + ";"; // LAUNCH_NUM
    result_string += "chrono;"; // TIMER
    result_string += std::to_string(write_times[launch_count - 1]) + ";"; //WRITE_TIME
    result_string += std::to_string(average_write_time) + ";"; // AverageWriteTIme
    result_string += std::to_string(write_bandwidth) + ";"; // WriteBandWidth
    result_string += std::to_string(abs_error_write) + ";"; // AbsError
    result_string += std::to_string(rel_error_write) + ";"; // RelError
    result_string += std::to_string(read_times[launch_count - 1]) + ";"; // ReadTime
    result_string += std::to_string(average_read_time) + ";"; // AverageReadTime
    result_string += std::to_string(read_bandwidth) + ";"; // REadBandWidth
    result_string += std::to_string(abs_error_read) + ";"; // AbsError
    result_string += std::to_string(rel_error_read); //RelError

    auto out = std::ofstream("file.csv", std::ios_base::app);
    out << result_string << std::endl;
    out.close();

}


time_measures test(ull size, ull launch_count) {
    time_measures test_results;
    for (ull test_counter = 0; test_counter < launch_count; test_counter++) {
        unsigned char* memory= (unsigned char *) malloc(size * sizeof(unsigned char));
        unsigned char* buffer= (unsigned char *) malloc(size * sizeof(unsigned char));
        for (int i = 0; i < size; i++) {
            buffer[i] = rand() % 256;
        }
        auto write_begin = get_time();
        for(ull i = 0; i < size; i++) {
            memory[i] = 'f';
        }
        auto write_end = get_time();
        auto write_time_diff = calculate_time(write_begin, write_end);

        auto read_begin = get_time();
        for(ull i = 0; i < size; i++) {
            memory[i];
        }
        auto read_end = get_time();
        auto read_time_diff = calculate_time(read_begin, read_end);
        
        delete[] memory;
        test_results.push_back({write_time_diff, read_time_diff});
    }

    return test_results;   
}


time_measures test(ull size, ull launch_count, std::string path) {
    std::string file_name = "temp";
    std::string full_path = path + file_name;
    time_measures test_results;
    for(int test_counter = 0; test_counter < launch_count; test_counter++) {
        unsigned char *memory = (unsigned char *)malloc(sizeof(unsigned char) * size);
        for (int i = 0; i < size; i++) {
            memory[i] = rand() % 256;
        }
        auto out = std::ofstream(full_path, std::ios_base::binary);
        auto write_begin = get_time();
        for (int i = 0; i < size; i++) {
            out << memory[i];
        }
        auto write_end = get_time();
        auto write_time_diff = calculate_time(write_begin, write_end);
        out.close();

        auto in = std::ifstream(full_path, std::ios_base::binary);
        delete[] memory;
        memory = (unsigned char *)malloc(sizeof(unsigned char) * size);

        auto read_begin = get_time();
        for(int i = 0; i < size; i++) {
            in >> memory[i];
        }
        auto read_end = get_time();
        in.close();
        auto read_time_diff = calculate_time(read_begin, read_end);

        delete[] memory;
        std::remove(full_path.c_str());
        test_results.push_back({write_time_diff, read_time_diff});
    }
    return test_results;
}


int main(int argc, char* argv[]) {
    std::string mode_string = get_command_line_argument("-m", argv);
    std::string size_string = get_command_line_argument("-b", argv);
    std::string launch_count_string = get_command_line_argument("-l", argv);
    std::string path_string = get_command_line_argument("-p", argv);

    if (mode_string == "") {
        return 1;
    }

    if (size_string == "") {
        return 1;
    }

    if (launch_count_string == "") {
        return 1;
    }

    if (mode_string != "RAM" && path_string == "") {
        return 1;
    }

    auto size = calculate_size(size_string);
    auto launch_count = stoull(launch_count_string);
    time_measures test_results;
    if (mode_string == "RAM") {
        test_results = test(size, launch_count);
    } else {
        test_results = test(size, launch_count, path_string);
    }

    calculate_and_write_statistic_into_file(test_results, mode_string, size, launch_count);

    return 0;
}