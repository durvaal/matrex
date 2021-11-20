#include <vector>

using namespace std;

#ifndef __MATRIX_CLASS_H_
#define __MATRIX_CLASS_H_

class Matrix {
  private:
    int col;
    int row;
    vector<vector<int>> elements;

  public:
    Matrix();
    ~Matrix();

    void setCol(int col);
    void setRow(int row);
    void setElements(vector<vector<int>> elements);
    void setElementValue(int row, int col, int elementValue);

    int getCol();
    int getRow();
    vector<vector<int>> getElements();
    void addElement(vector<int> element);
    int getElementValue(int row, int col);
};

#endif