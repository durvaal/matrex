#include <stdio.h>
#include <string.h>
#include <iostream>
#include "./modules/headers/create_matrix.h"
#include "./modules/headers/sequential.h"
#include "./modules/headers/threads.h"
#include "./modules/headers/process.h"

void initializeProgram() {
  char c;
  char commandLine[100];

  cout << "::::: Welcome to Matrex :::::\n\n";

  do {
    scanf("%[^\n]", commandLine);

    while ((c = getchar()) != '\n' && c != EOF) {} // Clear buffer

    char *arguments = strtok(commandLine, " ");

    try {
      if (strcmp(arguments, "quit") == 0) {
        cout << "\nBye bye... \n";
        exit(0);
      } else if (strcmp(arguments, "write") == 0) {
        cout << "\n";
        writerMatrix(arguments);
      } else if (strcmp(arguments, "sequential") == 0) {
        cout << "\n";
        handleMatricesSequentially(arguments);
      } else if (strcmp(arguments, "threads") == 0) {
        cout << "\n";
        calcThreads(arguments);
      } else if (strcmp(arguments, "process") == 0) {
        cout << "\n";
        calcProcess(arguments);
      } else {
        throw runtime_error("Runtime error: Command not found");
      }
    } catch (const exception& e) {
      cout << "\n:: " << e.what() << " ::\n\n";
    }
  } while (true);
}

int main() {
  cout << "\n:::: Available Commands ::::\n\n";
  cout << "quit                                           Exit the system\n";
  cout << "write [row1] [col1] [row2] [col2]              Start write m1 and m2 matrices \n";
  cout << "sequential [file1] [file2]                     Start sequential matrix calculation \n";
  cout << "threads [file1] [file2] [p]                    Start calculation with matrix threads \n";
  cout << "process [file1] [file2] [p]                    Start calculation with matrix processes \n";
  cout << "\n";

  initializeProgram();
}