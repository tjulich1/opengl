// Trent Julich ~ 29 July 2021

#include <fstream>
#include <sstream>

#include "shader.hpp"

/**
 * 
 */
Shader::Shader() {

}

/**
 * 
 */
Shader::Shader(std::string shaderSrc) {

}

/**
 * Reads in a shader that is located at the given path.
 * 
 * args: std::string path = path to the shader that should be opened.
 * returns: std::string shader = string contents of shader that was read. Empty string if shader 
 *              cannot be found at path.
 */
std::string openShader(std::string path) {
  // Init shader with empty string in case of failure to open file.
  std::string shader = "";

  // Try to open file.
  std::fstream shaderFile(path);
  
  // If the file was successfully opened
  if (shaderFile.is_open()) {
    // Read and store shader file.
    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    shader = buffer.str();    
  } 
  return shader;
}