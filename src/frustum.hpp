////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 1 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

/**
 * Included from src.
 */
#include "custom_math.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * 
 */
class Frustum 
{
public:
  /**
   * 
   */
  Frustum(float left, float right, float top, float bottom, float nearVal, float farVal);

  /**
   * 
   */
  custom_math::Mat4 createPerspectiveMatrix();

private:
  /**
   * 
   */
  float leftValue;
  float rightValue;
  float topValue;
  float bottomValue;
  float nearValue;
  float farValue;
};

////////////////////////////////////////////////////////////////////////////////////////////////////