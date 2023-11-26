g++ -std=c++11 -Wall -Wextra -o main main.cpp -lglfw -lGLEW -lGL
for (( i = 2; i <= 2048; i = i * 2))
do
    ./main $i
done