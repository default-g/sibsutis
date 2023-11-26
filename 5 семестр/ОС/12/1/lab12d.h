#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <sys/shm.h>


typedef enum { FALSE, TRUE } Boolean;
#define SHM_KEY 0x1234
#define SEM_KEY 0x5678
#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
#define WRITE_SEM 0
#define READ_SEM 1
#define BUF_SIZE 1024
extern Boolean bsUseSemUndo;
extern Boolean bsRetryOnEintr;
struct shmseg {
    int cnt;
    char buf[BUF_SIZE]; 
};

union semun { //используется в вызовах semctl(...) 
    int val;
    struct semid_ds *buf;
    unsigned short *array;
    struct seminfo * __buf;
};

int reserveSem(int semId, int semNum);
int releaseSem(int semId, int semNum);
int initSemAvailable(int semId, int semNum);
int initSemInUse(int semId, int semNum);