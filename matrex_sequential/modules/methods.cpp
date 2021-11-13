#include <stdio.h>
#include <sstream>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "./headers/matrix_class.h"
#include "./headers/methods.h"

using namespace std;

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

          vector<int> elements;
          split(line, back_inserter(elements));

          if ((int)(elements.size()) == (matrix->getCol() * matrix->getRow())) {
            matrix->setElements(elements);
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

// TODO
void calculateMatrix(Matrix *matrix1, Matrix *matrix2) {
  
}

void loadSystem() {
  Matrix *matrix1 = loadMatrix("m1.txt");
  Matrix *matrix2 = loadMatrix("m2.txt");

  calculateMatrix(matrix1, matrix2);

  delete matrix1;
  delete matrix2;
}

void listAvailableCommands() {
  cout << "\n:::: Available Commands ::::\n\n";
  cout << "quit                                           Exit the system\n";
  cout << "init                                           Start reading and calculating matrices \n";
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
      } else if (strcmp(arguments, "init") == 0) {
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