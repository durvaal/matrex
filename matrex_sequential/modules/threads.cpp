#include <pthread.h>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <random>
#include <chrono>
#include "./headers/matrix_class.h"
#include "./headers/methods.h"

using namespace std;
using namespace std::chrono;

typedef struct arguments_thread
{
  size_t i;
  size_t n1;
  size_t n2;
  size_t m1;
  size_t m2;
  int p;
  vector<vector<int>> matrix1;
  vector<vector<int>> matrix2;
} arguments_t;

void getRow(size_t target_row, size_t col, vector<vector<int>> *matrix, vector<int> *row) {
  //percorre a linha, guardando o valor individualmente
  for (size_t i = 0; i < col; i++) {
    int aux = (*matrix)[target_row][i];
    row->push_back(aux);
  }
}

void getCol(size_t target_col, size_t row, vector<vector<int>> *matrix, vector<int> *col) {
  //percorre a linha, guardando o valor individualmente
  for (size_t i = 0; i < row; i++) {
    int aux = (*matrix)[target_col][i];
    col->push_back(aux);
  }
}

void *calculateResultMatrix(void *thrgs) {
  arguments_t *calc_thread = ((arguments_t *)thrgs);

  stringstream filename;
  fstream file;

  filename << "calculation_result" << calc_thread->i << ".txt";

  file.open(filename.str(), fstream::out);
  if (!file) {
    cout << "Error opening file" << endl;
    exit(1);
  }
  
  steady_clock::time_point beginTime = steady_clock::now();

  vector<int> row, col;
  vector<string> res;
  int count = 0;

  //Coordenadas iniciais da matriz resultado
  size_t x = int(calc_thread->p * calc_thread->i / calc_thread->m2);
  size_t y = (calc_thread->p * calc_thread->i) % calc_thread->m2;

  while (count < calc_thread->p) {
    stringstream result_row;
    int aux;

    //NECESSÁRIO: pegar a linha da matriz 1 envolvida na multiplicação
    getRow(x, calc_thread->m1, &calc_thread->matrix1, &row);
    //NECESSÁRIO: pegar a coluna da matriz 2 envolvida na multiplicação.
    getCol(calc_thread->n2, y, &calc_thread->matrix2, &col);
    //Multiplicação
    for (size_t j = 0; j < calc_thread->m1; j++){
      aux += col[j] * row[j];
    }

    result_row << "c" << x+1 << y+1 << " " << aux << endl;
    res.push_back(result_row.str());

    row.clear(); col.clear();

    count++;
    
  }

  steady_clock::time_point endTime = steady_clock::now();
  int TimeTotalInNanoSeconds = duration_cast<nanoseconds>(endTime - beginTime).count();

  file << TimeTotalInNanoSeconds << endl;

  pthread_exit(NULL);

}

int main (int argc, char const *argv[]) {
  int p = atoi(argv[3]);
  Matrix *matrix = new Matrix();
  fstream matrixFile;

  //descobrir o número de arquivos que deverão ser abertos
  size_t arq_number = ceil(n1*n2/p);

  pthread_t threads[arq_number];
  arguments_t calc_thread[arq_number];

  // descobrir como puxar informações das matrizes m1 e m2
  //informações necessárias: qtd linhas, colunas, numeros_matrizes

  for (size_t i=0; i < arq_number; i++){
    calc_thread[i].i = i;
    calc_thread[i].n1 = n1;
    calc_thread[i].m1 = m1;
    calc_thread[i].n2 = n2;
    calc_thread[i].m2 = m2;
    calc_thread[i].matrix1 = matriz1;
    calc_thread[i].matrix1 = matriz2;

    pthread_create(&threads[i], NULL, calculateResultMatrix, &calc_thread[i]);
  }

}