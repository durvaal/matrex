#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <wait.h>
#include <unistd.h>
#include <chrono>
#include <math.h>
#include "./headers/common_methods.h"

using namespace std;
using namespace std::chrono;

void calcProcess(char *arguments) {
  string matrixFileM1 = convertCharToString(strtok(NULL, " "));
  string matrixFileM2 = convertCharToString(strtok(NULL, " "));
  size_t p = convertCharToInt(strtok(NULL, " "));

  fstream file;

  Matrix *matrix1 = loadMatrix(matrixFileM1);
  Matrix *matrix2 = loadMatrix(matrixFileM2);

  size_t process_number = ceil(matrix1->getRow()*matrix2->getCol()/p);

  pid_t childProcesses[process_number];

  for (size_t i = 0; i < process_number; i++) {
    childProcesses[i] = fork();
    if (childProcesses[i] < 0) {
      throwException("Error creating process");
      exit(1);
    } else {
      if (childProcesses[i] == 0) {
        vector<size_t> row, col;
        vector<string> result;
        size_t count = 0;

        stringstream filename;
        filename << "./process-files/process_result" << i << ".txt";

        file.open(filename.str(), fstream::out);
        if (!file) {
          throwException("Error opening file");
          exit(1);
        }

        steady_clock::time_point beginTime = steady_clock::now();

        size_t targetRow = size_t(p * i / matrix2->getCol());
        size_t targetCol = (p * i) % matrix2->getCol();

        while (count < p) {
          size_t aux = 0;
          stringstream res;

           getRowInterval(targetRow, matrix1->getCol(), matrix1, &row);
           getColInterval(targetCol, matrix2->getRow(), matrix2, &col);
          for (size_t j = 0; j < (size_t)matrix1->getCol(); j++){
            aux += col[j] * row[j];
          }

          res << "c" << targetRow + 1 << targetCol + 1 << " " << aux << endl;
          result.push_back(res.str());

          row.clear();
          col.clear();

          count++;
          targetCol++;

          if (targetCol >= matrix2->getCol()) {
            targetRow++;
            targetCol = (p * i) % matrix2->getCol();
          }
        }

        steady_clock::time_point endTime = steady_clock::now();
        size_t TimeTotalInNanoSeconds = duration_cast<nanoseconds>(endTime - beginTime).count();

        file << matrix1->getRow() << ' ' << matrix2->getCol() << endl;

        for (size_t j = 0; j < result.size(); j++) {
          file << result[j];
        }

        file << TimeTotalInNanoSeconds << endl;
        file.close();

        exit(0);
      }
    }
  }

  for (size_t i = 0; i < process_number; i++) {
    wait(NULL);
  }

  cout << "Calculated process matrices with success \n\n";
}