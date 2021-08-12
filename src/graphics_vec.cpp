////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 7 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cmath>

/**
 * Included from src.
 */
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

GraphicsVec GraphicsVec::normalize() 
{
  // Get the vectors euclidean length
  float length = getEuclideanLength();

  // New vector with same number of elements.
  GraphicsVec normalizedVec(numElements);

  // Divide each element by the length and assign to same index but in the new vector.
  for (int i = 0; i < numElements; i++) {
    normalizedVec.setElement(i, elements[i] / length);
  }

  return normalizedVec;
}

GraphicsVec GraphicsVec::cross(GraphicsVec other) 
{
  GraphicsVec crossVec(3);

  if (numElements == 3 && other.getSize() == 3) {
    crossVec.setX(getY()*other.getZ() - getZ()*other.getY());
    crossVec.setY(getZ()*other.getX() - getX()*other.getZ());
    crossVec.setZ(getX()*other.getY() - getY()-other.getX());
  }

  return crossVec;
}

float GraphicsVec::dot(GraphicsVec other) 
{
  float dot = 0;

  if (other.getSize() == numElements && numElements != 0) {
    for (int i = 0; i < numElements; i++) {
      dot += other.getElement(i) * getElement(i);
    }
  }

  return dot;
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

float GraphicsVec::getEuclideanLength()
{
  // Sum up all square of all elements
  float sum = 0;
  for (int i = 0; i < numElements; i++) {
    // Add current element square to sum.
    sum += pow(elements[i], 2);
  }
  return sqrt(sum);
}

float GraphicsVec::getElement(int index) 
{
  float returnVal = 0;
  if (index >= 0 && index < numElements) {
    returnVal = elements[index];
  }
  return returnVal;
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

void GraphicsVec::setElement(int index, float element) 
{
  if (index >= 0 && index < numElements) {
    elements[index] = element;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////