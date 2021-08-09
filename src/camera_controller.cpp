////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 8 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Included from src.
 */
#include "camera_controller.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

CameraController::CameraController()
{
  isCameraLinked = false;
}


CameraController::CameraController(Camera* theCamera) 
{
  myCamera.reset(theCamera);
  isCameraLinked = true;
}

void CameraController::moveY(float theDistance)
{
  GraphicsVec currentPosition = myCamera->getPosition();
  GraphicsVec newPosition(
    currentPosition.getX(),
    currentPosition.getY() + theDistance, 
    currentPosition.getZ()
  );
  myCamera->moveCamera(newPosition);
  GraphicsVec currentLook = myCamera->getLookDest();
  GraphicsVec newLook(
    currentLook.getX(),
    currentLook.getY() + theDistance,
    currentLook.getZ()
  );
  myCamera->look(newLook);
}

void CameraController::setCamera(Camera* newCamera) 
{
  myCamera.reset(newCamera);
  isCameraLinked = true;
}

void CameraController::disconnect()
{
  myCamera = nullptr;
  isCameraLinked = false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////