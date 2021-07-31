// Trent Julich ~ 27 July 2021

#pragma once

#include <vector>

/*
 * Included from source
 */
#include "custom_math.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Class that represents a collection of vertices used to render a 3D model.
 */
class Model 
{
public:
  /**
   * Constructor for new model, containing vertices found in the argument list.
   * 
   * modelVertices: Vector of Vec4, containing vertex information for model.
   */
  Model(std::vector<custom_math::Vec4>& modelVertices);

  /**
   * Prints the full list of model vertices to std::cout.
   */
  void listVertices();  

private:
  /**
   * Vector holding the vertex data.
   */
  std::vector<custom_math::Vec4> vertices;
};

////////////////////////////////////////////////////////////////////////////////////////////////////