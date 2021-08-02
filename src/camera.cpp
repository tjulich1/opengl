/**
 * Included from src. 
 */
#include "camera.hpp"

Camera::Camera(float x, float y, float z, float destX, float destY, float destZ) :
cameraX(x), cameraY(y), cameraZ(z), lookatX(destX), lookatY(destY), lookatZ(destZ) { }

custom_math::Mat4 Camera::getLookat() 
{
  custom_math::Mat4 lookat;

  custom_math::Vec4 temp(0, 1, 0, 1);
  temp.normalize();

  float forwardX = cameraX - lookatX;
  float forwardY = cameraY - lookatY;
  float forwardZ = cameraZ - lookatZ;

  custom_math::Vec4 forward(forwardX, forwardY, forwardZ, 1);
  forward.normalize();

  custom_math::Vec4 right = temp.cross(forward);

  custom_math::Vec4 up = forward.cross(right);

  right.setW(0);
  lookat.setRow(0, right);
  up.setW(0);
  lookat.setRow(1, up);
  forward.setW(0);
  lookat.setRow(2, forward);
  
  const custom_math::Vec4 cameraTranslate(cameraX, cameraY, cameraZ, 1);
  lookat.setRow(3, cameraTranslate);

  return lookat;
}