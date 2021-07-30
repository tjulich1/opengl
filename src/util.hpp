// Trent Julich ~ 26 July 2021

#ifndef UTIL_HPP
#define UTIL_HPP

#include <gl/GL.h>

namespace util {
  /**
   * 
   */
  GLfloat* convertToScreen(GLfloat* floats, int numPoints);
  
  /**
   * 
   */ 
  void printProgramLog(GLuint program);
};

#endif