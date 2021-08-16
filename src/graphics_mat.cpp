////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

// Included from src.
#include "graphics_mat.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

GraphicsMat::GraphicsMat(int rows, int cols)
{
  myRows = rows;
  myCols = cols;
  if (cols <= 0) {
    isInitialized = false;
  }
}

bool GraphicsMat::initialize(int rows, int cols) 
{
  bool success = false;

  if (!isInitialized && rows > 0 && cols > 0) {
    success = true;
    myRows = rows;
    myCols = cols;
    isInitialized = true;
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