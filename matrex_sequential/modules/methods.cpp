#include <stdio.h>
#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <random>
#include <chrono>
#include "./headers/matrix_class.h"
#include "./headers/methods.h"

using namespace std;
using namespace std::chrono;

void throwException(string message) {
  ostringstream oss;
  oss << message;
  throw runtime_error(oss.str());
}

template <typename Out>
void split(const string &line, Out result) {
  istringstream iss(line);
  string element;
  char delimiter = ' ';

  while (getline(iss, element, delimiter)) {
    *result++ = stoi(element);

    // comentario
  }
}

Matrix *loadMatrix(string file) {
  Matrix *matrix = new Matrix();
  string line;
  ifstream matrixFile(file);

  cout << "Init load of file '" << file << "' \n";

  if (matrixFile.is_open()) {
    int indexLine = 0;
    cout << "File '" << file << "' opened \n";

    while (getline(matrixFile, line)) {
      indexLine++;

      if (indexLine == 1) { // on line 1 of the file is the size of the matrix
        if (line != "") {
          cout << "Matrix size '" << line << "' \n";

          vector<int> elements;
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
          cout << "Matrix elements '" << line << "' \n";

          vector<int> element;
          split(line, back_inserter(element));

          if ((int)(element.size()) == matrix->getCol()) {
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

  cout << "End load of file '" << file << "' \n\n";

  matrixFile.close();

  return matrix;
}

void writerFileWithMatricesMultiplication(Matrix *matricesProduct, int calculationTimeInNanoSeconds)
{
  cout << "Init writerFileWithMatricesMultiplication \n";

  ofstream matricesProductFile;

  matricesProductFile.open("matricesProduct.txt");
  matricesProductFile << matricesProduct->getCol() << " " << matricesProduct->getRow() << "\n";

  for (int row = 0; row < matricesProduct->getRow(); row++) {
    for (int col = 0; col < matricesProduct->getCol(); col++) {
      matricesProductFile << "c" << row + 1 << col + 1 << " " << matricesProduct->getElementValue(row, col) << "\n";
    }
  }

  matricesProductFile << calculationTimeInNanoSeconds << "\n";

  matricesProductFile.close();

  cout << "End writerFileWithMatricesMultiplication \n";
};

void calculateMatricesMultiplication(Matrix *matrix1, Matrix *matrix2) {
  cout << "Init calculateMatricesMultiplication \n";

  if (matrix1->getCol() == matrix2->getRow()) {
    Matrix *matricesProduct = new Matrix();

    matricesProduct->setRow(matrix1->getRow());
    matricesProduct->setCol(matrix1->getCol());

    for (int row = 0; row < matrix1->getRow(); row++) {
      vector<int> emptyVector;

      for (int col = 0; col < matrix2->getCol(); col++) {
        emptyVector.push_back(0);
      }

      matricesProduct->addElement(emptyVector);
    }

    cout << "Total Matrices Multiplication \n";
    
    steady_clock::time_point beginTime = steady_clock::now();

    for (int row = 0; row < matrix1->getRow(); row++) {
      for (int col = 0; col < matrix2->getCol(); col++) {
        for (int inner = 0; inner < matrix2->getRow(); inner++) {
          int newElementValue = matricesProduct->getElementValue(row, col) + (matrix1->getElementValue(row, inner) * matrix2->getElementValue(inner, col));
          matricesProduct->setElementValue(row, col, newElementValue);
        }
        cout << matricesProduct->getElementValue(row, col) << "  ";
      }
      cout << "\n";
    }

    steady_clock::time_point endTime = steady_clock::now();

    cout << "\n";

    writerFileWithMatricesMultiplication(matricesProduct, duration_cast<nanoseconds>(endTime - beginTime).count());

    cout << "\n";

    delete matricesProduct;
  } else {
    throwException("Runtime error: It's not possible to multiply the matrices, the matrix1 has " + to_string(matrix1->getCol()) + " columns and the matrix2 has " + to_string(matrix2->getRow()) + " rows");
  }

  cout << "End calculateMatricesMultiplication \n";
}



void loadSystem() {
  Matrix *matrix1 = loadMatrix("m1.txt");
  Matrix *matrix2 = loadMatrix("m2.txt");

  calculateMatricesMultiplication(matrix1, matrix2);

  delete matrix1;
  delete matrix2;
}

void writerMatrix(){
  ofstream pArqMatriz1, pArqMatriz2;

  int n1, m1, n2, m2;

  cin >> n1 >> m1 >> n2 >> m2;

  pArqMatriz1.open("m1.txt");
  if (! pArqMatriz1) {
      cout << "Erro ao abrir M1";
      abort();
  }

  pArqMatriz2.open("m2.txt");
  if (! pArqMatriz2) {
      cout << "Erro ao abrir M2";
      abort();
  }

  int M1[n1][m1], M2[n2][m2];

  mt19937 mt(42);
  uniform_real_distribution<float> linear_r(0.f, 100.f);

  for (int i = 0; i < n1; i++){
      for (int j = 0; j < m1; j++) {
          M1[i][j] = linear_r( mt );
      }
  }

  for (int i = 0; i < n2; i++){
      for (int j = 0; j < m2; j++) {
          M2[i][j] = linear_r( mt );
      }
  }

  string aux;

  pArqMatriz1 << n1 << " " << m1 << endl;
  pArqMatriz2 << n2 << " " << m2 << endl;
  

  for (int i = 0; i < n1; i++){
      for (int j = 0; j < m1; j++) {
          pArqMatriz1 << M1[i][j] << " ";
      }
      pArqMatriz1 << "" << endl;
  }

  for (int i = 0; i < n2; i++){
      for (int j = 0; j < m2; j++) {
          pArqMatriz2 << M2[i][j] << " "; 
      }
      pArqMatriz2 << "" << endl;
  }

  pArqMatriz1.close();
  pArqMatriz2.close();

  loadSystem();
}

void listAvailableCommands() {
  cout << "\n:::: Available Commands ::::\n\n";
  cout << "quit                                           Exit the system\n";
  cout << "wm                                             Start write m1 and m2 matrices \n";
  cout << "rsm                                            Start reading and calculating sequentially matrices \n";
  cout << "\n";
}

void initializeProgram() {
  char c;
  char commandLine[10];

  cout << "::::: Welcome to Matrix multiplication sequentially :::::\n\n";
  cout << ":::: Type 'help' to list the available commands ::::\n\n";

  do {
    scanf("%[^\n]", commandLine);
    while ((c = getchar()) != '\n' && c != EOF) {} // Clear buffer

    char *arguments = strtok(commandLine, " ");

    try {
      if (strcmp(arguments, "quit") == 0) {
        cout << "\nBye bye... \n";
        exit(0);
      } else if (strcmp(arguments, "wm") == 0) {
        cout << "\n";
        writerMatrix();
      } else if (strcmp(arguments, "rsm") == 0) {
        cout << "\n";
        loadSystem();
      } else if (strcmp(arguments, "help") == 0) {
        listAvailableCommands();
      } else {
        throw runtime_error("Runtime error: Command not found");
      }
    } catch (const exception& e) {
      cout << "\n:: " << e.what() << " ::\n\n";
    }
  }
  
  while (true);
}