#include <iostream>
#include <atomic>
#include <thread>

#define MEMORY_MODEL std::memory_order_acq_rel

std::atomic <unsigned long long> sh(0);


void my_thread0() {
    for (int i = 0; i < 100000000; i++) {
        sh.fetch_add(1, MEMORY_MODEL);
    }
}


void my_thread1() {
    for(int i = 0; i < 100000000; i++) {
        sh.fetch_add(2, MEMORY_MODEL);
    }
}


int main() {
    std::thread th1(my_thread0);
    std::thread th2(my_thread1);
    th1.join();
    th2.join();

    std::cout << sh << std::endl;
}



