#include <vector>

using namespace std;

#ifndef __MATRIX_CLASS_H_
#define __MATRIX_CLASS_H_

class Matrix {
  private:
    int col;
    int row;
    vector<int> elements;

  public:
    Matrix();
    ~Matrix();

    void setCol(int col);
    void setRow(int row);
    void setElements(vector<int> elements);

    int getCol();
    int getRow();
    vector<int> getElements();
    void addElement(int element);
};

#endif