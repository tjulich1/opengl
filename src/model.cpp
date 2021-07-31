// Trent Julich ~ 27 July 2021

#include <iostream>

// Included from source
#include "model.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

Model::Model(std::vector<custom_math::Vec4>& modelVertices) {
  for (int i = 0; i < modelVertices.size(); i++) {
    // Make a copy of the vertex and store it in the model vertex list.
    vertices.emplace_back(modelVertices[i].copy());
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Model::listVertices() {
  for (int i = 0; i < vertices.size(); i++) {
    custom_math::Vec4 vertex = vertices[i];
    float x = vertex.getX();
    float y = vertex.getY();
    float z = vertex.getZ();
    float w = vertex.getW();
    std::cout << "(" << x << ", " << y << ", " << z << ", " << w << ")" << std::endl;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////