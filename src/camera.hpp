////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 2 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>

/**
 * Included from src.
 */
#include "custom_math.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Class representing a camera in 3D space. Also used to get LookAt matrix for view transformation.
 */
class Camera
{
public:
  /**
   * Constructor for a camera with the given position and looking in the direction defined by 
   * cameraLook.
   * 
   * cameraPosition: A 3D vector defining the position of the camera in 3D space.
   * cameraLook: A 3D vector defining the direction the camera is viewing in 3D space.
   */
  Camera(custom_math::Vec3 cameraPosition, custom_math::Vec3 cameraLook);

  /**
   * Default constructor for empty camera object.
   */
  Camera();

  /**
   * Method used to generate a lookat matrix using the given camera objects current orientation 
   * (camera position and camera view point).
   */
  custom_math::Mat4 getLookat();

private:

  /**
   * Vector containing the position of the camera in 3D space.
   */
  custom_math::Vec3 position;

  /**
   * Vector containing the point that the camera is looking towards.
   */
  custom_math::Vec3 lookDirection;
};

////////////////////////////////////////////////////////////////////////////////////////////////////