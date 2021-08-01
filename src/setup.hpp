 // Trent Julich ~ 31 July 2021

 #pragma once

#include <string>
#include <SDL.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Class used to initialize SDL and all other libraries required for engine.
 */
class Setup 
{
public:

  const static bool USE_VSYNC = true;

  /**
   * Constructor for Setup object. Takes arguments for window size, and title.
   * 
   * title: The title of the program/window, displayed at the top.
   * width: The window width in pixels.
   * height: The window height in pixels.
   */
  Setup(std::string title, int width, int height);

  /**
  * The primary method that is called to kick start the initialization process. 
  *
  * returns: True if initialization is successful.
  *          False if initialization is unsuccessful.
  */
  bool initialize();

  // DETERMINE MIN AND MAX SUPPORTED VERSIONS AND ADD CHECKS.
  /**
   * Sets the version of OpenGL that SDL uses to major.minor. 
   */
  void setGLVersion(int major, int minor);

  /**
   * Returns pointer to currently setup SDLWindow.
   */
  inline SDL_Window* getWindow() { return window; }

  /**
   * Gets the SDL_GLContext associated with the current window.
   */
  inline SDL_GLContext getContext() { return context; }

private:

  /**
   * Attempts to initialize the basic SDL systems. 
   * 
   * returns: True if SDL was initialized.
   *          False if SDL was not initialized.
   */
  bool initSDL();

  /**
   * Method which sets the OpenGL version that SDL should use. Will use defaults stored in class, or 
   * version defined by user via publically facing setGLVersion(major, minor) method.
   */ 
  void setGLVersion();

  /**
   * Attempts to create an SDL_Window with the given setup arguments.
   * 
   * returns: True if window is successfully created, as well as initializing window member field.
   *          False if window is not created.
   */
  bool createWindow();

  /**
   * Method which attempts to obtain an OpenGL context associated with this objects window field.
   * 
   * returns: True if context was able to be created.
   *          False if context was unable to be created.
   */
  bool createContext();

  /**
   * Helper method used to initialize GLEW library.
   * 
   * returns: True if glew was successfully initialized.
   *          False if glew was not initialized.
   */
  bool initGlew();

  /**
   * Attempts to initialize vsync.
   */
  bool initVsync();

  /**
   * Array which stores success codes for different stages of initialization.
   * 
   * 0: SDL init
   * 1: Window created
   * 2: Context created
   * 3: GLEW initialized
   * 4: V-Sync
   */
  bool successCodes[5];

  /**
   * Fields which store the OpenGL version that SDL should use. 
   */
  int majorVersion = 3;
  int minorVersion = 2;

  /**
   * Title of the window.
   */
  std::string windowTitle;

  /**
   * Window dimensions in pixels.
   */
  int windowWidth;
  int windowHeight;

  /**
   * SDL window that is attempted to be created when initialize method is called.
   */
  SDL_Window* window;

  /**
   * OpenGL context corresponding to window member field, initialized if window creation is 
   * successul.
   */
  SDL_GLContext context;

};

///////////////////////////////////////////////////////////////////////////////////////////////////