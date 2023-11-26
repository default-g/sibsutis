#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

struct termios original_termios;

void restore_terminal() {
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
}

void enable_raw_mode() {
  struct termios raw_termios;

  // Получаем исходные настройки терминала
  tcgetattr(STDIN_FILENO, &original_termios);
  atexit(restore_terminal);

  raw_termios = original_termios;

  // Отключаем канонический (строчный) режим
  raw_termios.c_lflag &= ~(ICANON | ECHO);

  // Отключаем обработку сигналов и символьных кодов
  raw_termios.c_lflag &= ~ISIG;
  raw_termios.c_iflag &= ~(IXON | ICRNL);

  // Отключаем вывод символов в зависимости от их значения
  raw_termios.c_iflag &= ~ISTRIP;
  raw_termios.c_oflag &= ~OPOST;
  raw_termios.c_cflag |= CS8;

  // Устанавливаем минимальное количество символов и время ожидания
  raw_termios.c_cc[VMIN] = 0;
  raw_termios.c_cc[VTIME] = 1;

  // Применяем новые настройки терминала
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);
}

int main() {
  enable_raw_mode();

  char c;
  while (1) {
    // Чтение символа с клавиатуры
    if (read(STDIN_FILENO, &c, 1) == -1) {
      perror("read");
      exit(1);
    }

    // Если нажата клавиша 'q', выходим из программы
    if (c == 'q') {
      break;
    }

    // Выводим код нажатой клавиши
    printf("Код клавиши: %d\n", c);
  }

  // Восстанавливаем исходные настройки терминала
  restore_terminal();

  return 0;
}
