////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 7 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

// Included from source 
#include "input_handler.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputHandler::handleKeyDown(SDL_Event e)
{
  bool success = true;

  switch(e.key.keysym.sym) {

    // X-axis camera controls.
    case SDLK_a: 
      myCameraController.moveAxis(-1, myCameraController.X_AXIS); break;
    case SDLK_d: 
      myCameraController.moveAxis(1, myCameraController.X_AXIS); break;
      
    // Z-axis camera controls.  
    case SDLK_s: 
      myCameraController.moveAxis(1, myCameraController.Z_AXIS); break;
    case SDLK_w: 
      myCameraController.moveAxis(-1, myCameraController.Z_AXIS); break;

    // Y-axis controls.
    case SDLK_SPACE: 
      myCameraController.moveAxis(1, myCameraController.Y_AXIS); break;
    case SDLK_LSHIFT: 
      myCameraController.moveAxis(-1, myCameraController.Y_AXIS); break;

    // Everything else.
    default: success = false; break;
  }
  return success;
}

/**
 * Stub for now, some keys may have actions when released.
 */
bool InputHandler::handleKeyUp(SDL_Event e) 
{
  bool validKey = true;
  switch(e.key.keysym.sym) {
    case SDLK_a:  break;
    case SDLK_d:  break;
    case SDLK_w:  break;
    case SDLK_s:  break;
    default: validKey = false; break;
  }
  return validKey;
}

bool InputHandler::handleEvent(SDL_Event e) 
{
  bool success = true;
  switch (e.type) {
    case SDL_KEYDOWN: success = handleKeyDown(e); break; 
    case SDL_KEYUP:   success = handleKeyUp(e);   break;
  }
  return success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////