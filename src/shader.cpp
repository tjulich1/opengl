// Trent Julich ~ 29 July 2021

#include <fstream>
#include <sstream>

#include "shader.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

Shader::Shader(std::string shaderSrc) {

}

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

////////////////////////////////////////////////////////////////////////////////////////////////////