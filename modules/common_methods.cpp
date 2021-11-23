#include <stdio.h>
#include <sstream>
#include <fstream>
#include <random>
#include "./headers/matrix_class.h"

using namespace std;

void throwException(string message) {
  ostringstream oss;
  oss << message;
  throw runtime_error(oss.str());
}

void getRowInterval(size_t targetRow, size_t col, Matrix *matrix, vector<size_t> *row) {
  //percorre a linha, guardando o valor individualmente
  for (size_t i = 0; i < col; i++) {
    size_t aux = matrix->getElementValue(targetRow, i);
    row->push_back(aux);
  }
}

void getColInterval(size_t targetCol, size_t row, Matrix *matrix, vector<size_t> *col) {
  //percorre a linha, guardando o valor individualmente
  for (size_t i = 0; i < row; i++) {
    size_t aux = matrix->getElementValue(targetCol, i);
    col->push_back(aux);
  }
}

size_t convertCharToInt(char *field) {
  return atoi(field);
}

string convertCharToString(char *field) {
  string fieldValueConverted;
  fieldValueConverted = field;
  return fieldValueConverted;
}

template <typename Out>
void split(const string &line, Out result) {
  istringstream iss(line);
  string element;
  char delimiter = ' ';

  while (getline(iss, element, delimiter)) {
    *result++ = (size_t)stoi(element);
  }
}

Matrix *loadMatrix(string file) {
  Matrix *matrix = new Matrix();
  string line;
  ifstream matrixFile(file);

  if (matrixFile.is_open()) {
    size_t indexLine = 0;

    while (getline(matrixFile, line)) {
      indexLine++;

      if (indexLine == 1) { // on line 1 of the file is the size of the matrix
        if (line != "") {
          vector<size_t> elements;
          split(line, back_inserter(elements));

          if (elements.size() == 2) {
            matrix->setCol(elements[0]);
            matrix->setRow(elements[1]);
          } else {
            throwException("Runtime error: The file '" + file + "' has incorrect size definition");
          }
        } else {
          throwException("Runtime error: The file '" + file + "' has not size defined");
        }
      } else {
        if (line != "") { // on line 2 of the file is the elements of the matrix
          vector<size_t> element;
          split(line, back_inserter(element));

          if ((size_t)(element.size()) == matrix->getCol()) {
            matrix->addElement(element);
          } else {
            throwException("Runtime error: The file '" + file + "' has incorrect elements definition");
          }
        } else {
          throwException("Runtime error: The file '" + file + "' has not element defined");
        }
      }
    }
  } else {
    throwException("Runtime error: File '" + file + "' is not opened");
  }

  matrixFile.close();

  return matrix;
}