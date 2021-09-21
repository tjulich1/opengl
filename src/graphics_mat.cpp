////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

// Included from src.
#include "graphics_mat.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

GraphicsMat::GraphicsMat() : myRows(0), myCols(0) { };

GraphicsMat::GraphicsMat(int cols)
{
  if (cols <= 0) throw std::invalid_argument("Number of columns must be positive: " + cols);

  // Vector filled with zeros, containing as many elements as there are columns.
  GraphicsVec emptyVec(cols);

  myCols = cols;
  myRows = 0;
  isInitialized = true;
}

void GraphicsMat::setElement(int colIndex, int rowIndex, float value)
{
  if (rowIndex < 0 || rowIndex >= myRows) 
    throw std::out_of_range("Invalid index for row: " + rowIndex);
  if (colIndex < 0 || colIndex >= myCols) 
    throw std::out_of_range("Invalid index for col: " + colIndex);

  matrixValues.at(rowIndex).setElement(colIndex, value);    
}

void GraphicsMat::setRow(int rowIndex, GraphicsVec elements) 
{
  if (rowIndex < 0 || rowIndex >= myRows)  
    throw std::out_of_range("Invalid index for row: " + rowIndex);

  // Ensure the row index is valid for this matrix.
  if (isInitialized && rowIndex < myRows) {
    for (int i = 0; i < elements.getSize() && i < myRows; i++) {
      matrixValues.at(rowIndex).setElement(i, elements.getElement(i));
    }
  }
}

void GraphicsMat::addRow(GraphicsVec elements)
{
  int numValues = elements.getSize();

  // Vector starts filled with zeros.
  GraphicsVec theNewRow(myCols);

  if (numValues < myCols) {
    // Less values were given than available space, so take all the values.
    for (int i = 0; i < numValues; i++) {
      theNewRow.setElement(i, elements.getElement(i));
    }
  } else {
    // More values were given, so only take what we can store.
    for (int i = 0; i < myCols; i++) {
      theNewRow.setElement(i, elements.getElement(i));
    }
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