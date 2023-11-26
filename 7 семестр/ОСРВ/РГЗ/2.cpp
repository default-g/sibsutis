#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int *data = (int *)malloc(sizeof(int)); // Выделяем динамическую память
    int *new_data = new int;

    if (data == NULL) {
        perror("malloc");
        return 1;
    }

    *data = 42;
    *new_data = 42;

    pid_t pid = fork(); // Создаем дочерний процесс

    if (pid == -1) {
        perror("fork");
        return 1;
    }

    if (pid == 0) { // Это код, выполняемый дочерним процессом
        printf("Дочерний процесс: Значение data = %d, Адрес = %p\n", *data, data);
        printf("Дочерний процесс: Значение new_data = %d, Адрес = %p\n", *new_data, new_data);
        (*data)++; // Меняем значение
        (*new_data)++; // Меняем значение
        printf("Дочерний процесс: Новое значение data = %d, Адрес = %p\n", *data, data);
        printf("Дочерний процесс: Новое значение new_data = %d, А адрес = %p\n", *new_data, new_data);
    } else { // Это код, выполняемый родительским процессом
        printf("Родительский процесс: Значение data = %d, Адрес = %p\n", *data, data);
        printf("Родительский процесс: Значение new_data = %d, Адрес = %p\n", *new_data, new_data);
        sleep(1); // Даем дочернему процессу время для выполнения
        printf("Родительский процесс: Значение data осталось неизменным: %d, Адрес = %p\n", *data, data);
        printf("Родительский процесс: Значение new_data осталось неизменным: %d, Адрес = %p\n", *new_data, new_data);
    }

    free(data); // Освобождаем выделенную память
    delete new_data;

    return 0;
}
