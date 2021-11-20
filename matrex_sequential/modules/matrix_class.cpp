#include "./headers/matrix_class.h"

Matrix::Matrix(){};
Matrix::~Matrix(){};

void Matrix::setCol(int col) {
  this->col = col;
}
void Matrix::setRow(int row) {
  this->row = row;
}
void Matrix::setElements(vector<vector<int>> elements){
  this->elements = elements;
}
void Matrix::setElementValue(int row, int col, int elementValue){
  this->elements[row][col] = elementValue;
}

int Matrix::getCol() {
  return this->col;
}
int Matrix::getRow() {
  return this->row;
}
vector<vector<int>> Matrix::getElements(){
  return this->elements;
}
int Matrix::getElementValue(int row, int col){
  return this->elements[row][col];
}

void Matrix::addElement(vector<int> element){
  this->elements.push_back(element);
}