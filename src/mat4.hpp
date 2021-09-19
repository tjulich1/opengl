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
   * 
   * @param initialValue An optional initial value used to initialize each element of the matrix. 
   */
  Mat4(float initialValue = 0.0f);
  
  /**
   * Sets a single element within the Mat4.
   * 
   * @param col column of element to set.
   * @param row row of element to set.
   * @param value value to assign to the element.
   */
  void setElement(int col, int row, float value);
  
  /**
   * Sets an entire row of the Mat4 using values from a GraphicsVec. If < 4 values are given, the 
   * given values will be written to the beginning of the row. If > 4 values are given, only the 
   * first 4 are used.
   * 
   * @param row the row to set.
   * @param rowValues a vector containing values to assign to the matrix row.
   * @throws out_of_range error if row is out of index range.
   */
  void setRow(int row, GraphicsVec rowValues);

  /**
   * Retrieves an element from the Mat4 based on indices of row and col. Both indices must be within
   * [0, 3] inclusive.
   * 
   * @param col column of element to retrieve.
   * @param row row of element to retrieve.
   * @throws out_of_range exception if either col or row are out of valid range.
   * @return the matrix value located at the desired location.
   */
  float getElement(int col, int row) const;

  /**
   * Fills an array with the values stored in the Mat4.
   * 
   * @param dest GLfloat array to store the values into.
   * @return pointer to the array which the values were stored in.
   */
  GLfloat* getFloats(GLfloat dest[]);

  /**
   * Access a row within range [0, 3] and returns it as a vector.
   * 
   * @param row The row to access.
   * @throws out_of_range exception if row is out of range.
   * @return The values in the desired row packaged into a vector.
   */
  GraphicsVec getRow(int row) const;

  /**
   * Accesses a column within range [0, 3] and returns it as a vector.
   *
   * @param column index of the desired column.
   * @throws out_of_range exception if column is not in range. 
   */
  GraphicsVec getCol(int column) const;

  /**
   * Override of the * operator. When used, it will perform matrix multiplication between the 
   * two matrices.
   * 
   * @param other the other matrix to multiply with.
   * @returns the resulting mat4 created from the product.
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
 * @param matrix Matrix to print to output.
 * @param stream Output stream to write to.
 * @return reference to the ostream object this object was output to.
 */
std::ostream& operator<< (std::ostream& stream, const Mat4& matrix);

////////////////////////////////////////////////////////////////////////////////////////////////////