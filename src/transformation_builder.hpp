////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 30 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once

// Included from src.
#include "mat4.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Class used to generate transformation matrices used in computer graphics. 
 */
class TransformationBuilder 
{
public:
  /**
   * Constructs a translation matrix, which when multiplied with a vertex will translate it in 3D 
   * space by the given arguments.
   * 
   * xTranslate: The amount to shift along the x-axis.
   * yTranslate: The amount to shift along the y-axis.
   * zTranslate: The amount to shift along the z-axis.
   */
  Mat4 translation(float xTranslate, float yTranslate, float zTranslate);
  
  /**
   * Constructs a matrix which when multiplied with a vertex, will scale each of its components by
   * the scale factor given as arguments.
   * 
   * xFactor: Scale factor along x-axis.
   * yFactor: Scale factor along y-axis.
   * zFactor: Scale factor along z-axis.
   */
  Mat4 scale(float xFactor, float yFactor, float zFactor);
  
  /**
   * Constructs a matrix which when multiplied with a vertex, rotates said vertex around the x-axis.
   * 
   * angleOfRotation: The angle in degrees that the vertex should be rotated.
   */
  Mat4 xRotation(int angleOfRotation);

  /**
   * Constructs a matrix which when multiplied with a vertex, rotates said vertex around the y-axis.
   * 
   * angleOfRotation: The angle in degrees that the vertex should be rotated.
   */
  Mat4 yRotation(int angleOfRotation);

  /**
   * Constructs a matrix which when multiplied with a vertex, rotates said vertex around the z-axis.
   * 
   * angleOfRotation: The angle in degrees that the vertex should be rotated.
   */
  Mat4 zRotation(int angleOfRotation);

  /**
   * Constructs a matrix that when multiplied with a vertex, will rotate said vertex around an 
   * arbitrary axis.
   * 
   * angleOfRotation: The angle in degrees that the vertex should be rotated.
   * axis: A vector that points along the desired axis of rotation.
   */
  Mat4 rotateFromAxisAngle(int angleOfRotation, GraphicsVec axis);
};

////////////////////////////////////////////////////////////////////////////////////////////////////