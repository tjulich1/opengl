////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

// Included from src.
#include "model.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

Model::Model(GLfloat vertexBuffer[], int numValues) 
{
  seenNewTransform = false;
  transformMatrix = Mat4::Identity();
  vertexCount = 0;
  /**
   * Have 4 columns in the model vertex matrix (x, y, z, w=1). While there is higher memory cost 
   * having to store all of the additional w values, having to construct a new vertex matrix with 
   * the homogeneous coordinates each frame would have much more impact.
   */
  localVertexData = GraphicsMat(4);
  if (numValues > 0) {
    for (int i = 0; i < numValues; i += 3) 
  {
    
    // Add a new row of vertices to the local vertex data matrix.
    localVertexData.addRow(GraphicsVec{
      vertexBuffer[i],
      vertexBuffer[i+1],
      vertexBuffer[i+2],
      1
    });

    // Count each value triplet as an additional vertex.
    vertexCount++;
  }
  }
}

GraphicsMat Model::getVertexMat()
{
  return localVertexData;
}

void Model::transform(Mat4 theTransformation) 
{
  transformMatrix = transformMatrix * theTransformation;
  seenNewTransform = true;
}

int Model::getVertexCount()
{
  return vertexCount;
}

////////////////////////////////////////////////////////////////////////////////////////////////////