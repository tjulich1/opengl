////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <SDL.h>
#include <string>

// Included from source 
#include "engine.hpp"
#include "setup.hpp"

/* Dimensions of main window. */
const static int WIDTH = 500;
const static int HEIGHT = 500;

const static std::string TITLE = "OpenGL test";

const static int MAJOR_VERSION = 3;
const static int MINOR_VERSION = 2;

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Main entry point of program. Accepts no arguments.
 */
int main(int argc, char* argv[]) 
{
  // Code that is returned by the program.
  int success = 0;

  Setup config(TITLE, WIDTH, HEIGHT);
  config.initialize();
  SDL_Window* window = config.getWindow();

  if (window) {
    Engine engine(window);
    engine.start();
  }

  return success;
}

////////////////////////////////////////////////////////////////////////////////////////////////////