// Trent Julich ~ 29 July 2021

#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

class Shader {
public:
  Shader();
  Shader(std::string shaderSrc);
  
private:
};

std::string openShader(std::string path);

#endif