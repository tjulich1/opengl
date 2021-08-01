////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 1 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <SDL.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

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
};

////////////////////////////////////////////////////////////////////////////////////////////////////