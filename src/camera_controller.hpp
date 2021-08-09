////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 8 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <memory>

/**
 * Included from src.
 */
#include "camera.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

class CameraController 
{
public:
  /**
   * Default camera controller constructor, must be given camera object to be used.
   */
  CameraController();

  /**
   * Camera controller constructor which applies user inputs to the given camera object.
   */
  CameraController(Camera* theCamera);

  /**
   * Moves the camera along the y-axis by the given amount.
   * 
   * theDistance: The amount to move the camera.
   */
  void moveY(float theDistance);

  /**
   * Setter for the camera that this controller should control.
   */
  void setCamera(Camera* newCamera);

  /**
   * Returns the status of whether a camera object is currently linked to this controller.
   */
  bool getIsCameraLinked() { return isCameraLinked; } 

  /**
   * Disconnects the current camera object, if one is attached.
   */
  void disconnect();

private:
  /**
   * Pointer to the camera object associated with this camera controller.
   */
  std::shared_ptr<Camera> myCamera = nullptr;

  /**
   * Flag for determining if a camera object has been provided for control, or if default 
   * constructor was used.
   */
  bool isCameraLinked;
};

////////////////////////////////////////////////////////////////////////////////////////////////////