////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 21 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////

#include <math.h>

/**
 * Headers from src.
 */
#include "custom_math.hpp"

using namespace custom_math;

////////////////////////////////////////////////////////////////////////////////////////////////////

Vec4::Vec4() 
{
  for (int i = 0; i < MAX_ELEMENTS; i++) {
    values[i] = 0;
  }
}

Vec4::Vec4(float x, float y, float z, float w) 
{
  values[0] = x;
  values[1] = y;
  values[2] = z;
  values[3] = w;
}

Vec4::Vec4(float initialValue) 
{
  for (int i = 0; i < MAX_ELEMENTS; i++) {
    values[i] = initialValue;
  }
}

Vec4 Vec4::copy() 
{
  Vec4 theCopy(values[0], values[1], values[2], values[3]);
  return theCopy;
}

Vec4 Vec4::cross(Vec4 other) {
  float x = getY()*other.getZ() - getZ()*other.getY();
  float y = getZ()*other.getX() - getX()*other.getZ();
  float z = getX()*other.getY() - getY()*other.getX();
  return Vec4(x, y, z, 0);
}

void Vec4::normalize() {
  float length =sqrt(values[0]*values[0] + values[1]*values[1] + values[2]*values[2]);
  values[0] = values[0] / length;
  values[1] = values[1] / length;
  values[2] = values[2] / length;
}

////////////////////////////////////////////////////////////////////////////////////////////////////