////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Included from src.
 */
#include "graphics_mat.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

GraphicsMat::GraphicsMat()
{
  isInitialized = true;
  myRows = 0;
  myCols = 0;
}

GraphicsMat::GraphicsMat(int cols) 
{
  myCols = cols;
  myRows = 0;
  isInitialized = false;
}

GraphicsMat::GraphicsMat(int rows, int cols) 
{
  if (rows > 0 && cols > 0) {
    myRows = rows;
    myCols = cols;
    isInitialized = false;
  } else {
    myRows = 0;
    myCols = 0;
    isInitialized = true;
  }
}

bool GraphicsMat::initialize(int rows, int cols) 
{
  bool success = false;

  if (!isInitialized && rows > 0 && cols > 0) {
    success = true;
    myRows = rows;
    myCols = cols;
  }

  return success;
}

bool GraphicsMat::setElement(int rowIndex, int colIndex, float value)
{
  bool success = false;

  if (isInitialized && rowIndex >= 0 && colIndex >= 0 && rowIndex < myRows && colIndex < myCols) {
    matrixValues.at(rowIndex).setElement(colIndex, value);
    success = true;
  }

  return success;
}

bool GraphicsMat::setRow(int rowIndex, GraphicsVec elements) 
{
  bool success = true;

  // Ensure the row index is valid for this matrix.
  if (isInitialized && rowIndex < myRows) {
    for (int i = 0; i < elements.getSize(); i++) {
      matrixValues.at(rowIndex).setElement(i, elements.getElement(i));
    }
    success = true;
  }
  return success;
}

void GraphicsMat::addRow(GraphicsVec elements)
{
  int numValuesSupplied = elements.getSize();

  // Padding will be required.
  if (numValuesSupplied < myCols) {

  }

  // Fill rest of values.
  for (int i = 0; i < elements.getSize(); i++) {
    
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////