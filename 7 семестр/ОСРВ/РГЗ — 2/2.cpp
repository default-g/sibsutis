#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/neutrino.h>
#include <inttypes.h>

#define CLOCKS_PER_MSEC (CLOCKS_PER_SEC / 1000)

int main() {
    size_t page_size = getpagesize();
    size_t mem_size = page_size; // размер памяти для выделения (1 страница)

    printf("Page size: %ld\n", page_size);

    void* mem = mmap(NULL, mem_size, PROT_READ | PROT_WRITE | PROT_NOCACHE, MAP_PRIVATE | MAP_ANON, NOFD, 0);
    if (mem == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    char hello[] = "Memory Test!\n";
    int string_length = sizeof(hello) / sizeof(char);


    uint64_t start_time = ClockCycles();

    for (int i = 0; i < string_length; i++) {
        ((char*)mem)[i] = hello[i];
    }

    memset((((char *)mem) + string_length - 1), 0x00, mem_size - string_length);

    uint64_t end_time = ClockCycles();

    printf("Write time without cache: %d\n", end_time - start_time);

    start_time = ClockCycles();
    for (int i = 0; i < mem_size; i++) {
        ((char*)mem)[i];
    }
    end_time = ClockCycles();

    printf("Read time without cache: %d\n", end_time - start_time);

    munmap(mem, mem_size);

    mem = mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, NOFD, 0);
    if (mem == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }

    start_time = ClockCycles();

    for (int i = 0; i < string_length; i++) {
        ((char*)mem)[i] = hello[i];
    }

    memset((((char *)mem) + string_length - 1), 0x00, mem_size - string_length);

    end_time = ClockCycles();

    printf("Write time with cache: %d\n", end_time - start_time);

    start_time = ClockCycles();

    for (int i = 0; i < mem_size; i++) {
        ((char*)mem)[i];
    }

    end_time = ClockCycles();

    printf("Read time with cache: %d\n", end_time - start_time);

    munmap(mem, mem_size);

    return 0;
}
