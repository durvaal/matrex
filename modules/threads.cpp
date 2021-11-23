#include <pthread.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <string.h>
#include "./headers/matrix_class.h"
#include "./headers/common_methods.h"

using namespace std;
using namespace std::chrono;

typedef struct arguments_thread
{
  size_t i;
  size_t p;
  Matrix *matrix1;
  Matrix *matrix2;
} arguments_t;

void *calculateResultMatrix(void *thrgs) {
  arguments_t *calc_thread = ((arguments_t *)thrgs);

  stringstream filename;
  fstream file;

  filename << "./thread-files/threadProduct" << calc_thread->i << ".txt";

  file.open(filename.str(), fstream::out);
  if (!file) {
    throwException("Error opening file 'threadProduct" + to_string(calc_thread->i) + "'");
    exit(1);
  }
  
  steady_clock::time_point beginTime = steady_clock::now();

  vector<size_t> row, col;
  size_t count = 0;

  size_t targetRow = size_t(calc_thread->p * calc_thread->i / calc_thread->matrix2->getCol());
  size_t targetCol = (calc_thread->p * calc_thread->i) % calc_thread->matrix2->getCol();

  while (count < calc_thread->p) {
    size_t aux;

    getRowInterval(targetRow, calc_thread->matrix1->getCol(), calc_thread->matrix1, &row);
    getColInterval(targetCol, calc_thread->matrix1->getRow(), calc_thread->matrix2, &col);

    for (size_t j = 0; j < (size_t)calc_thread->matrix1->getCol(); j++){
      aux += col[j] * row[j];
    }

    file << "c" << targetRow + 1 << targetCol + 1 << " " << aux << endl;

    row.clear(); col.clear();

    count++;

    targetCol++;

    if (targetCol >= (size_t)calc_thread->matrix2->getCol()) {
      targetRow++;
      targetCol = (calc_thread->p * calc_thread->i) % calc_thread->matrix2->getCol();
    }
  }

  steady_clock::time_point endTime = steady_clock::now();
  size_t TimeTotalInNanoSeconds = duration_cast<nanoseconds>(endTime - beginTime).count();

  file << TimeTotalInNanoSeconds << endl;
  file.close();

  pthread_exit(NULL);
}

void calcThreads(char *arguments) {
  string matrixFileM1 = convertCharToString(strtok(NULL, " "));
  string matrixFileM2 = convertCharToString(strtok(NULL, " "));
  size_t p = convertCharToInt(strtok(NULL, " "));

  Matrix *matrix1 = loadMatrix(matrixFileM1);
  Matrix *matrix2 = loadMatrix(matrixFileM2);

  size_t threads_number = ceil(matrix1->getRow()*matrix2->getCol()/p);

  pthread_t threads[threads_number];
  arguments_t calc_thread[threads_number];

  for (size_t i=0; i < threads_number; i++){
    calc_thread[i].i = i;
    calc_thread[i].p = p;
    calc_thread[i].matrix1 = matrix1;
    calc_thread[i].matrix2 = matrix2;

    pthread_create(&threads[i], NULL, calculateResultMatrix, &calc_thread[i]);
  }

  cout << "Calculated thread matrices with success \n\n";
}