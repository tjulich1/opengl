// Trent Julich ~ 26 July 2021

#pragma once

#include <gl/GL.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace util {
  /**
   * Converts the float representation of homogeneous vertex data into screen coordinates by 
   * removing all values corresponding to w.
   * 
   * floats: The list of floats to convert to screen coordinates.
   * numPoints: The number of vertices that should be stripped.
   */
  GLfloat* convertToScreen(GLfloat* floats, int numPoints);
  
  /**
   * Prints the log associated with the desired OpenGL shader program.
   * 
   * program: ID of the program to print log of.
   */ 
  void printProgramLog(GLuint program);
};

////////////////////////////////////////////////////////////////////////////////////////////////////