////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 21 July 2021 */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>
#include <cmath>
#include <sstream>

// Included from src.
#include "mat4.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

Mat4::Mat4(float initialValue) {
  for (int i = 0; i < 16; i++) {
    values[i] = 0.0f;
  }
}

Mat4 Mat4::Identity() {
  Mat4 newVec;
  for (int i = 0; i < 4; i++) {
    newVec.setElement(i, i, 1.0f);
  } 
  return newVec;
}

Mat4 Mat4::LookAt(GraphicsVec cameraLocation, GraphicsVec viewDirection) {
  // Vector in direction cam is pointing.
  float x = cameraLocation.getX() - viewDirection.getX();
  float y = cameraLocation.getY() - viewDirection.getY();
  float z = cameraLocation.getZ() - viewDirection.getZ();

  // Viewing plane normal.
  GraphicsVec forward(x, y, z, 0);
  forward.normalize();

  // Normal vector pointing up along the y axis.
  GraphicsVec temp(0, 1, 0, 0);

  // U vector
  GraphicsVec right = temp.cross(forward);

  Mat4 lookAt;
  lookAt.setRow(0, right);
  lookAt.setRow(1, temp);
  lookAt.setRow(2, forward);
  lookAt.setElement(3, 3, 1);

  Mat4 posMat = Identity();
  posMat.setElement(0, 3, -cameraLocation.getX());
  posMat.setElement(1, 3, -cameraLocation.getY());
  posMat.setElement(2, 3, -cameraLocation.getZ());

  Mat4 result = lookAt*posMat;

  return result;
}

void Mat4::setElement(int col, int row, float value) {
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