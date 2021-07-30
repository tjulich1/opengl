// Trent Julich ~ 30 July 2021

#include "transformation_builder.hpp"

#define _USE_MATH_DEFINES

#include <math.h>

TransformationBuilder::TransformationBuilder() {
  identity = Mat4::Identity();
}

/**
 * Factory method for translation matrices, used to translate a vector in space.
 * 
 * xTranslate: the value to translate x by.
 * yTranslate: the value to translate y by.
 * zTranslate: the value to translate z by.
 * 
 * returns: matrix used to translate a 4D vector in space by the given values.
 */
Mat4 TransformationBuilder::translation(float xTranslate, float yTranslate, float zTranslate) {
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
Mat4 TransformationBuilder::scale(float xFactor, float yFactor, float zFactor) {
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
Mat4 TransformationBuilder::xRotation(int angleOfRotation) {
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
Mat4 TransformationBuilder::yRotation(int angleOfRotation) {
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
Mat4 TransformationBuilder::zRotation(int angleOfRotation) {
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
 * Factory method for constructing matrices used for rotations around any desired axis.
 * 
 * angleOfRotation: the angle in degrees to rotate the vertex.
 * axis: the axis to rotate around. Only the first 3 elements in the vector are used, and are first
 * normalized to a unit vector.
 */
Mat4 TransformationBuilder::rotateFromAxisAngle(int angleOfRotation, Vec4 axis) {
  Mat4 rotate;

  float angleInRads = to_radians(angleOfRotation);
  float x = axis.getX();
  float y = axis.getY();
  float z= axis.getZ();

  float length = sqrt(x*x + y*y + z*z);
  x /= length;
  y /= length;
  z /= length;

  float angleCos = cos(angleInRads);
  float angleSin = sin(angleInRads);
  float oneMinusCos = 1 - angleCos;

  // First row elements.
  rotate.setElement(0, 0, angleCos + x*x*oneMinusCos);
  rotate.setElement(1, 0, x*y*oneMinusCos - z*angleSin);
  rotate.setElement(2, 0, x*z*oneMinusCos + y*angleSin);
  
  // Second row elements
  rotate.setElement(0, 1, y*x*oneMinusCos + z*angleSin);
  rotate.setElement(1, 1, angleCos + y*y*oneMinusCos);
  rotate.setElement(2, 1, y*z*oneMinusCos - x*angleSin);

  // Third row elements.
  rotate.setElement(0, 2, z*x*oneMinusCos - y*angleSin);
  rotate.setElement(1, 2, z*y*oneMinusCos + x*angleSin);
  rotate.setElement(2, 2, angleCos + z*z*oneMinusCos);

  // Set bottom right to 1.
  rotate.setElement(3, 3, 1);

  return rotate;
}