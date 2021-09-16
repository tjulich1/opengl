////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 7 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// Included from src.
#include "mat4.hpp"

#include <stdexcept>
#include <ostream>
#include <vector>

////////////////////////////////////////////////////////////////////////////////////////////////////

class Mat4;

/**
 * Class adding operations to vector that are needed for graphics transformations.
 */
class GraphicsVec 
{
public:

  /**
   * Constructor which takes the size of the desired vector.
   * 
   * @param size The number of elements to put in vector.
   */
  GraphicsVec(int size = 0);

  /**
   * Constructor for 3D vector, taking intial values for each element.
   * 
   * @param x
   * @param y
   * @param z
   */
  GraphicsVec(float x, float y, float z);

  /**
   * Constructor for 4D vector, taking initial values for each element.
   * 
   * @param x The initial value for the first vector element.
   * @param y The initial value for the second vector element.
   * @param z The initial value for the third vector element.
   * @param w The initial value for the fourth vector element.
   */
  GraphicsVec(float x, float y, float z, float w);

  /**
   * Creates and normalizes a new vector using this vectors values (converts to unit vector). 
   * 
   * @returns Normalized version of vector method is called on.
   */
  GraphicsVec normalize();

  /**
   * Computes the cross product between the vector having the method called (on the left) and 
   * "other" on the right.
   * 
   * @param other The vector on the right hand side of the cross product.
   * @returns The resulting vector from the cross product, or empty vector for non-3D vectors.
   */
  GraphicsVec cross(GraphicsVec other);

  /**
   * Multiplies this vector on the left side of a 4x4 matrix. Will only succeed for vectors of 
   * length 4.
   * 
   * @param theMatrix The matrix to multiply against the vector.
   * 
   * @returns Vector containing the result of the multiplication, or an empty vector.
   */
  GraphicsVec operator*(const Mat4& theMatrix);

  /**
   * Computes the dot product between two vectors of the same size.
   * 
   * @param other The other vector to include in the dot product.
   * 
   * @returns Dot product of two vectors, or zero if mismatched sizes or empty.
   */
  float dot(GraphicsVec other);

  /**
   * Method used to get the size of the vector.
   * 
   * @returns The number of elements this vector holds.
   */
  int getSize() const { return numElements; }

  /**
   * Accesses the vector element corresponding to its x component. Vector must have size at least 
   * 1 to access x element.
   *
   * @returns x component of vector. 
   */
  float getX()
  {
    if (numElements >= 1) return elements[0];
    throw std::out_of_range("Cannot access x element of empty vector.");
  }

  /**
   * Accesses the vector element corresponding to its y component. Vector must have size at least 
   * 2 to access y element.
   *
   * @returns y component of vector. 
   */
  float getY() 
  {
    if (numElements >= 2) return elements[1];
    throw std::out_of_range("Cannot access y element of vector without at least 2 elements: num=" 
      + numElements);
  }

  /**
   * Accesses the vector element corresponding to its z component. Vector must have size at least 
   * 3 to access z element.
   *
   * @returns z component of vector. 
   */
  float getZ() 
  {
    if (numElements >= 3) return elements[2];
    throw std::out_of_range("Cannot access z element of vector without at least 3 elements: num="
      + numElements);
  }

  /**
   * Accesses the vector element corresponding to its w component. Vector must have size at least 
   * 4 to access w element.
   *
   * @returns w component of vector. 
   */
  float getW() 
  {
    if (numElements >= 4) return elements[3];
    throw std::out_of_range("Cannot access w element of vector without at least 4 lements: num=" 
      + numElements);
  }

  /**
   * Used access the euclidean length of the vector, or the square root of the sum of each element
   * squared.
   * 
   * @returns The euclidean length of the vector.
   */
  float getEuclideanLength();

  /**
   * Used to access an element by index, as long as index within [0, numElements-1] inclusive.
   * 
   * @param index Index of element to access.
   * @returns The element at given index, or arbitrary value.
   */
  float getElement(int index) const;

  /**
   * Method used to assign a new value to the vectors x component. Vector must have size at least 1.
   * 
   * @param newX The value to assign to the x component.
   */
  void setX(float newX);

  /**
   * Method used to assign a new value to the vectors y component. Vector must have size at least 2.
   * 
   * @param newY The value to assign to the y component.
   */
  void setY(float newY);
  
  /**
   * Method used to assign a new value to the vectors z component. Vector must have size at least 3.
   * 
   * @param newZ The value to assign to the z component.
   */
  void setZ(float newZ);

  /**
   * Method used to assign a new value to the vectors w component. Vector must have size at least 4.
   * 
   * @param newW The value to assign to the w component.
   */
  void setW(float newW);

  /**
   * Method used to assign an element by index. No changes to elements are made if index is outside 
   * of range [0, numElements-1] inclusive.
   * 
   * @param index The index within vector of the element to assign value to.
   * @param element The value assigned to the given index.
   */
  void setElement(int index, float element);

private:

  /**
   * Number of elements in the vector.
   */
  int numElements;

  /**
   * Vector that holds the 
   */
  std::vector<float> elements; 
};

/**
 * Override of the << operator, used to write a representation of the vector to the output stream.
 * 
 * @param vec Vector to print to output.
 * @param stream Output stream to write to.
 */
std::ostream& operator<< (std::ostream& stream, const GraphicsVec& vec);

////////////////////////////////////////////////////////////////////////////////////////////////////