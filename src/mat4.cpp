// Trent Julich ~ 21 July 2021



#include "custom_math.hpp"
#include <math.h>
#include <cmath>
#include <sstream>

using namespace custom_math;

/**
 * Default constructor, initializes each value to zero.
 */
Mat4::Mat4() {
  for (int i = 0; i < 16; i++) {
    values[i] = 0.0f;
  }
}

/**
 * Constructor which sets each element in the matrix to the same initial value.
 */
Mat4::Mat4(float initialValue) {
  for (int i = 0; i < 16; i++) {
    values[i] = initialValue;
  }
}


Mat4 Mat4::Identity() {
  Mat4 newVec;
  for (int i = 0; i < 4; i++) {
    newVec.setElement(i, i, 1.0f);
  } 
  return newVec;
}

/**
 * Generates a Mat4 which moves the camera to cameraLocation, and points it towards viewDirection.
 */
Mat4 Mat4::LookAt(Vec4 cameraLocation, Vec4 viewDirection) {
  // Vector in direction cam is pointing.
  float x = cameraLocation.getX() - viewDirection.getX();
  float y = cameraLocation.getY() - viewDirection.getY();
  float z = cameraLocation.getZ() - viewDirection.getZ();

  Vec4 forward(x, y, z, 0);
  forward.normalize();

  // Temp vec used to calculate right vector.
  Vec4 temp(0, 1, 0, 0);
  Vec4 right = temp.cross(forward);

  Vec4 up = forward.cross(right);
  up.normalize();

  Mat4 lookAt;
  lookAt.setRow(0, right);
  lookAt.setRow(1, up);
  lookAt.setRow(2, forward);
  lookAt.setElement(3, 3, 1);

  Mat4 posMat = Identity();
  posMat.setElement(3, 0, -cameraLocation.getX());
  posMat.setElement(3, 1, -cameraLocation.getY());
  posMat.setElement(3, 2, -cameraLocation.getZ());

  Mat4 result = lookAt*posMat;

  return result;
}

/**
 * Sets the element at (col, row) in the matrix to the given value.
 *
 * col: column of the element to set.
 * row: row of the element to set.
 * value: the value to assign to the matrix.
 */
void Mat4::setElement(int col, int row, float value) {
  values[row * 4 + col] = value;
}

/**
 * Sets desired row of matrix to the values of the given vector. Makes no changes if the row is not 
 * within [0, 3].
 */
void Mat4::setRow(int row, Vec4 rowValues) {
  // Make sure row is valid.
  if (row >= 0 && row < 4) {
    for (int i = 0; i < 4; i++) {
      values[row * 4 + i] = rowValues.getElement(i);
    }
  }
}

/**
 * Returns the element located at (col, row) in the matrix.
 * 
 * col: column of element to access.
 * row: row of element to access.
 * 
 * returns: element in the desired location in the matrix. Returns 0 if index is outside of matrix
 * bounds.
 */ 
float Mat4::getElement(int col, int row) const {
  float element = 0.0f;
  if (col < 4 && col >= 0 && row < 4 && row >= 0) {
    element = values[row * 4 + col];
  }
  return element;
}

/**
 * Takes a float array and writes the contents of the matrix to it. Contents are written in order of 
 * row.
 * 
 * dest: the array to write the elements to.
 * 
 * returns: pointer to array that was passed in.
 */
GLfloat* Mat4::getFloats(GLfloat dest[]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      dest[i * 4 + j] = values[i * 4 + j];
    }
  }
  return dest;
}

/**
 * Override of the * operator. When used, it will return the product of the matrix multiplication 
 * with "other" matrix being on the right hand side.
 */
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

/**
 * Override of << Operator. Used to output a representation of a matrix to the given output stream.
 */
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