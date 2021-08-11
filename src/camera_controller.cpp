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

void CameraController::moveAxis(float theDistance, Axis theAxis)
{
  GraphicsVec currentPosition = myCamera->getPosition();
  GraphicsVec currentLook     = myCamera->getLookDest();

  float posX = currentPosition.getX();
  float posY = currentPosition.getY();
  float posZ = currentPosition.getZ(); 
  
  float lookX = currentLook.getX();
  float lookY = currentLook.getY();
  float lookZ = currentLook.getZ();
  
  /**
   * Depending on the axis, add the given distance to the x, y, or z components of the original
   * position and view point.
   */
  switch (theAxis) 
  {
    case X_AXIS: {
      posX  += theDistance;
      lookX += theDistance;
      break;
    }
    case Y_AXIS: {
      posY  += theDistance;
      lookY += theDistance;
      break;
    }
    case Z_AXIS: {
      posZ  += theDistance;
      lookZ += theDistance;
      break;
    }
    // Don't move anything if invalid axis is somehow passed.
    default: return;
  }
  myCamera->moveCamera(GraphicsVec(posX, posY, posZ));
  myCamera->look(GraphicsVec(lookX, lookY, lookZ));
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