// Trent Julich ~ 21 July 2021

#include "custom_math.hpp"

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

/**
 * Factory method for identity matrix, which is a 4x4 matrix with 1.0f along the diagonal (starting at 
 * the top left, ending at bottom right).
 */
Mat4 Mat4::Identity() {
  Mat4 newVec;
  for (int i = 0; i < 4; i++) {
    newVec.setElement(i, i, 1.0f);
  } 
  return newVec;
}

/**
 * Factory method for translation matrices, used to translate a vecor in space.
 * 
 * xTranslate: the value to translate x by.
 * yTranslate: the value to translate y by.
 * zTranslate: the value to translate z by.
 * 
 * returns: matrix used to translate a 4D vector in space by the given values.
 */
Mat4 Mat4::Translation(float xTranslate, float yTranslate, float zTranslate) {
  Mat4 translateVec = Mat4::Identity();
  translateVec.setElement(3, 0, xTranslate);
  translateVec.setElement(3, 1, yTranslate);
  translateVec.setElement(3, 2, zTranslate);
  return translateVec;
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
 * Returns the element located at (col, row) in the matrix.
 * 
 * col: column of element to access.
 * row: row of element to access.
 * 
 * returns: element in the desired location in the matrix. Returns 0 if index is outside of matrix
 * bounds.
 */ 
float Mat4::getElement(int col, int row) {
  float element = 0.0f;
  if (col < 4 && col >= 0 && row < 4 && row >= 0) {
    element = values[row * 4 + col];
  }
  return element;
}