#ifndef MATRIX_HANDLER
#define MATRIX_HANDLER
#include <iostream>
#include "utility.h"

#define GREEN "\033[32m"
#define RED "\033[31m"
#define STANDART_COLOR "\033[0m"

using namespace std;

void init_matrix(float *matrix)
{
    srand(time(NULL));
    for (int i = 0; i < NUM_ELEMENTS; i++)
        matrix[i] = (float)(rand() % 90 + 10);
}

void init_zero_matrix(float *matrix)
{
    for (int i = 0; i < NUM_ELEMENTS; i++)
        matrix[i] = 0.0f;
}

void print_matrix(float *matrix)
{
    for (int i = 0; i < MATRIX_SIZE; i++)
    {
        for (int j = 0; j < MATRIX_SIZE; j++)
            cout << matrix[i * MATRIX_SIZE + j] << " ";
        cout << endl;
    }
    cout << endl;
}

#endif