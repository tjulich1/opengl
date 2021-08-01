////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 29 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * 
 */
class Shader 
{
public:
  /**
   * Constructor for new shader, taking the source code string as an argument.
   * 
   * shaderSrc: The shader source code string.
   */
  Shader(std::string shaderSrc);
  
private:
};

/**
 * Opens shader file found at path, and returns the source code read as a string.
 * 
 * path: The path to the shader file to attempt to open.
 * 
 * returns: String containing shader source code.
 */
std::string openShader(std::string path);

////////////////////////////////////////////////////////////////////////////////////////////////////