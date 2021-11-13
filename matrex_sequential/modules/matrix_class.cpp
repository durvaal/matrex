#include "./headers/matrix_class.h"

Matrix::Matrix(){};
Matrix::~Matrix(){};

void Matrix::setCol(int col) {
  this->col = col;
}
void Matrix::setRow(int row) {
  this->row = row;
}
void Matrix::setElements(vector<int> elements) {
  this->elements = elements;
}

int Matrix::getCol() {
  return this->col;
}
int Matrix::getRow() {
  return this->row;
}
vector <int> Matrix::getElements() {
  return this->elements;
}

void Matrix::addElement(int element) {
  return this->elements.push_back(element);
}