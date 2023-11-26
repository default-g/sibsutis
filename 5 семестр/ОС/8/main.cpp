#include <iostream>
#include <pthread.h>
#include <thread>
#include <chrono>
#include <math.h>

#define AMOUNT_OF_VALUES 99999999
#define MAX_THREADS 8

int values_for_sum[AMOUNT_OF_VALUES];
unsigned long long int sum;


void fill_values_for_sum() {
    for(int i = 0; i < AMOUNT_OF_VALUES; i++) {
        values_for_sum[i] = 1;
    }
}


long double calculate_without_threads() {
    auto start = std::chrono::steady_clock::now();
    for(int i = 0; i < AMOUNT_OF_VALUES; i++) {
        sum += values_for_sum[i];
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count();
}


unsigned long long int sum_buffers[AMOUNT_OF_VALUES];

typedef struct args {
    int start_index;
    int end_index;
    int number_of_sum_buffer;
} indexes;


void* sum_array(void* args) {
    indexes *the_indexes = (indexes *) args;

    int start_i = the_indexes->start_index;
    int end_i = the_indexes->end_index;
    int number_of_sum_buffer = the_indexes->number_of_sum_buffer;

    for (int i = start_i; i < end_i; i++) {
        sum_buffers[number_of_sum_buffer] += values_for_sum[i];
    }

    pthread_exit(NULL);
}


long double calculating_with_posix_threads() {
    pthread_t threads[MAX_THREADS];
    indexes args_pool[MAX_THREADS];


    int n_split = AMOUNT_OF_VALUES < MAX_THREADS ? AMOUNT_OF_VALUES : MAX_THREADS;
    int n_work = AMOUNT_OF_VALUES < MAX_THREADS ? 1 : AMOUNT_OF_VALUES / MAX_THREADS;


    for (int i = 0; i < n_split; i++) {
        indexes args;
        args.start_index = i * n_work;
        args.end_index = args.start_index + n_work;
        args.number_of_sum_buffer = i;
        if (i == n_split - 1 && args.end_index < AMOUNT_OF_VALUES) {
            args.end_index = AMOUNT_OF_VALUES;
        }
        args_pool[i] = args;
        pthread_create(&threads[i], NULL, sum_array, (void *) &args_pool[i]);
    }

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n_split; i++) {
        pthread_join(threads[i], NULL);
    }
    for (int i = 0; i < n_split; i++) {
        sum += sum_buffers[i];
        sum_buffers[i] = 0;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count();
}


long double calculating_with_std_threads() {
    std::thread threads[MAX_THREADS];
    indexes args_pool[MAX_THREADS];

    int n_split = AMOUNT_OF_VALUES < MAX_THREADS ? AMOUNT_OF_VALUES : MAX_THREADS;
    int n_work = AMOUNT_OF_VALUES < MAX_THREADS ? 1 : AMOUNT_OF_VALUES / MAX_THREADS;
    auto f = [](indexes args) {
        int start_i = args.start_index;
        int end_i = args.end_index;
        int number_of_sum_buffer = args.number_of_sum_buffer;
        for (int i = start_i; i < end_i; i++) {
            sum_buffers[number_of_sum_buffer] += values_for_sum[i];
        }
    };

    for (int i = 0; i < n_split; i++) {
        indexes args;
        args.start_index = i * n_work;
        args.end_index = args.start_index + n_work;
        args.number_of_sum_buffer = i;
        if (i == n_split - 1 && args.end_index < AMOUNT_OF_VALUES) {
            args.end_index = AMOUNT_OF_VALUES;
        }
        args_pool[i] = args;
        threads[i] = std::thread(f, args_pool[i]);
    }

    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < n_split; i++) {
        threads[i].join();
    }
    for(int i = 0; i < n_split; i++) {
        sum += sum_buffers[i];
        sum_buffers[i] = 0;
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    return std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed_seconds).count();

}


int main() {
    fill_values_for_sum();
    sum = 0;
    auto time = calculate_without_threads();
    std::cout << "Time without threads: " << time << " nanoseconds" << std::endl;
    auto no_threads_sum = sum;
    sum = 0;
    time = calculating_with_posix_threads();
    std::cout << "Time with posix threads: " << time << " nanoseconds" << std::endl;
    auto posix_threads_sum = sum;
    sum = 0;
    time = calculating_with_std_threads();
    std::cout << "Time with std threads: " << time << " nanoseconds" << std::endl;
    auto std_threads_sum = sum;

    std::cout << "Are all sums are equal: " << ((no_threads_sum == posix_threads_sum && posix_threads_sum == std_threads_sum) ? "Yes" : "No") << std::endl;

}