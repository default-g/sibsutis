#include <sys/types.h> 
#include <unistd.h> 
#include <iostream>
#include <array>

std::string get_stdout_from_command(std::string cmd) {
    std::array<char, 256> buffer;
    std::string result;

    FILE* pipe = popen(cmd.c_str(), "r");

    if (!pipe) throw std::runtime_error("popen() failed!");

    while (!feof(pipe)) {
        if (fgets(buffer.data(), 256, pipe) != nullptr) {
          result += buffer.data();
        };
    }
    pclose(pipe);

    return result;
}


int main() {
  pid_t pid;
  pid = fork();
  for (int i = 0; i < 3; ++i) {
    if (pid == -1) {
      perror("fork"); //произошла ошибка
      exit(1); //выход из родительского процесса
    } else if (pid > 0) {
      std::cout << "[PARENT] Это процесс-родитель: " << get_stdout_from_command("ps | grep -m1 " + std::to_string(getpid()));
      // system(("kill -9 " + std::to_string(getpid())).c_str());
    } else {
      std::cout << "[CHILD] Это процесс-ребенок: " << get_stdout_from_command("ps | grep -m1 " + std::to_string(getpid()));
    }
    //std::cout << i << "\n";
  }
  while(true);
  return 0;
}