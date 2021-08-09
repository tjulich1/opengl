////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 7 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "graphics_vec.hpp"

GraphicsVec::GraphicsVec() 
{
  numElements = 0;
}

GraphicsVec::GraphicsVec(int size) 
{
  numElements = size;
  elements = std::vector<float>(size);
  for (int i = 0; i < numElements; i++) {
    elements[i] = 0;
  }
}

GraphicsVec::GraphicsVec(float x, float y, float z) 
{
  numElements = 3;
  elements = std::vector<float>(numElements);
  elements[0] = x;
  elements[1] = y;
  elements[2] = z;
}

GraphicsVec::GraphicsVec(float x, float y, float z, float w) 
{
  numElements = 4;
  elements = std::vector<float>(numElements);
  elements[0] = x;
  elements[1] = y;
  elements[2] = z;
  elements[3] = w;
}

int GraphicsVec::getSize() { return numElements; }

float GraphicsVec::getX()
{
  float x = -1;
  if (numElements >= 1) {
    x = elements[0];
  }
  return x;
}

float GraphicsVec::getY() 
{
  float y = -1;
  if (numElements >= 2) {
    y = elements[1];
  }
  return y;
}

float GraphicsVec::getZ()
{
  float z = -1;
  if (numElements >= 3) {
    z = elements[2];
  } 
  return z;
}

float GraphicsVec::getW()
{
  float w = -1;
  if (numElements >= 4) {
    w = elements[3];
  }
  return w;
}

void GraphicsVec::setX(float newX) 
{
  if (numElements >= 1) {
    elements[0] = newX;
  }
}

void GraphicsVec::setY(float newY) 
{
  if (numElements >= 2) {
    elements[1] = newY;
  }
}

void GraphicsVec::setZ(float newZ)
{
  if (numElements >= 3) {
    elements[2] = newZ;
  }
}

void GraphicsVec::setW(float newW) 
{
  if (numElements >= 4) {
    elements[3] = newW;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////