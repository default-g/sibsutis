#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

volatile sig_atomic_t stop;

void handle_signal(int signal) { stop = 1; }

void clear_screen() {
  printf("\033[2J");
  printf("\033[1;1H");
  fflush(stdout);
}

void move_cursor(int x, int y) {
  printf("\033[%d;%dH", y, x);
  fflush(stdout);
}

void set_color(int color) {
  printf("\033[38;5;%dm", color);
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  if (argc < 5) {
    printf(
        "Usage: ./moving_symbol <symbol> <color> <x_velocity> <y_velocity>\n");
    return 1;
  }

  char symbol = argv[1][0];
  int color = atoi(argv[2]);
  int x_velocity = atoi(argv[3]);
  int y_velocity = atoi(argv[4]);

  struct termios original_termios;
  tcgetattr(STDIN_FILENO, &original_termios);

  struct termios raw_termios = original_termios;
  raw_termios.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_termios);

  int original_flags = fcntl(STDIN_FILENO, F_GETFL);
  fcntl(STDIN_FILENO, F_SETFL, original_flags | O_NONBLOCK);

  signal(SIGINT, handle_signal);

  int x = 1;
  int y = 1;
  int x_max, y_max;

  while (!stop) {
    clear_screen();
    move_cursor(x, y);
    set_color(color);
    printf("%c", symbol);
    fflush(stdout);

    usleep(100000); 

    // Расчет новой позиции
    x += x_velocity;
    y += y_velocity;

    // Получение размера терминала
    printf("\033[999B\033[999C");
    fflush(stdout);
    printf("\033[6n");
    fflush(stdout);
    scanf("\033[%d;%dR", &y_max, &x_max);

    if (x > x_max) {
      x = 1;
    } else if (x < 1) {
      x = x_max;
    }

    if (y > y_max) {
      y = 1;
    } else if (y < 1) {
      y = y_max;
    }
  }

  tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_termios);
  fcntl(STDIN_FILENO, F_SETFL, original_flags);

  return 0;
}
