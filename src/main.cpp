// Trent Julich ~ 12 July 2021

#include <SDL.h>
#include <glew.h>
#include <gl\GL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// Included from source
#include "custom_math.hpp"
#include "engine.hpp"
#include "util.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "transformation_builder.hpp"
#include "setup.hpp"

/* Dimensions of main window. */
const static int WIDTH = 500;
const static int HEIGHT = 500;

const static std::string TITLE = "OpenGL test";

const static int MAJOR_VERSION = 3;
const static int MINOR_VERSION = 2;

int create_vertex_shader(GLuint shaderProgram);
int create_fragment_shader(GLuint shaderProgram);
void printShaderLog(GLuint shader);

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


