#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <wait.h>
#include <chrono>
#include "./headers/matrix_class.h"
#include "./headers/methods.h"


using namespace std;
using namespace std::chrono;

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

int main(int argc, char const *argv[]) {
    int p = atoi(argv[3]);
    
    fstream file;

    file.open(argv[1]);
    if (!file) {
    cout << "Error opening file" << endl;
    exit(1);
    }

    file.open(argv[2]);
    if (!file) {
    cout << "Error opening file" << endl;
    exit(1);
    }

    size_t arq_number = ceil(n1*m2/p);

    pid_t childProcesses[arq_number];

    for (size_t i = 0; i < arq_number; i++) {
        childProcesses[i] = fork();
        if (childProcesses[i] < 0) {
            cout << "Error creating process" << endl;
            exit(1);
        } else {
            if (childProcesses[i] == 0) {
                vector<int> row, col;
                vector<string> result;
                int count = 0;

                stringstream filename;
                filename << "process_result" << i << ".txt";

                file.open(filename.str(), fstream::out);
                if (!file) {
                    cout << "Error opening file" << endl;
                    exit(1);
                }

                steady_clock::time_point beginTime = steady_clock::now();

                //Coordenadas iniciais da matriz resultado
                size_t x = int(p * i / m2);
                size_t y = (p * i) % m2;

                while (count < p) {
                    int aux = 0;
                    stringstream res;

                    //NECESSÁRIO: pegar a linha da matriz 1 envolvida na multiplicação
                    getRow(x, m1, &matrix1, &row);
                    //NECESSÁRIO: pegar a coluna da matriz 2 envolvida na multiplicação.
                    getCol(n2, y, &matrix2, &col);
                    //Multiplicação
                    for (size_t j = 0; j < m1; j++){
                        aux += col[j] * row[j];
                    }

                    res << "c" << x + 1 << y + 1 << " " << aux << endl;
                    result.push_back(res.str());

                    row.clear();
                    col.clear();

                    count++;
                }

                steady_clock::time_point endTime = steady_clock::now();
                int TimeTotalInNanoSeconds = duration_cast<nanoseconds>(endTime - beginTime).count();

                file << n1 << ' ' << m2 << endl;
                for (size_t j = 0; j < result.size(); j++) {
                    file < result[j];
                }
                file << TimeTotalInNanoSeconds << endl;

                exit(0);
            }
        }
    }

    for (size_t i = 0; i < arq_number; i++) {
        wait(NULL);        
    }

    return 0;
}