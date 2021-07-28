// Trent Julich ~ 27 July 2021

#ifndef MODEL_HPP
#define MODEL_HPP

#include <vector>

// Included from source
#include "custom_math.hpp"

/**
 * Class that represents a collection of vertices used to render a 3D model.
 */
class Model {

public:
  Model();
  Model(std::vector<custom_math::Vec4>& modelVertices);

  void listVertices();  

private:
  std::vector<custom_math::Vec4> vertices;
};

#endif