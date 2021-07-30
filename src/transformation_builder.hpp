// Trent Julich ~ 30 July 2021

#ifndef TRANSFORMATION_BUILDER_HPP
#define TRANSFORMATION_BUILDER_HPP

#include "custom_math.hpp"

using namespace custom_math;

class TransformationBuilder {

public:
  TransformationBuilder();

  Mat4 translation(float xTranslate, float yTranslate, float zTranslate);
  Mat4 scale(float xFactor, float yFactor, float zFactor);
  Mat4 xRotation(int angleOfRotation);
  Mat4 yRotation(int angleOfRotation);
  Mat4 zRotation(int angleOfRotation);
  Mat4 rotateFromAxisAngle(int angleOfRotation, Vec4 axis);

private: 
  Mat4 identity;
};

#endif