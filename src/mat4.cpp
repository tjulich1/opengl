// Trent Julich ~ 21 July 2021

#define _USE_MATH_DEFINES

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
 * Factory method for scaling matrices, used to scale a vector in the x, y, and z directions.
 * 
 * xFactor: scale factor in the x direction.
 * yFactor: scale factor in the y direction.
 * zFactor: scale factor in the z direction.
 */
Mat4 Mat4::Scale(float xFactor, float yFactor, float zFactor) {
  Mat4 scaleVec;
  scaleVec.setElement(0, 0, xFactor);
  scaleVec.setElement(1, 1, yFactor);
  scaleVec.setElement(2, 2, zFactor);
  scaleVec.setElement(3, 3, 1);
  return scaleVec;
}

float to_radians(int angleOfRotation) {
  return M_PI / 180 * angleOfRotation;
}

/**
 * Factory method for constructing rotation matrices used for rotations of angleOfRotation degrees
 * around the x-axis.
 * 
 * angleOfRotation: The angle in degrees to rotate around the x-axis.
 */
Mat4 Mat4::XRotation(int angleOfRotation) {
  Mat4 rotateVec = Mat4::Identity();
  float angleInRads =  to_radians(angleOfRotation);
  float rotateCos = cos(angleInRads);
  float rotateSin = sin(angleInRads);

  rotateVec.setElement(1, 1, rotateCos);
  rotateVec.setElement(2, 1, -rotateSin);
  rotateVec.setElement(1, 2, rotateSin);
  rotateVec.setElement(2, 2, rotateCos);

  return rotateVec;
}

/**
 * Factory method for constructing rotation matrices used for rotations of angleOfRotation degrees
 * around the y-axis.
 * 
 * angleOfRotation: The angle in degrees to rotate around the y-axis.
 */
Mat4 Mat4::YRotation(int angleOfRotation) {
  Mat4 rotateVec = Mat4::Identity();
  float angleInRads = to_radians(angleOfRotation);
  float rotateCos = cos(angleInRads);
  float rotateSin = sin(angleInRads);

  rotateVec.setElement(0, 0, rotateCos);
  rotateVec.setElement(2, 0, rotateSin);
  rotateVec.setElement(0, 2, -rotateSin);
  rotateVec.setElement(2, 2, rotateCos);

  return rotateVec;
}

/**
 * Factory method for constructing rotation matrices used for rotations of angleOfRotation degrees
 * around the z-axis.
 * 
 * angleOfRotation: The angle in degrees to rotate around the z-axis.
 */
Mat4 Mat4::ZRotation(int angleOfRotation) {
  Mat4 rotateVec = Mat4::Identity();
  float angleInRads = to_radians(angleOfRotation);
  float rotateCos = cos(angleInRads);
  float rotateSin = sin(angleInRads);

  rotateVec.setElement(0, 0, rotateCos);
  rotateVec.setElement(1, 0, -rotateSin);
  rotateVec.setElement(0, 1, rotateSin);
  rotateVec.setElement(1, 1, rotateCos);

  return rotateVec;
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
float Mat4::getElement(int col, int row) const {
  float element = 0.0f;
  if (col < 4 && col >= 0 && row < 4 && row >= 0) {
    element = values[row * 4 + col];
  }
  return element;
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