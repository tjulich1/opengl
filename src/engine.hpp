////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 1 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SDL.h>

#include "camera.hpp"
#include "frustum.hpp"
#include "transformation_builder.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

static const float ASPECT = 720.0f / 580.0f;

static const float LEFT = -ASPECT;
static const float RIGHT = ASPECT;
static const float TOP = 1.0f;
static const float BOTTOM = -TOP;
static const float NEAR_VAL = 0.1;
static const float FAR_VAL = 100;

static custom_math::Vec3 CAMERA_START(0, 0, 1);
static custom_math::Vec3 CAMERA_LOOK(0, 0, 0);

/**
 * Class that handles the creation and management of resources needed for graphics engine.
 */
class Engine
{
public:
  /**
   * Constructor that takes a pointer to an SDL window that will be rendered to.
   */
  Engine(SDL_Window* window);
  
  /**
   * Called to start the rendering loop.
   */
  void start();

private:
  /**
   * Main rendering viewport for graphics engine.
   */
  SDL_Window* mainWindow;

  /**
   * ID of the main shader program used by renderer.
   */
  unsigned int shaderProgram;

  /**
   * Main camera object, containing info about camera position and view direction.
   */
  Camera camera;

  /**
   * Holds information regarding the frustum that should be used when performing projections.
   */
  Frustum frustum;

  /**
   * Object used to create transformation matrices for different graphical transformations.
   */
  TransformationBuilder transformer;
};

////////////////////////////////////////////////////////////////////////////////////////////////////