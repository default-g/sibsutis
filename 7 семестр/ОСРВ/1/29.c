#include <stdio.h>
#include <unistd.h>

void clear_line() {
  printf("\r\033[K");
  fflush(stdout);
}

int main() {
  // Выключаем отображение курсора
  printf("\033[?25l");
  fflush(stdout);

  int position = 0;
  int direction = 1;

  while (1) {
    clear_line();

    // Выводим пробелы перед символом
    for (int i = 0; i < position; i++) {
      printf(" ");
    }

    // Выводим символ
    printf("X");
    fflush(stdout);

    // Задержка для создания эффекта движения
    usleep(10000);

    // Изменяем позицию символа
    position += direction;

    // Изменяем направление при достижении границ экрана
    if (position == 0 || position == 50) {
      direction *= -1;
    }
  }

  // Включаем отображение курсора перед выходом
  printf("\033[?25h");
  fflush(stdout);

  return 0;
}
