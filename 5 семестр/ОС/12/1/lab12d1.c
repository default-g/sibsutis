#include "lab12d.h"

int main(int argc, char *argv[]) {
  int semid, shmid, bytes, xfrs;
  struct shmseg *shmp;
  union semun dummy;
  semid = semget(SEM_KEY, 2, IPC_CREAT | OBJ_PERMS);
  if (semid == -1)
    fprintf(stderr, "semget");
  if (initSemAvailable(semid, WRITE_SEM) == -1)
    fprintf(stderr, "initSemAvailable");
  if (initSemInUse(semid, READ_SEM) == -1)
    fprintf(stderr, "initSemInUse");
  shmid = shmget(SHM_KEY, sizeof(struct shmseg), IPC_CREAT | OBJ_PERMS);
  if (shmid == -1)
    fprintf(stderr, "shmget");
  shmp = shmat(shmid, NULL, 0);
  if (shmp == (void *)-1)
    fprintf(stderr, "shmat");

  for (xfrs = 0, bytes = 0;; xfrs++, bytes += shmp->cnt) {
    if (reserveSem(semid, WRITE_SEM) == -1)
      fprintf(stderr, "reserveSem");
    shmp->cnt = read(STDIN_FILENO, shmp->buf, BUF_SIZE);
    if (shmp->cnt == -1)
      fprintf(stderr, "read");
    if (releaseSem(semid, READ_SEM) == -1)
      fprintf(stderr, "releaseSem"); /* Give reader a turn */
    if (shmp->cnt == 0)
      break;
  }
  if (reserveSem(semid, WRITE_SEM) == -1)
    fprintf(stderr, "reserveSem");
  if (semctl(semid, 0, IPC_RMID, dummy) == -1)
    fprintf(stderr, "semctl");
  if (shmdt(shmp) == -1)
    fprintf(stderr, "shmdt");
  if (shmctl(shmid, IPC_RMID, 0) == -1)
    fprintf(stderr, "shmctl");
  fprintf(stderr, "Sent %d bytes (%d xfrs)\n", bytes, xfrs);
  exit(EXIT_SUCCESS);
}