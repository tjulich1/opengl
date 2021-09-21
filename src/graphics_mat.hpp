////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <ostream>

// Included from src.
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
   * Default constructor for an empty GraphicsMat. Number of columns must be set before adding rows
   * to the matrix (using setCols()).
   */
  GraphicsMat();

  /**
   * Constructor for new row-major GraphicsMat. Takes parameter for the number of columns that this
   * matrix will contain. 
   * 
   * @param cols the number of columns that should be present in the matrix.
   * 
   * @throws invalid_argument exception if negative values are given for either cols or rows.
   */
  GraphicsMat(int cols);

  /**
   * Method used to set a single element within the matrix, as long as the given indices fall within
   * [0, row/colCount - 1] respectively. 
   * 
   * @param rowIndex index of the row in which to modify element.
   * @param colIndex index of the column in which to modify element.
   * @param value float value to be written to the matrix.
   * 
   * @throws out_of_range exception for row/col indices less than zero or above this matrices 
   *         dimensions.
   */
  void setElement(int colIndex, int rowIndex, float value);

  /**
   * Used to set new values to a whole row within the matrix. Row index must not exceed the number 
   * of rows within the matrix, or be negative. Only the first "myCols" elements will be taken from 
   * the supplied vector, and if not enough values are found, matrix values will be left to their 
   * previous values.
   * 
   * @param rowIndex the row that should be set within the matrix.
   * @param elements vector containing values that should be put in matrix.
   * 
   * @return true if row was set, false otherwise.
   */
  void setRow(int rowIndex, GraphicsVec elements); 

  /**
   * Appends a new row to the bottom of the matrix. If not enough values are found in the supplied 
   * vector zeros will be used as padding. If too many values are supplied, elements equal to the 
   * number of columns will be used.
   * 
   * @param elements Vector containing the elements within the row to add.
   */
  void addRow(GraphicsVec elements);

  /**
   * Accesses the number of columns in the matrix.
   * 
   * @return number of columns in the matrix.
   */
  int getCols() const { return myCols; }

  /**
   * Accesses the number of rows in the matrix.
   * 
   * @return nunmber of rows in the matrix.
   */
  int getRows() const { return myRows; }

  /**
   * Used to set the number of columns this matrix should contain. Should only be called on matrices 
   * that have not had dimensions set, i.e. from default constructor.
   * 
   * @param cols
   * 
   * @throws invalid_argument exception if number of cols is <= 0. 
   */
  void setCols(int cols);

  /**
   * Accesses the element in the given row/column, or an arbitrary value if indices are out of 
   * bounds.
   * 
   * @param col column of element desired.
   * @param row row of element desired.
   * 
   * @return element at the given row/col in the matrix.
   */
  float getElement(int col, int row) const;

  /**
   * Returns a vector containing the values in the desired row.
   * 
   * @param rowIndex the index of the row to access.
   * 
   * @return vector containing all elements in the desired row.
   */
  GraphicsVec accessRow(int rowIndex) const;

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
   * Vector of GraphicsVecs containing matrix values.
   */
  std::vector<GraphicsVec> matrixValues;
};

/**
 * Override of the << operator, used to put a representation of the Mat4 to the output stream.
 * 
 * matrix: Matrix to print to output.
 * stream: Output stream to write to.
 */
std::ostream& operator<< (std::ostream& stream, const GraphicsMat& matrix);

////////////////////////////////////////////////////////////////////////////////////////////////////