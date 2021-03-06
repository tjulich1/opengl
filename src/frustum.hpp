////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 1 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// Included from src.
#include "mat4.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Class that defines a camera frustum, or the 3D space that should be rendered to the screen.
 */
class Frustum 
{
public:
  /**
   * Constructor for a Frustum based on the 6 defining planes.
   */
  Frustum(float left = 0, float right = 0, float top = 0, float bottom = 0, float nearVal = 0,
          float farVal = 0);

  /**
   * Method used to generate a perspective matrix, used to perform perspective projection 
   * transformations (converts coordinates from camera space to screen space).
   */
  Mat4 createPerspectiveMatrix();

private:
  /**
   * Values which define the coordinates of the 6 planes used to define the frustum.
   */
  float leftValue;
  float rightValue;
  float topValue;
  float bottomValue;
  float nearValue;
  float farValue;
};

////////////////////////////////////////////////////////////////////////////////////////////////////