#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>

pthread_mutex_t lock;
int turn = 0;
int shmid;
int shmkey = 0x5678;//u can choose it as your choice


void* create_shared_memory(size_t size) {
  int protection = PROT_READ | PROT_WRITE;

  int visibility = MAP_SHARED | MAP_ANONYMOUS;

  return mmap(NULL, size, protection, visibility, -1, 0);
}


void *my_thread0() {
  int i = 0;
  for (; i < 10000; i++) {
    pthread_mutex_lock(&lock);
    int *data = (int *) shmat(shmid, 0, 0);
    (*data) += 1;
    shmdt((void *) data);
    pthread_mutex_unlock(&lock);
  }
}


void *my_thread1() {
  int i = 0;
  for (; i < 10000; i++) {
    pthread_mutex_lock(&lock);
    int *data = (int *) shmat(shmid, 0, 0);
    (*data) += 2;
    shmdt((void *) data);
    pthread_mutex_unlock(&lock);
  }
}


int main() {
  shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
  if (shmid == -1) {
    perror("Could not get shared memory");
    return EXIT_FAILURE;
  }
  pthread_mutex_init(&lock, 0);
  int *data = shmat(shmid, 0, 0);
  *data = 0;
  shmdt(data);
  pthread_t th_id[2];
  pthread_create(&th_id[0], NULL, &my_thread0, NULL);
  pthread_create(&th_id[1], NULL, &my_thread1, NULL);
  pthread_join(th_id[0], NULL);
  pthread_join(th_id[1], NULL);
  data = shmat(shmid, 0, 0);
  printf("%d\n", *data);
  shmctl(shmid, IPC_RMID,NULL);
  return 0;
}