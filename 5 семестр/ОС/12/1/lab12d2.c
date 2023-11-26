#include "lab12d.h"

int main(int argc, char *argv[]) {
  int semid, shmid, xfrs, bytes;
  struct shmseg *shmp;
  semid = semget(SEM_KEY, 0, 0);
  if (semid == -1)
    fprintf(stderr, "semget");
  shmid = shmget(SHM_KEY, 0, 0);
  if (shmid == -1)
    fprintf(stderr, "shmget");
  shmp = shmat(shmid, NULL, SHM_RDONLY);
  if (shmp == (void *)-1)
    fprintf(stderr, "shmat");
  for (xfrs = 0, bytes = 0;; xfrs++) {
    if (reserveSem(semid, READ_SEM) == -1)
      fprintf(stderr, "reserveSem");
    if (shmp->cnt == 0)
      break;
    bytes += shmp->cnt;
    if (write(STDOUT_FILENO, shmp->buf, shmp->cnt) != shmp->cnt)
      fprintf(stderr, "partial/failed write");
    if (releaseSem(semid, WRITE_SEM) == -1) /* Give writer a turn */
      fprintf(stderr, "releaseSem");
  }

  if (shmdt(shmp) == -1)
    fprintf(stderr, "shmdt");
  if (releaseSem(semid, WRITE_SEM) == -1)
    fprintf(stderr, "releaseSem");
  fprintf(stderr, "Received %d bytes (%d xfrs)\n", bytes, xfrs);
  exit(EXIT_SUCCESS);
}