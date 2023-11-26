#include <iostream>
#include <cstdlib>
#include <stdlib.h>


int main() {
    for (int i = 0; i < 3; i++) {
        std::system("nohup ./children &");
    }
}