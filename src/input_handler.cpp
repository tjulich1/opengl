////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 7 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

/**
 * Included from src.
 */
#include "input_handler.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

bool InputHandler::handleKeyDown(SDL_Event e)
{
  bool success = true;
  switch(e.key.keysym.sym) {
    case SDLK_a: std::cout << "A DOWN" << std::endl; break;
    case SDLK_d: std::cout << "D DOWN" << std::endl; break;
    case SDLK_w: std::cout << "W DOWN" << std::endl; break;
    case SDLK_s: std::cout << "S DOWN" << std::endl; break;
    default: success = false; break;
  }
  return success;
}

bool InputHandler::handleKeyUp(SDL_Event e) 
{
  bool validKey = true;
  switch(e.key.keysym.sym) {
    case SDLK_a: std::cout << "A UP" << std::endl; break;
    case SDLK_d: std::cout << "D UP" << std::endl; break;
    case SDLK_w: std::cout << "W UP" << std::endl; break;
    case SDLK_s: std::cout << "S UP" << std::endl; break;
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