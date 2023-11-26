#include <chrono>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

unsigned long dim;
unsigned short opt;


long double dgemm(std::vector<std::vector<double>> &a,
                  std::vector<std::vector<double>> &b,
                  std::vector<std::vector<double>> &c) {
  auto start = std::chrono::system_clock::now();
  for (unsigned long it = 0; it < a.size(); ++it)
    for (unsigned long jt = 0; jt < a.size(); ++jt)
      for (unsigned long et = 0; et < a.size(); ++et)
        c[it][jt] += a[it][et] * b[et][jt];
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<long double> difference = end - start;
  return difference.count();
}


long double dgemm_opt_1(std::vector<std::vector<double> > &a,
                 std::vector<std::vector<double> > &b,
                 std::vector<std::vector<double> > &c) {
  auto start = std::chrono::system_clock::now();
  double temp;
  double sum = 0.0;
  auto size = a.size();

  for (int i = 0; i < size; i++) {
    for (int k = 0; k < size; k++) {
      temp = a[i][k];
      sum = 0.0;
      for (int j = 0; j < size; j++)
        sum += temp * b[k][j];
      c[i][k] = sum;
    }
  }
  auto end = std::chrono::system_clock::now();
  std::chrono::duration<long double> difference = end - start;
  return difference.count();
}


int main(int argc, char *argv[]) {
  dim = std::stol(std::string(argv[1]));
  opt = std::stol(std::string(argv[2]));
  std::vector<std::vector<double> > a(dim, std::vector<double>(dim)),
      b(dim, std::vector<double>(dim)), c(dim, std::vector<double>(dim));
  std::random_device rd;
  std::mt19937 rng(rd());
  std::normal_distribution<double> dist;
  for (auto &it : a)
    for (auto &_ : it)
      _ = dist(rng);
  for (auto &it : b)
    for (auto &_ : it)
      _ = dist(rng);
  long double time;
  if (opt == 0)
    time = dgemm(a, b, c);
  else if (opt == 1)
    time = dgemm_opt_1(a, b, c);

  std::ofstream out("file.csv", std::ios_base::app);
  if (out.is_open()) {
    out << dim << ";" << time << std::endl;
  }
  out.close();
}