////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 8 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <memory>

// Included from src.
#include "camera.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

class CameraController 
{
public:

  /**
   * Enum used for specifying axis of movement for camera translations.
   */
  enum Axis
  {
    X_AXIS, Y_AXIS, Z_AXIS
  };

  /**
   * Camera controller constructor which applies user inputs to the given camera object.
   * 
   * theCamera: Pointer to the camera that should be controlled.
   */
  CameraController(Camera* theCamera = 0);

  /**
   * Method used to move both the cameras position and look point a fixed direction along a given 
   * axis.
   * 
   * theDistance: The distance to move the camera along the axis.
   * theAxis: The desired axis to move the camera along.
   */
  void moveAxis(float theDistance, Axis theAxis);

  /**
   * Setter for the camera that this controller should control.
   * 
   * newCamera: Pointer to the camera that should be controlled.
   */
  void setCamera(Camera* newCamera);

  /**
   * Returns the status of whether a camera object is currently linked to this controller.
   * 
   * returns: True if a camera has been linked and can be controlled, else False.
   */
  bool getIsCameraLinked() { return isCameraLinked; } 

  /**
   * Disconnects the current camera object, if one is attached.
   */
  void disconnect();

private:
  /**
   * Pointer to the camera object associated with this controller.
   */
  std::shared_ptr<Camera> myCamera = nullptr;

  /**
   * Flag for determining if a camera object has been provided for control, or if default 
   * constructor was used.
   */
  bool isCameraLinked;
};

////////////////////////////////////////////////////////////////////////////////////////////////////