#include <string>
#include "./matrix_class.h"

using namespace std;

#ifndef __METHODS_H_
#define __METHODS_H_

void throwException(string message);
void split();
Matrix *loadMatrix(string file);
void calculateMatrix(Matrix *matrix1, Matrix *matrix2);
void loadSystem();
void listAvailableCommands();
void initializeProgram();

#endif