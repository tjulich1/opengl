// Trent Julich ~ 2 August 2021

#pragma once

/**
 * Included from src.
 */
#include "custom_math.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

class Camera
{
public:
  /**
   * 
   */
  Camera(float x, float y, float z, float destX, float destY, float destZ);
  
  /**
   * 
   */
  custom_math::Mat4 getLookat();

  /**
   * 
   */
  inline void setX(float newX) { cameraX = newX; }

  /**
   * 
   */
  inline void setY(float newY) { cameraY = newY; }

  /**
   * 
   */
  inline void setZ(float newZ) { cameraZ = newZ; }

  /**
   * 
   */
  inline float getX() { return cameraX; };

  /**
   * 
   */
  inline float getY() { return cameraY; }

  /**
   * 
   */
  inline float getZ() { return cameraZ; }

private:
  /**
   * 
   */
  float cameraX; 
  float cameraY;
  float cameraZ;

  /**
   * 
   */
  float lookatX;
  float lookatY;
  float lookatZ;
};

////////////////////////////////////////////////////////////////////////////////////////////////////