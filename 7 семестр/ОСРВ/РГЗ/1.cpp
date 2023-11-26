#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <unistd.h>

// Глобальные переменные
pthread_t thread;
sem_t semaphore;

clock_t start_time;
clock_t end_time;

// Функция, которую выполнит нить
void* worker_function(void* arg) {
    // Засекаем время создания нити
    start_time = clock();
    sem_post(&semaphore); // Активизация семафора
    return NULL;
}

int main() {
    // Инициализация семафора
    sem_init(&semaphore, 0, 0);

    // Инициализация потока
    if (pthread_create(&thread, NULL, worker_function, NULL) != 0) {
        perror("pthread_create");
        return 1;
    }

    // Ждем, пока семафор будет активирован
    sem_wait(&semaphore);

    // Засекаем время активизации семафора
    end_time = clock();

    double elapsed_time_create = (double)(end_time - start_time) / CLOCKS_PER_SEC;
    printf("Время создания нити: %lf секунд\n", elapsed_time_create);

    // Ожидание завершения нити
    if (pthread_join(thread, NULL) != 0) {
        perror("pthread_join");
        return 1;
    }

    sem_destroy(&semaphore); // Освобождение ресурсов семафора

    return 0;
}
