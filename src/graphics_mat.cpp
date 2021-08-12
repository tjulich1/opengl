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

/**
 * TODO
 */
bool GraphicsMat::setElement(int rowIndex, int colIndex, float value)
{
  return false;
}

/**
 * TODO
 */
bool GraphicsMat::setRow(int rowIndex, GraphicsVec elements) 
{
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////