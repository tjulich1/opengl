// Trent Julich ~ 21 July 2021

#include "custom_math.hpp"

using namespace custom_math;

/**
 * Default constructor, sets all vector values to 0.
 */
Vec4::Vec4() {
  for (int i = 0; i < MAX_ELEMENTS; i++) {
    values[i] = 0;
  }
}

/**
 * Constructor which initializes each vector element with the given arguments.
 */
Vec4::Vec4(float x, float y, float z, float w) {
  values[0] = x;
  values[1] = y;
  values[2] = z;
  values[3] = w;
}

/**
 * Constructor which initializes all vector elements with the same value.
 */
Vec4::Vec4(float initialValue) {
  for (int i = 0; i < MAX_ELEMENTS; i++) {
    values[i] = initialValue;
  }
}

/* * * * * * *
 * Mutators  *
 * * * * * * */
void Vec4::setX(float newX) {
  values[0] = newX;
}

void Vec4::setY(float newY) {
  values[1] = newY;
}

void Vec4::setZ(float newZ) {
  values[2] = newZ;
}

void Vec4::setW(float newW) {
  values[3] = newW;
}

/* * * * * * *
 * Accessors *
 * * * * * * */
float Vec4::getX() { return values[0]; }

float Vec4::getY() { return values[1]; }

float Vec4::getZ() { return values[2]; }

float Vec4::getW() { return values[3]; }

float Vec4::getElement(int element) {
  float result = 0;
  if (element >= 0 && element < 4) {
    result = values[element];
  }
  return result;
}