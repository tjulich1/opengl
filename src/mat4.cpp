////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 21 July 2021 */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <cmath>
#include <sstream>

// Included from src.
#include "mat4.hpp"
#include "transformation_builder.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

Mat4::Mat4(float initialValue) 
{
  for (int i = 0; i < 16; i++) {
    values[i] = initialValue;
  }
}

void Mat4::setElement(int col, int row, float value) 
{
  values[row * 4 + col] = value;
}

void Mat4::setRow(int row, GraphicsVec rowValues) {
  // Make sure row is valid.
  if (row >= 0 && row < 4) {
    for (int i = 0; i < 4; i++) {
      values[row * 4 + i] = rowValues.getElement(i);
    }
  }
}

float Mat4::getElement(int col, int row) const {
  float element = 0.0f;
  if (col < 4 && col >= 0 && row < 4 && row >= 0) {
    element = values[row * 4 + col];
  }
  return element;
}

GLfloat* Mat4::getFloats(GLfloat dest[]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dest[i * 4 + j] = values[i * 4 + j];
    }
  }
  return dest;
}

Mat4 Mat4::operator*(const Mat4& other) {
  Mat4 temp;
  // Loop iterates over the rows of the first matrix.
  for (int i = 0; i < 4; i++) {
    // Loop iterates over the columns of the second matrix
    for (int j = 0; j < 4; j++) {
      float sum = 0;
      // Loop for the 4 multiplications that need to be done.
      for (int k = 0; k < 4; k++) {
        sum += getElement(k, i) * other.getElement(j, k);
      }
      temp.setElement(j, i, sum);
    }
  }
  return temp;
}

GraphicsVec Mat4::getRow(int row) const 
{
  if (row < 0 || row > 3) throw std::out_of_range("Invalid row index: " + row);

  return GraphicsVec{
    getElement(0, row),
    getElement(1, row),
    getElement(2, row),
    getElement(3, row)
  };
}

GraphicsVec Mat4::getCol(int column) const
{
  if (column < 0 || column > 3) throw std::out_of_range("Invalid column index: " + column);
  
  return GraphicsVec{
    getElement(column, 0), 
    getElement(column, 1),
    getElement(column, 2),
    getElement(column, 3)
  };
}

std::ostream& operator <<(std::ostream &os, const Mat4& mat) {
  os << "[\n";
  for (int i = 0; i < 4; i++) {
    os << "\t[";
    for (int j = 0; j < 4; j++) {
      os << " " << mat.getElement(j, i);
    }
    os << " ]" << std::endl;
  }
  os << "]";
  return os;
}

////////////////////////////////////////////////////////////////////////////////////////////////////