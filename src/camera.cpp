////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 2 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

// Included from src.
#include "camera.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

Camera::Camera(GraphicsVec cameraPosition, GraphicsVec cameraLook) 
{
  position = cameraPosition;
  lookDirection = cameraLook;
}

void Camera::moveCamera(GraphicsVec newPosition)
{
  if (newPosition.getSize() >= 3) {
    position.setX(newPosition.getX());
    position.setY(newPosition.getY());
    position.setZ(newPosition.getZ());
  }
}

void Camera::look(GraphicsVec newLookPosition) 
{
  if (newLookPosition.getSize() >= 3) {
    lookDirection.setX(newLookPosition.getX());
    lookDirection.setY(newLookPosition.getY());
    lookDirection.setZ(newLookPosition.getZ());
  }
}

Mat4 Camera::getLookat() 
{
  Mat4 lookat;

  // Calculate vector pointing in the direction the camera (new z-axis).
  GraphicsVec zAxis(
    lookDirection.getX() - position.getX(), 
    lookDirection.getY() - position.getY(), 
    lookDirection.getZ() - position.getZ(), 
    0
  );
  zAxis = zAxis.normalize();

  // Choose arbitrary vector pointing in positive y direction.
  GraphicsVec up(0, 1, 0, 0);

  // Calculate x-axis from z-axis and arbitrary vector.
  GraphicsVec xAxis = zAxis.cross(up);
  xAxis = xAxis.normalize();

  // Calculate true camera up from z-axis and x-axis.
  GraphicsVec yAxis = xAxis.cross(zAxis);
  
  // Flip z-axis, so +z points behind the camera.
  zAxis.setX(-zAxis.getX());
  zAxis.setY(-zAxis.getY());
  zAxis.setZ(-zAxis.getZ());

  GraphicsVec cameraVec(position.getX(), position.getY(), position.getZ(), 0);

  GraphicsVec bottomRow(-xAxis.dot(cameraVec), -yAxis.dot(cameraVec), 
    -zAxis.dot(cameraVec), 1);

  lookat.setElement(0, 0, xAxis.getX());
  lookat.setElement(1, 0, yAxis.getX());
  lookat.setElement(2, 0, zAxis.getX());
  lookat.setElement(3, 0, 0);

  lookat.setElement(0, 1, xAxis.getY());
  lookat.setElement(1, 1, yAxis.getY());
  lookat.setElement(2, 1, zAxis.getY());
  lookat.setElement(3, 1, 0);
  
  lookat.setElement(0, 2, xAxis.getZ());
  lookat.setElement(1, 2, yAxis.getZ());
  lookat.setElement(2, 2, zAxis.getZ());
  lookat.setElement(3, 2, 0);

  lookat.setElement(0, 3, bottomRow.getX());
  lookat.setElement(1, 3, bottomRow.getY());
  lookat.setElement(2, 3, bottomRow.getZ());
  lookat.setElement(3, 3, 1);

  return lookat;
}

////////////////////////////////////////////////////////////////////////////////////////////////////