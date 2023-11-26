#include <iostream>
#include <fstream>
#include <math.h>
#include <stdio.h>
#include <vector>
#include <chrono>
#include <time.h>

//ср.знач.
double average(std::vector<double> measures) {
    double sum = 0;
    for(double measure : measures) {
        sum += measure;
    }
    return sum / double(measures.size());
}

//дисперс.
double dispersion(std::vector<double> measures) {
    double avg = average(measures);
    double sum = 0;
    for (double measure : measures) {
        sum += (measure - avg) * (measure - avg);
    }
    return (1.0 / measures.size()) * sum;
}

//ср.квад.откл.
double standard_deviation(std::vector<double> measures) {
    return sqrt(dispersion(measures));
} 

double get_rand_number() {
    return static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
}

std::chrono::high_resolution_clock::time_point get_time() {
    return std::chrono::high_resolution_clock::now();
}

double calculate_time_diff(std::chrono::high_resolution_clock::time_point begin, std::chrono::high_resolution_clock::time_point end) {
    return std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
}

struct Stats {
    std::string PModel = "Intel(R) Core(TM) i7-9750H CPU @ 2.60GHz";
    std::string Task;
    std::string OpType = "double";
    std::string Opt = "None";
    std::string InsCount = "11";
    std::string Timer = "now()";
    std::string Time;
    std::string LNum;
    std::string AvTime;
    std::string AbsError;
    std::string RelError;
    std::string TaskPerf = "?";
    std::string to_csv_string() {
        return PModel + "; " 
        + Task + "; "
        + OpType + "; " 
        + Opt + "; "
        + InsCount + "; " 
        + Timer + "; " 
        + Time + "; " 
        + LNum + "; " 
        + AvTime + "; " 
        + AbsError + "; " 
        + RelError + "; " 
        + TaskPerf + "\n";
    }
};

double calculate_score(std::vector <double> measures) {
    double result = 0;
    for (auto measure : measures )
        result += 1 / (1 / measure);
    return pow(1 / (1 / average(measures)), -1);
}

double _fabs(double arg) {
    if (arg >= 0.0)
        return arg;
    else
        return (arg * -1.0);
}

double test_cos(double x) {
    double t, s;
    int p;
    p = 0;
    s = 1.0;
    t = 1.0;
    //int ins_count = 0;
    //ins_count += 7;
    while(_fabs(t/s) > 0.000001)
    {
        //ins_count += 3; // +2 from _fabs
        p++;
        //ins_count += 2;
        t = (-t * x * x) / ((2 * p - 1) * (2 * p));
        //ins_count += 9;
        s += t;
        //ins_count += 2;
    }
    //std::cout << "cos IC = " << ins_count + 1 << std::endl;
    return s;
}

double test_sin(double x) {
    int i = 1;
    double cur = x;
    double acc = 1;
    double fact= 1;
    double pow = x;
    //int ins_count = 0;
    //ins_count += 6;
    while (_fabs(acc) > 0.000001 && i < 100){
        //ins_count += 5; // +2 from _fabs
        fact *= ((2*i)*(2*i+1));
        //ins_count += 5;
        pow *= -1 * x*x;
        //ins_count += 4;
        acc =  pow / fact;
        //ins_count += 2;
        cur += acc;
        //ins_count += 2;
        i++;
        //ins_count += 2;
    }
    //std::cout << "sin IC = " << ins_count + 1 << std::endl;
    return cur;
}

Stats init_header(){
    Stats statistic = Stats();
        statistic.PModel = "CPU model";
        statistic.Task = "Task";
        statistic.OpType = "Operand type";
        statistic.Opt = "Opt key";
        statistic.InsCount = "Instruction Count";
        statistic.Timer = "Timer func.";
        statistic.Time = "Time per test";
        statistic.LNum = "Test num.";
        statistic.AvTime = "Average time";
        statistic.AbsError = "Absolute error";
        statistic.RelError = "Relative error";
        statistic.TaskPerf = "Task performance";
        return statistic;
}

int main() {
    std::vector<unsigned int> amount_of_tests;
    int i = 0;
    std::cout << "Input amount of tests for " << std::endl;
    for(int i = 0; i < 3; i++) {
        std::cout << (i + 1) << " task : ";
        int user_input = 0;
        std::cin >> user_input;
        if (user_input < 10) {
            std::cout << "Amount of tests must be greater or equal 10\n";
            continue;
        }
        amount_of_tests.push_back(user_input);
    }

    unsigned long long int total_tests_counter = 0;
    std::vector <Stats> statistics;
    std::vector <double> measures;
    auto random_number = get_rand_number();
    statistics.push_back(init_header());

    for (int i = 0; i < amount_of_tests[0]; i++) {
        if (i == 0)     test_cos(random_number);
        std::chrono::high_resolution_clock::time_point begin = get_time();
        test_cos(random_number);
        std::chrono::high_resolution_clock::time_point end = get_time();
        measures.push_back(calculate_time_diff(begin, end));
    }
    std::string avg_time = std::to_string(average(measures));
    std::string abs_error = std::to_string(sqrt(abs(dispersion(measures))));
    std::string rel_error = std::to_string(sqrt(abs(dispersion(measures))) / average(measures));
    char buffer[100];
    sprintf(buffer, "%.6f", calculate_score(measures));
    std::string score = std::string(buffer);
    for (auto measure : measures) {
        Stats statistic = Stats();
        statistic.Task = "cos";
        statistic.Time = std::to_string(measure);
        statistic.LNum = std::to_string(++total_tests_counter);
        statistic.AvTime = avg_time;
        statistic.AbsError = abs_error;
        statistic.RelError = rel_error;
        statistic.TaskPerf = score;
        statistic.InsCount = std::to_string(88);
        statistics.push_back(statistic);
    }
 
    measures.clear();
    random_number = get_rand_number();
    for (int i = 0; i < amount_of_tests[1]; i++) {
        std::chrono::high_resolution_clock::time_point begin = get_time();
        test_sin(random_number);
        std::chrono::high_resolution_clock::time_point end = get_time();
        measures.push_back(calculate_time_diff(begin, end));
    }
    avg_time = std::to_string(average(measures));
    abs_error = std::to_string(sqrt(abs(dispersion(measures))));
    rel_error = std::to_string(sqrt(abs(dispersion(measures))) / average(measures));
    sprintf(buffer, "%.6f", calculate_score(measures));
    score = std::string(buffer);
    for (auto measure : measures) {
        Stats statistic = Stats();
        statistic.Task = "sin";
        statistic.Time = std::to_string(measure);
        statistic.LNum = std::to_string(++total_tests_counter);
        statistic.AvTime = avg_time;
        statistic.AbsError = abs_error;
        statistic.RelError = rel_error;
        statistic.TaskPerf = score;
        statistic.InsCount = std::to_string(67);
        statistics.push_back(statistic);
    }

    measures.clear();
    random_number = get_rand_number();

    for (int i = 0; i < amount_of_tests[2]; i++) {
        std::chrono::high_resolution_clock::time_point begin = get_time();
        _fabs(random_number);
        std::chrono::high_resolution_clock::time_point end = get_time();
        measures.push_back(calculate_time_diff(begin, end));
    }
    avg_time = std::to_string(average(measures));
    abs_error = std::to_string(sqrt(abs(dispersion(measures))));
    rel_error = std::to_string(sqrt(abs(dispersion(measures))) / average(measures));
    sprintf(buffer, "%.6f", calculate_score(measures));
    score = std::string(buffer);
    for (auto measure : measures) {
        Stats statistic = Stats();
        statistic.Task = "fabs";
        statistic.Time = std::to_string(measure);
        statistic.LNum = std::to_string(++total_tests_counter);
        statistic.AvTime = avg_time;
        statistic.AbsError = abs_error;
        statistic.RelError = rel_error;
        statistic.TaskPerf = score;
        statistic.InsCount = std::to_string(2);
        statistics.push_back(statistic);
    }

    std::ofstream file_out("out.csv");
    for (Stats stats : statistics) {
        file_out << stats.to_csv_string();
    }
    file_out.close();

}