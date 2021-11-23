#include <stdio.h>
#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <random>
#include "./headers/common_methods.h"

using namespace std;
void writerMatrix(char *arguments){
  ofstream pArqMatriz1, pArqMatriz2;

  size_t n1 = convertCharToInt(strtok(NULL, " "));
  size_t m1 = convertCharToInt(strtok(NULL, " "));
  size_t n2 = convertCharToInt(strtok(NULL, " "));
  size_t m2 = convertCharToInt(strtok(NULL, " "));

  pArqMatriz1.open("m1.txt");
  if (!pArqMatriz1) {
    throwException("Erro ao abrir M1");
    abort();
  }

  pArqMatriz2.open("m2.txt");
  if (!pArqMatriz2) {
    throwException("Erro ao abrir M2");
    abort();
  }

  size_t M1[n1][m1], M2[n2][m2];

  mt19937 mt(42);
  uniform_real_distribution<float> linear_r(0.f, 100.f);

  for (size_t i = 0; i < n1; i++){
    for (size_t j = 0; j < m1; j++) {
      M1[i][j] = linear_r(mt);
    }
  }

  for (size_t i = 0; i < n2; i++){
    for (size_t j = 0; j < m2; j++) {
      M2[i][j] = linear_r(mt);
    }
  }

  string aux;

  pArqMatriz1 << n1 << " " << m1 << endl;
  pArqMatriz2 << n2 << " " << m2 << endl;

  for (size_t i = 0; i < n1; i++){
    for (size_t j = 0; j < m1; j++) {
      pArqMatriz1 << M1[i][j] << " ";
    }
    pArqMatriz1 << "" << endl;
  }

  for (size_t i = 0; i < n2; i++){
    for (size_t j = 0; j < m2; j++) {
      pArqMatriz2 << M2[i][j] << " "; 
    }
    pArqMatriz2 << "" << endl;
  }

  pArqMatriz1.close();
  pArqMatriz2.close();

  cout << "Created matrices with success \n\n";
}