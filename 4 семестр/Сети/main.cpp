#include <iostream>

#include <fstream>

using namespace std;

int check(unsigned int i) { return ((i & (1 << 31)) ? 1 : 0); }

int shift(unsigned int i, unsigned int bit) { return i = i << 1 | bit; }

int CRC32(unsigned int polinom, unsigned int registr, string file) {

  char ch;

  ifstream stream;

  stream.open(file, ifstream::in);

  if (!stream.is_open()) {
    return -1;
  }

  while (stream.get(ch)) {

    if (stream.eof())
      exit;

    for (int i = 7; i >= 0; i--) {

      if (check(registr)) {

        registr = shift(registr, ch & (1 << i) ? 1 : 0);

        registr ^= polinom;

      }

      else {

        registr = shift(registr, ch & (1 << i) ? 1 : 0);
      }
    }
  }

  return registr;
}

int main(int argc, char *argv[]) {

  setlocale(LC_ALL, "Russian");
  std::string file_path = std::string(argv[1]);

  unsigned int init = 0xFFFFFFFF, polynom = 0x04C11DB7;

  unsigned int result =
      CRC32(polynom, init, file_path);

  cout << std::hex;

  cout << "CRC32" << endl;

  cout << "Полином = " << polynom << endl;

  cout << "Чек сумма = " << result << endl;

  return 0;
}

