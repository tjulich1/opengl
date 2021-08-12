////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 21 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <gl/GL.h>
#include <string>

/**
 * Included from src.
 */
#include "graphics_vec.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////
class Mat4;

/**
 * Class representing a 4x4 matrix used for transformations in graphics programming.
 */
class Mat4 
{
public:
  /**
   * Default constructor, initializes all matrix elements to zero.
   */
  Mat4();

  /**
   * Constructor which sets all elements of the matrix to the same value.
   * 
   * initialValue: The value to initialize the matrix with.
   */
  Mat4(float initialValue);
  
  /**
   * Factory method used to generate Identity matrices, or matrices with the value 1 along the 
   * diagonal (from top left to bottom right).
   */
  static Mat4 Identity();
  
  /**
   * Factory method used to generate LookAt matrices. When this matrix is multiplied with a model 
   * matrix, it converts the models world coordinates to camera space.
   * 
   * return: Mat4 encoding the lookat transformation.
   */
  static Mat4 LookAt(GraphicsVec cameraPosition, GraphicsVec viewDirection);

  /**
   * Sets a single element within the Mat4.
   * 
   * col:   Column of element to set.
   * row:   Row of element to set.
   * value: The value to assign to the element.
   */
  void setElement(int col, int row, float value);
  
  /**
   * Sets an entire row of the Mat4 using values from a GraphicsVec.
   * 
   * row:       The row to set.
   * rowValues: GraphicsVec containing values to assign to elements.
   */
  void setRow(int row, GraphicsVec rowValues);

  /**
   * Retrieves an element from the Mat4.
   * 
   * col: Column of element to retrieve.
   * row: Row of element to retrieve.
   */
  float getElement(int col, int row) const;

  /**
   * Fills an array with the values stored in the Mat4.
   * 
   * dest: GLfloat array to store the values into.
   */
  GLfloat* getFloats(GLfloat dest[]);

  /**
   * Accesses a column within range [0, 3] and returns it as a vector.
   */
  inline GraphicsVec getCol(int column) const
  {
    GraphicsVec result(0);
    
    if (column >= 0 && column <= 3) {
      result.setX(getElement(column, 0));
      result.setY(getElement(column, 1));
      result.setZ(getElement(column, 2));
      result.setW(getElement(column, 3));
    }

    return result;
  }

  /**
   * Override of the * operator. When used, it will perform matrix multiplication between the 
   * two matrices.
   * 
   * other: The other matrix to multiply with.
   */
  Mat4 operator*(const Mat4& other);

private:
  /**
   * Array containing the float values of the 4x4 matrix.  
   */
  float values[16];
};


/**
 * Override of the << operator, used to put a representation of the Mat4 to the output stream.
 * 
 * matrix: Matrix to print to output.
 * stream: Output stream to write to.
 */
std::ostream& operator<< (std::ostream& stream, const Mat4& matrix);

////////////////////////////////////////////////////////////////////////////////////////////////////