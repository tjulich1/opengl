////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>

// Included from src.
#include "model.hpp"
#include "transformation_builder.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

Model::Model(GLfloat vertexBuffer[], int numValues) 
{
  seenNewTransform = false;
  transformMatrix = TransformationBuilder::Identity();
  vertexCount = 0;
  /**
   * Have 4 columns in the model vertex matrix (x, y, z, w=1). While there is higher memory cost 
   * having to store all of the additional w values, having to construct a new vertex matrix with 
   * the homogeneous coordinates each frame would have more impact.
   */
  localVertexData = GraphicsMat(4);
  if (numValues > 0) {
    for (int i = 0; i < numValues; i += 3) {
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
  cachedWorldVertexData = localVertexData;
}

GraphicsMat Model::getVertexMat()
{
  return localVertexData;
}

void Model::translate(float x, float y, float z) 
{
  // Build the translate matrix.
  Mat4 translateMatrix = TransformationBuilder::translation(x, y, z);

  // Add translation into previous transformations.
  transformMatrix = transformMatrix * translateMatrix;

  seenNewTransform = true;
}

int Model::getVertexCount()
{
  return vertexCount;
}

GraphicsMat Model::getTransformedVertexMat()
{
  GraphicsMat worldSpaceVertices;
  // Model has seen another transformation since last request for world-space coordinates.
  if (seenNewTransform) {
    // Compute the result of all transformations on original vertex values.
    computeWorldCoordinates();
    worldSpaceVertices = cachedWorldVertexData;
  }
  return worldSpaceVertices;
}

void Model::computeWorldCoordinates()
{
  /**
   * Each model has local vertex data aligned in rows:
   * 
   * x1, y1, z1, 
   * x2, y2, ...
   * ...
   * ...
   * 
   * Grab a row at a time, and multiply with the models current transformation matrix. 
   */
  if (seenNewTransform) {
    // For each vertex in the model...
    for (int i = 0; i < vertexCount; i++) {
      GraphicsVec currentVertex = localVertexData.accessRow(i);
      GraphicsVec transformedVertex = currentVertex * transformMatrix;
      cachedWorldVertexData.setRow(i, transformedVertex);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////