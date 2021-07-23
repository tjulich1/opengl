// Trent Julich ~ 21 July 2021

#include "custom_math.hpp"

using namespace custom_math;

/**
 * Default constructor, sets all vector values to 0.
 */
Vec4::Vec4() : x(0), y(0), z(0), w(0) {};

/**
 * Constructor which initializes each vector element with the given arguments.
 */
Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {};

/**
 * Constructor which initializes all vector elements with the same value.
 */
Vec4::Vec4(float initialValue) : x(initialValue), y(initialValue), z(initialValue), 
  w(initialValue) {};

/* * * * * * *
 * Mutators  *
 * * * * * * */
void Vec4::setX(float newX) {
  x = newX;
}

void Vec4::setY(float newY) {
  y = newY;
}

void Vec4::setZ(float newZ) {
  z = newZ;
}

void Vec4::setW(float newW) {
  w = newW;
}

/* * * * * * *
 * Accessors *
 * * * * * * */
float Vec4::getX() { return x; }

float Vec4::getY() { return y; }

float Vec4::getZ() { return z; }

float Vec4::getW() { return w; }