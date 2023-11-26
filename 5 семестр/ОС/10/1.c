#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdatomic.h>

// #define MEMORY_MODEL __ATOMIC_RELAXED
// #define MEMORY_MODEL __ATOMIC_CONSUME
// #define MEMORY_MODEL __ATOMIC_ACQUIRE
// #define MEMORY_MODEL __ATOMIC_RELEASE
#define MEMORY_MODEL __ATOMIC_ACQ_REL
// #define MEMORY_MODEL __ATOMIC_SEQ_CST


unsigned long long int sh = 0;


void *my_thread0() {
  int i = 0;
  for (; i < 100000000; i++) {
    __atomic_fetch_add(&sh, 1, MEMORY_MODEL);
  }
}


void *my_thread1() {
  int i = 0;
  for (; i < 100000000; i++) {
     __atomic_fetch_add(&sh, 2, MEMORY_MODEL);
  }
}


int main() {
  pthread_t th_id[2];
  pthread_create(&th_id[0], NULL, &my_thread0, NULL);
  pthread_create(&th_id[1], NULL, &my_thread1, NULL);
  pthread_join(th_id[0], NULL);
  pthread_join(th_id[1], NULL);
  printf("%llu\n", sh);
  return 0;
}