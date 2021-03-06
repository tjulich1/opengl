////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 1 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "frustum.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

Frustum::Frustum(float left, float right, float top, float bottom, float nearVal, float farVal) 
{
  leftValue = left;
  rightValue = right;
  topValue = top;
  bottomValue = bottom;
  nearValue = nearVal;
  farValue = farVal;
}

Mat4 Frustum::createPerspectiveMatrix() 
{
  Mat4 perspectiveMatrix;

  GraphicsVec firstRow {
    2*nearValue / (rightValue-leftValue),
    0, 0, 0
  };

  GraphicsVec secondRow {
    0, 
    2*nearValue / (topValue-bottomValue),
    0, 0
  };

  GraphicsVec thirdRow {
    (rightValue+leftValue) / (rightValue-leftValue),
    (topValue+bottomValue) / (topValue-bottomValue), 
    -(farValue+nearValue) / (farValue-nearValue),
    -1
  };

  GraphicsVec fourthRow {
    0, 0, 
    -2*farValue*nearValue / (farValue-nearValue),
    0
  };

  perspectiveMatrix.setRow(0, firstRow);
  perspectiveMatrix.setRow(1, secondRow);
  perspectiveMatrix.setRow(2, thirdRow);
  perspectiveMatrix.setRow(3, fourthRow);

  return perspectiveMatrix;
}

////////////////////////////////////////////////////////////////////////////////////////////////////