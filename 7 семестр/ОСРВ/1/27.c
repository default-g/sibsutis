#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

void clear_screen() { system("clear"); }

void print_center(const char *message) {
  int terminal_width;
  int terminal_height;
  int message_length;
  int padding;

  struct winsize w;
  ioctl(0, TIOCGWINSZ, &w);
  terminal_width = w.ws_col;
  terminal_height = w.ws_row;

  message_length = strlen(message);

  padding = terminal_height / 2;
  for (int i = 0; i < padding; i++) {
    printf("\n");
  }
  padding = (terminal_width - message_length) / 2;

  for (int i = 0; i < padding; i++) {
    printf(" ");
  }

  printf("%s\n", message);
  padding = terminal_height / 2;

  for (int i = 0; i < padding; i++) {
    printf("\n");
  }
}

int main() {
  clear_screen();
  print_center("HELLO");
  return 0;
}
