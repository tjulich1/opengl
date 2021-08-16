////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 2 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <array>

// Included from src.
#include "mat4.hpp"
#include "graphics_vec.hpp"

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
  Camera(GraphicsVec cameraPosition = GraphicsVec(3), GraphicsVec cameraLook = GraphicsVec(3));

  /**
   * Moves the camera to position specified by given vector.
   * 
   * newPosition: 3D vector containing the new position of the camera.
   */
  void moveCamera(GraphicsVec newPosition);

  /**
   * Changes the point that the camera is looking at to the point specified by the given vector.
   * 
   * newLookPosition: 3D vector containing new position for camera to look.
   */
  void look(GraphicsVec newLookPosition);

  /**
   * Method used to generate a lookat matrix using the given camera objects current orientation 
   * (camera position and camera view point).
   */
  Mat4 getLookat();

  /**
   * Returns the current position of the camera.
   */
  GraphicsVec  getPosition() { return position; }

  /**
   * Returns the point the camera is currently looking at.
   */
  GraphicsVec getLookDest() { return lookDirection; }

private:

  /**
   * Vector containing the position of the camera in 3D space.
   */
  GraphicsVec position;

  /**
   * Vector containing the point that the camera is looking towards.
   */
  GraphicsVec lookDirection;
};

////////////////////////////////////////////////////////////////////////////////////////////////////