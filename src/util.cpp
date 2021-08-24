////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 26 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <glew.h>
#include <iostream>

// Included from source
#include "util.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

GLfloat* util::convertToScreen(GLfloat* floats, int numPoints) {
  GLfloat* cartesianFloats = new GLfloat[numPoints*3];

  // Offset used when storing non-homogeneous coordinates to new array.
  const int cartesianOffset = 3;

  // Offset used when grabbing the x, y, z coordinates from the input array.
  const int homogeneousOffset = 4;

  for (int i = 0; i < numPoints; i++) {
    // Grab the x, y, z coordinates from the current point.
    float w = floats[i*homogeneousOffset+3];

    if (w == 0.0f) { w = 1.0f; }

    float x = floats[i*homogeneousOffset] / w;
    float y = floats[(i*homogeneousOffset)+1] / w;
    float z = floats[(i*homogeneousOffset)+2] / w;

    cartesianFloats[i*cartesianOffset] = x;
    cartesianFloats[(i*cartesianOffset)+1] = y; // y
    cartesianFloats[(i*cartesianOffset)+2] = z; // z
  }

  return cartesianFloats;
}

void util::printProgramLog(GLuint program) {
  //Make sure name is shader
  if( glIsProgram( program ) == GL_TRUE) {
    //Program log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;
        
    // Get the length of the log.
    glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
        
    // String to store program log.
    char* infoLog = new char[ maxLength ];
        
    glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );

    if( infoLogLength > 0 ) {
      std::cout << infoLog << std::endl;
    }
    delete[] infoLog;
  } else {
    printf( "Name %d is not a program\n", program );
  }
}

float util::randFloatInRange() 
{
  return 0.0f;
}



////////////////////////////////////////////////////////////////////////////////////////////////////