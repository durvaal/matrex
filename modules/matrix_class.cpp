#include "./headers/matrix_class.h"

Matrix::Matrix(){};
Matrix::~Matrix(){};

void Matrix::setCol(size_t col) {
  this->col = col;
}
void Matrix::setRow(size_t row) {
  this->row = row;
}
void Matrix::setElements(vector<vector<size_t>> elements){
  this->elements = elements;
}
void Matrix::setElementValue(size_t row, size_t col, size_t elementValue){
  this->elements[row][col] = elementValue;
}

size_t Matrix::getCol() {
  return this->col;
}
size_t Matrix::getRow() {
  return this->row;
}
vector<vector<size_t>> Matrix::getElements(){
  return this->elements;
}
size_t Matrix::getElementValue(size_t row, size_t col){
  return this->elements[row][col];
}

void Matrix::addElement(vector<size_t> element){
  this->elements.push_back(element);
}