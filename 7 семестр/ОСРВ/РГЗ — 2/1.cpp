#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/neutrino.h>
#include <sys/sched.h>
#include <stdint.h>
#include <pthread.h>

int priorities[] = {1, 10, 15, 25, 29};
int priorities_count = sizeof(priorities) / sizeof(int);
pthread_mutex_t mutex;


int main() {

    pthread_mutexattr_t mutex_attr;
    pthread_mutexattr_init(&mutex_attr);
    pthread_mutexattr_setpshared(&mutex_attr, PTHREAD_PROCESS_SHARED);
    pthread_mutexattr_setprotocol(&mutex_attr, PTHREAD_PRIO_NONE);
    pthread_mutex_init(&mutex, &mutex_attr);

    pthread_mutex_lock(&mutex);

    pid_t pid = fork();
    if (pid == 0) {
        pid_t child_pid = getpid();
        for (int i = 0; i < priorities_count; i++) {
            setprio(child_pid, priorities[i]);
            pthread_mutex_lock(&mutex);
            pthread_mutex_unlock(&mutex);
        }
    } else {
        pthread_mutex_unlock(&mutex);
        uint64_t start_time;
        uint64_t end_time;
        for (int i = 0; i < priorities_count; i++) {
            start_time = ClockCycles();
            pthread_mutex_lock(&mutex);
            end_time = ClockCycles();
            printf("Ticks took for %d priority: %d \n", priorities[i], end_time - start_time);
            pthread_mutex_unlock(&mutex);
        }

        waitpid(pid, NULL, 0);
        pthread_mutex_destroy(&mutex);
    }

    return 0;
}
