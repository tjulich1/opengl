////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 31 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <glew.h>
#include <iostream>

// Included from src.
#include "setup.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

Setup::Setup(std::string title, int width, int height) 
{
  windowWidth = width;
  windowHeight = height;
  windowTitle = title;
}

bool Setup::initialize() 
{
  bool success = true;
  if (initSDL() && createWindow() && createContext() && initGlew() && initVsync()) {
    
  } else {
    success = false;
  }
  return success;
}

bool Setup::initSDL() 
{
  const int sdlSuccessCode = 0;
  successCodes[sdlSuccessCode] = true;
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
    successCodes[sdlSuccessCode] = false;
  }
  return successCodes[sdlSuccessCode];
}

void Setup::setGLVersion(int major, int minor) 
{
  majorVersion = major;
  minorVersion = minor;
}

void Setup::setGLVersion() 
{
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, majorVersion);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, minorVersion);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}

bool Setup::createWindow() 
{
  const int windowSuccessCode = 1;
  successCodes[windowSuccessCode] = true;
  window = SDL_CreateWindow(windowTitle.c_str(), SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
  if (!window) {
    std::cout << "Failed to create window: " << SDL_GetError() << std::endl;
    successCodes[windowSuccessCode] = false;
  }
  return successCodes[windowSuccessCode];
}

bool Setup::createContext() 
{
  const int contextSuccessCode = 2;
  successCodes[contextSuccessCode] = true;
  if (window) {
    context = SDL_GL_CreateContext(window);
    if (!context) {
      std::cout << "Failed to create context: " << SDL_GetError() << std::endl;
      successCodes[contextSuccessCode] = false;
    }
  }
  return successCodes[contextSuccessCode];
}

bool Setup::initGlew()
{
  const int glewSuccessCode = 3;
  successCodes[glewSuccessCode] = true;
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();

  if (glewError != GLEW_OK) {
    std::cout << "Error initializing GLEW: " << glewGetErrorString(glewError) << std::endl;
    successCodes[glewSuccessCode] = false;
  }
  return successCodes[glewSuccessCode];
}

bool Setup::initVsync() 
{
  const int vsyncSuccessCode = 4;
  successCodes[vsyncSuccessCode] = true;
  if (USE_VSYNC && SDL_GL_SetSwapInterval(1) < 0) {
    successCodes[vsyncSuccessCode] = false;
    std::cout << "Unable to use vsync: " << SDL_GetError() << std::endl;
  }
  return successCodes[vsyncSuccessCode];
}

////////////////////////////////////////////////////////////////////////////////////////////////////