#include <vector>

using namespace std;

#ifndef __MATRIX_CLASS_H_
#define __MATRIX_CLASS_H_

class Matrix {
  private:
    size_t col;
    size_t row;
    vector<vector<size_t>> elements;

  public:
    Matrix();
    ~Matrix();

    void setCol(size_t col);
    void setRow(size_t row);
    void setElements(vector<vector<size_t>> elements);
    void setElementValue(size_t row, size_t col, size_t elementValue);

    size_t getCol();
    size_t getRow();
    vector<vector<size_t>> getElements();
    void addElement(vector<size_t> element);
    size_t getElementValue(size_t row, size_t col);
};

#endif