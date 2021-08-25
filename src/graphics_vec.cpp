////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 7 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

// Included from src.
#include "custom_exceptions.hpp"

#include <cmath>
#include <stdexcept>

// Temp
#include <iostream>

/**
 * Included from src.
 */
#include "graphics_vec.hpp"

GraphicsVec::GraphicsVec(int size) 
{
  if (size < 0) {
    throw std::invalid_argument("Cannot construct vector with negative size.");
  } 
  numElements = size;
  if (size != 0) {
    elements = std::vector<float>(size);
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
  if (numElements <= 0) {
    throw InvalidOperationException(std::string("Cannot normalize vector with less than one element."));
  }

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
    crossVec.setX((getY()*other.getZ()) - (getZ()*other.getY()));
    crossVec.setY((getZ()*other.getX()) - (getX()*other.getZ()));
    crossVec.setZ((getX()*other.getY()) - (getY()*other.getX()));
  }

  return crossVec;
}

GraphicsVec GraphicsVec::operator*(const Mat4& theMatrix) 
{
  GraphicsVec result(0);
  
  if (numElements == 4) {
    result = GraphicsVec(4);
    for (int i = 0; i < 4; i++) {
      GraphicsVec currentColumn = theMatrix.getCol(i);
      result.setElement(i, dot(currentColumn));
    }
  }

  return result;
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

float GraphicsVec::getElement(int index) const
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