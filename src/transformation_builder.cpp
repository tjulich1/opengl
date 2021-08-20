////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 30 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////

#define _USE_MATH_DEFINES

#include <math.h>

// Included from src.
#include "transformation_builder.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Helper Methods                                                                                 */
//////////////////////////////////////////////////////////////////////////////////////////////////// 

float to_radians(int angleOfRotation) {
  return M_PI / 180 * angleOfRotation;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

Mat4 TransformationBuilder::Identity() {
  Mat4 newVec;
  for (int i = 0; i < 4; i++) {
    newVec.setElement(i, i, 1.0f);
  } 
  return newVec;
}

Mat4 TransformationBuilder::translation(float xTranslate, float yTranslate, float zTranslate) {
  Mat4 translateVec = TransformationBuilder::Identity();
  translateVec.setElement(0, 3, xTranslate);
  translateVec.setElement(1, 3, yTranslate);
  translateVec.setElement(2, 3, zTranslate);
  return translateVec;
}

Mat4 TransformationBuilder::LookAt(GraphicsVec cameraLocation, GraphicsVec viewDirection) {
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

  Mat4 posMat = TransformationBuilder::Identity();
  posMat.setElement(0, 3, -cameraLocation.getX());
  posMat.setElement(1, 3, -cameraLocation.getY());
  posMat.setElement(2, 3, -cameraLocation.getZ());

  Mat4 result = lookAt*posMat;

  return result;
}

Mat4 TransformationBuilder::scale(float xFactor, float yFactor, float zFactor) {
  Mat4 scaleVec;
  scaleVec.setElement(0, 0, xFactor);
  scaleVec.setElement(1, 1, yFactor);
  scaleVec.setElement(2, 2, zFactor);
  scaleVec.setElement(3, 3, 1);
  return scaleVec;
}

Mat4 TransformationBuilder::xRotation(int angleOfRotation) {
  Mat4 rotateVec = TransformationBuilder::Identity();
  float angleInRads =  to_radians(angleOfRotation);
  float rotateCos = cos(angleInRads);
  float rotateSin = sin(angleInRads);

  rotateVec.setElement(1, 1, rotateCos);
  rotateVec.setElement(2, 1, -rotateSin);
  rotateVec.setElement(1, 2, rotateSin);
  rotateVec.setElement(2, 2, rotateCos);

  return rotateVec;
}

Mat4 TransformationBuilder::yRotation(int angleOfRotation) {
  Mat4 rotateVec = TransformationBuilder::Identity();
  float angleInRads = to_radians(angleOfRotation);
  float rotateCos = cos(angleInRads);
  float rotateSin = sin(angleInRads);

  rotateVec.setElement(0, 0, rotateCos);
  rotateVec.setElement(2, 0, rotateSin);
  rotateVec.setElement(0, 2, -rotateSin);
  rotateVec.setElement(2, 2, rotateCos);

  return rotateVec;
}

Mat4 TransformationBuilder::zRotation(int angleOfRotation) {
  Mat4 rotateVec = TransformationBuilder::Identity();
  float angleInRads = to_radians(angleOfRotation);
  float rotateCos = cos(angleInRads);
  float rotateSin = sin(angleInRads);

  rotateVec.setElement(0, 0, rotateCos);
  rotateVec.setElement(1, 0, -rotateSin);
  rotateVec.setElement(0, 1, rotateSin);
  rotateVec.setElement(1, 1, rotateCos);

  return rotateVec;
}

Mat4 TransformationBuilder::rotateFromAxisAngle(int angleOfRotation, GraphicsVec axis) {
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

////////////////////////////////////////////////////////////////////////////////////////////////////