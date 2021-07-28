// Trent Julich ~ 26 July 2021

// Included from source
#include "util.hpp"

GLfloat* util::convertToScreen(GLfloat* floats, int numPoints) {
  GLfloat* cartesianFloats = new GLfloat[numPoints*3];

  // Offset used when storing non-homogeneous coordinates to new array.
  const int cartesianOffset = 3;

  // Offset used when grabbing the x, y, z coordinates from the input array.
  const int homogeneousOffset = 4;

  for (int i = 0; i < numPoints; i++) {
    // Grab the x, y, z coordinates from the current point.
    cartesianFloats[i*cartesianOffset] = floats[i*homogeneousOffset]; // x
    cartesianFloats[(i*cartesianOffset)+1] = floats[(i*homogeneousOffset)+1]; // y
    cartesianFloats[(i*cartesianOffset)+2] = floats[(i*homogeneousOffset)+2]; // z
  }

  return cartesianFloats;
}