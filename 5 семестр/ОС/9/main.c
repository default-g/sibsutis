#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
int sh = 0;

int turn = 0;

void *my_thread0() {
  int i = 0;
  for (; i < 100000; i++) {
    while (turn);
    sh++; 
    turn = 1;
  }
}


void *my_thread1() {
  int i = 0;
  for (; i < 100000; i++) {
   while (!turn);
    sh += 2;
    turn = 0;
  }
}

int main() {
  pthread_t th_id[2];
  pthread_create(&th_id[0], NULL, &my_thread0, NULL);
  pthread_create(&th_id[1], NULL, &my_thread1, NULL);
  pthread_join(th_id[0], NULL);
  pthread_join(th_id[1], NULL);
  printf("%d\n", sh);
  return 0;
}