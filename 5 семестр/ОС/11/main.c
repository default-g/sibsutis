#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> 

#define MAX_ITEMS 5 
#define BUFFER_SIZE 5 

sem_t empty;
sem_t full;
int in = 0;
int out = 0;
int buffer[BUFFER_SIZE];
pthread_mutex_t mutex;


void red() {
  printf("\033[1;31m");
}


void green() {
  printf("\033[0;32m");
}


void *producer(void *pno) {   
    int item;
    for(int i = 0; i < MAX_ITEMS; i++) {
        item = rand() % 100;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[in] = item;
        int number_of_producer = *((int *) pno);
        green();
        printf("Производитель %d: Создал элемент %d в %d\n", number_of_producer, buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
}


void *consumer(void *cno) {   
    for(int i = 0; i < MAX_ITEMS; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        int item = buffer[out];
        red();
        printf("Потребитель %d: Удалил элемент %d в %d\n",*((int *)cno),item, out);
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(1);
    }
}


int main() {   

    pthread_t producers[5],consumers[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty,0,BUFFER_SIZE);
    sem_init(&full,0,0);

    int a[5] = {1,2,3,4,5};

    for(int i = 0; i < 5; i++) {
        pthread_create(&producers[i], NULL, producer, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&consumers[i], NULL, consumer, (void *)&a[i]);
    }

    for(int i = 0; i < 5; i++) {
        pthread_join(producers[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(consumers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
    
}