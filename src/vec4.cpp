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
Vec4::Vec4(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {};

/**
 * Constructor which initializes all vector elements with the same value.
 */
Vec4::Vec4(int initialValue) : x(initialValue), y(initialValue), z(initialValue), 
  w(initialValue) {};

/* * * * * * *
 * Mutators  *
 * * * * * * */
void Vec4::setX(int newX) {
  x = newX;
}

void Vec4::setY(int newY) {
  y = newY;
}

void Vec4::setZ(int newZ) {
  z = newZ;
}

void Vec4::setW(int newW) {
  w = newW;
}

/* * * * * * *
 * Accessors *
 * * * * * * */
int Vec4::getX() { return x; }

int Vec4::getY() { return y; }

int Vec4::getZ() { return z; }

int Vec4::getW() { return w; }