#include <string>
#include "./matrix_class.h"

using namespace std;

#ifndef __COMMON_METHODS_H_
#define __COMMON_METHODS_H_

void throwException(string message);
void getRowInterval(size_t targetRow, size_t col, Matrix *matrix, vector<size_t> *row);
void getColInterval(size_t targetCol, size_t row, Matrix *matrix, vector<size_t> *col);
size_t convertCharToInt(char *field);
string convertCharToString(char *field);
template <typename Out>
void split(const string &line, Out result);
Matrix *loadMatrix(string file);

#endif