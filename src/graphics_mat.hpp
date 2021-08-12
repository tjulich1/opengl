////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>

/**
 * Included from src.
 */
#include "graphics_vec.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * General purpose matrices used for encoding 3D model information, as well as transformations.
 * Matrices are encoded in row major order.
 */
class GraphicsMat 
{
public:

  /**
   * Default constructor for an entirely empty matrix. Dimensions must be set using initialize().
   */
  GraphicsMat();

  /**
   * Constructor which takes initial dimensions of the matrix. Each element is set to zero 
   * initially.
   * 
   * rows: The number of rows in the matrix.
   * cols: The number of columns in the matrix. 
   */
  GraphicsMat(int rows, int cols);

  /**
   * Attempts to initialize matrix with the given number of rows and columns. Will only set values 
   * on an empty matrix and for positive values.
   * 
   * rows: The desired number of rows in the matrix.
   * cols: The desired number of columns in the matrix.
   * 
   * returns: True if dimensions were set, false otherwise.
   */
  bool initialize(int rows, int cols);

  /**
   * Method used to set a single element within the matrix, as long as the given indices fall within
   * valid ranges, i.e. are non-negative and do not equal or exceed matrix row/column counts.
   */
  bool setElement(int rowIndex, int colIndex, float value);

  /**
   * Used to set new values to a whole row within the matrix. Row index must not exceed the number 
   * of rows within the matrix, or be negative. Only the first "myCols" elements will be taken from 
   * the supplied vector, and if not enough values are found, matrix values will be left to their 
   * previous values.
   * 
   * rowIndex: The row that should be set within the matrix.
   * elements: Vector containing values that should be put in matrix.
   */
  bool setRow(int rowIndex, GraphicsVec elements); 

  /**
   * Accesses the number of columns in the matrix.
   */
  int getCols() { return myCols; }

  /**
   * Accesses the number of rows in the matrix.
   */
  int getRows() { return myRows; }

private:

  /**
   * Number of rows in the matrix.
   */
  int myRows;

  /**
   * Number of columns in the matrix.
   */
  int myCols;

  /**
   * Flag indicating whether or not the matrix has been initialized with valid dimensions.
   */
  bool isInitialized;

  /**
   * Vector containing the float values held within the matrix.
   */
  std::vector<float> matrixValues;
};

////////////////////////////////////////////////////////////////////////////////////////////////////