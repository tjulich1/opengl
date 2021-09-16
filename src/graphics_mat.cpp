////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

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
  int numValues = elements.getSize();

  for (int i = 0; i < elements.getSize(); i++) {
    std::cout << "Element " << i << ": " << elements.getElement(i) << std::endl;
  }

  // Vector starts filled with zeros.
  GraphicsVec theNewRow(myCols);

  if (numValues < myCols) {
    std::cout << "Here" << std::endl;
    // Less values were given than available space, so take all the values.
    for (int i = 0; i < numValues; i++) {
      theNewRow.setElement(i, elements.getElement(i));
    }
  } else {
    std::cout << "Here two" << std::endl;
    // More values were given, so only take what we can store.
    for (int i = 0; i < myCols; i++) {
      theNewRow.setElement(i, elements.getElement(i));
    }
  }

  for (int i = 0; i < myCols; i++) {
    std::cout << "New row value: " << theNewRow.getElement(i) << std::endl;
  }

  matrixValues.push_back(theNewRow);
  myRows++;
}

float GraphicsMat::getElement(int col, int row) const {
  float result = -1;
  if (col >= 0 && col < myCols && row >= 0 && row < myRows) {
    result = matrixValues[row].getElement(col);
  }
  return result;
}

GraphicsVec GraphicsMat::accessRow(int rowIndex) const{
  GraphicsVec theRow(myCols);
  if (rowIndex >= 0 && rowIndex < myRows) {
    for (int i = 0; i < myCols; i++) {
      theRow.setElement(i, matrixValues.at(rowIndex).getElement(i));
    }
  }
  return theRow;
}

std::ostream& operator <<(std::ostream &os, const GraphicsMat& mat) {
  os << "[\n";
  for (int i = 0; i < mat.getRows(); i++) {
    os << "\t[";
    for (int j = 0; j < mat.getCols(); j++) {
      os << " " << mat.getElement(j, i);
    }
    os << " ]" << std::endl;
  }
  os << "]";
  return os;
}
////////////////////////////////////////////////////////////////////////////////////////////////////