#include <string>
#include "./matrix_class.h"

using namespace std;

#ifndef __SEQUENTIAL_H_
#define __SEQUENTIAL_H_

void split();
Matrix *loadMatrix(string file);
void writerFileWithMatricesMultiplication(Matrix *matricesProduct, size_t calculationTimeInNanoSeconds);
void calculateMatricesMultiplicationSequentially(Matrix *matrix1, Matrix *matrix2);
void handleMatricesSequentially(char *arguments);

#endif