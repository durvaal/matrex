#include <stdio.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string.h>
#include "./headers/matrix_class.h"
#include "./headers/common_methods.h"

using namespace std;
using namespace std::chrono;

void writerFileWithMatricesMultiplication(Matrix *matricesProduct, size_t calculationTimeInNanoSeconds){
  ofstream matricesProductFile;

  matricesProductFile.open("matricesProduct.txt");
  matricesProductFile << matricesProduct->getCol() << " " << matricesProduct->getRow() << "\n";

  for (size_t row = 0; row < matricesProduct->getRow(); row++) {
    for (size_t col = 0; col < matricesProduct->getCol(); col++) {
      matricesProductFile << "c" << row + 1 << col + 1 << " " << matricesProduct->getElementValue(row, col) << "\n";
    }
  }

  matricesProductFile << calculationTimeInNanoSeconds << "\n";

  matricesProductFile.close();
};

void calculateMatricesMultiplicationSequentially(Matrix *matrix1, Matrix *matrix2) {
  if (matrix1->getCol() == matrix2->getRow()) {
    Matrix *matricesProduct = new Matrix();

    matricesProduct->setRow(matrix1->getRow());
    matricesProduct->setCol(matrix2->getCol());

    for (size_t row = 0; row < matrix1->getRow(); row++) {
      vector<size_t> emptyVector;

      for (size_t col = 0; col < matrix2->getCol(); col++) {
        emptyVector.push_back(0);
      }

      matricesProduct->addElement(emptyVector);
    }
    
    steady_clock::time_point beginTime = steady_clock::now();

    for (size_t row = 0; row < matrix1->getRow(); row++) {
      for (size_t col = 0; col < matrix2->getCol(); col++) {
        for (size_t inner = 0; inner < matrix2->getRow(); inner++) {
          size_t newElementValue = matricesProduct->getElementValue(row, col) + (matrix1->getElementValue(row, inner) * matrix2->getElementValue(inner, col));
          matricesProduct->setElementValue(row, col, newElementValue);
        }
      }
    }

    steady_clock::time_point endTime = steady_clock::now();

    writerFileWithMatricesMultiplication(matricesProduct, duration_cast<nanoseconds>(endTime - beginTime).count());

    delete matricesProduct;
  } else {
    throwException("Runtime error: It's not possible to multiply the matrices, the matrix1 has " + to_string(matrix1->getCol()) + " columns and the matrix2 has " + to_string(matrix2->getRow()) + " rows");
  }
}

void handleMatricesSequentially(char *arguments) {
  string matrixFileM1 = convertCharToString(strtok(NULL, " "));
  string matrixFileM2 = convertCharToString(strtok(NULL, " "));

  Matrix *matrix1 = loadMatrix(matrixFileM1);
  Matrix *matrix2 = loadMatrix(matrixFileM2);

  calculateMatricesMultiplicationSequentially(matrix1, matrix2);

  delete matrix1;
  delete matrix2;

  cout << "Calculated sequentially matrices with success \n\n";
}