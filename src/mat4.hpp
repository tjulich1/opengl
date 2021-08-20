////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 21 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>
#include <gl/GL.h>
#include <string>

// Included from src.
#include "graphics_vec.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

class GraphicsVec;

/**
 * Class representing a 4x4 matrix used for transformations in graphics programming.
 */
class Mat4 
{
public:
  /**
   * Constructor for new Mat4, takes an initial value. If none is provided, 0 will be used.
   */
  Mat4(float initialValue = 0.0f);
  
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
  GraphicsVec getCol(int column) const;

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