/**
 * Included from src. 
 */
#include "camera.hpp"

Camera::Camera(float x, float y, float z, float destX, float destY, float destZ) :
cameraX(x), cameraY(y), cameraZ(z), lookatX(destX), lookatY(destY), lookatZ(destZ) { }

custom_math::Mat4 Camera::getLookat() 
{
  custom_math::Mat4 lookat;

  float z_x = lookatX - cameraX;
  float z_y = lookatY - cameraY;
  float z_z = lookatZ - cameraZ;

  custom_math::Vec4 zAxis(z_x, z_y, z_z, 0);
  zAxis.normalize();

  custom_math::Vec4 up(0, 1, 0, 0);

  custom_math::Vec4 xAxis = zAxis.cross(up);

  custom_math::Vec4 yAxis = xAxis.cross(zAxis);
  
  zAxis.setX(-zAxis.getX());
  zAxis.setY(-zAxis.getY());
  zAxis.setZ(-zAxis.getZ());

  custom_math::Vec4 cameraVec(cameraX, cameraY, cameraZ, 0);

  custom_math::Vec4 bottomRow(-xAxis.dot(cameraVec), -yAxis.dot(cameraVec), 
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