
#define _GNU_SOURCE

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sched.h>



int turn = 1;
int sh = 0;

void* my_thread0() {
    for (int i = 0; i < 100; i++) {
        while(turn);
        sh++;
        turn = 0;
    }
}


void* my_thread1() {
    for (int i = 0; i < 100; i++) {
        while(!turn);
        sh += 2;
        turn = 1;
    }
}

int main() {
    pthread_t th_id[2];
    cpu_set_t cpuset;

    pthread_create(&th_id[0], NULL, &my_thread0, NULL);
    pthread_create(&th_id[1], NULL, &my_thread1, NULL);

    CPU_ZERO(&cpuset);
    for (int j = 0; j <= 1; j++) {
        CPU_SET(j, &cpuset);
    }
    pthread_setaffinity_np(th_id[0], sizeof(cpu_set_t), &cpuset);
    pthread_setaffinity_np(th_id[1], sizeof(cpu_set_t), &cpuset);
    pthread_join(&th_id[0], NULL);
    pthread_join(&th_id[1], NULL);
    printf("%lld\n", sh);
    return 0;

}