#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>

int main() {
  int forkSize, currentPid;
  forkSize = 4;

  int parentPid = getpid();

  for (int i = 0; i < forkSize; i++) {
    currentPid = fork();
    if (currentPid < 0) {
      std::cout << "Error in fork\n";
      exit(0);
    }
    if (currentPid == 0) {
      std::cout << "РЕБЕНОК: ID предка = " << getppid() << "\n";
      std::cout << "РЕБЕНОК: ID = " << getpid() << "\n";
      sleep(1);
    } else {
      std::cout << "РОДИТЕЛЬ: ID = " << getpid() << "\n";
      std::cout << "РОДИТЕЛЬ: Значение, вернувшееся из fork() = " << currentPid << "\n";
    }

  }
  while(1);
  return 0;
}