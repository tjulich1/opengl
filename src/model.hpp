////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>
#include <gl/GL.h>

// Included from src.
#include "graphics_mat.hpp"
#include "graphics_vec.hpp"
#include "mat4.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * 
 */
class Model 
{
public:

  /**
   * Constructor for model that should be rendered with the given vertex data. 
   * 
   * @param vertices Array of GLfloats, with each consecutive group of 3 numbers corresponding to a single
   *           model vertex. If numValues % 3 != 0, any remaining values will not be used.
   * 
   * @param numValues The number of data points in the given buffer. 
   */
  Model(GLfloat* vertexBuffer = 0, int numValues = 0);

  /**
   * Used to get a matrix containing vertex information of the model in its local coordinate space.
   * 
   * @returns Local-space coordinates of model encoded in matrix.
   */
  GraphicsMat getVertexMat();

  /**
   * Moves the model from its previous position by the desired amounts along each axis.
   * 
   * @param x amount to shift x.
   * @param y amount to shift y.
   * @param z amount to shift z.
   */
  void translate(float x, float y, float z);

  /**
   * Gets a copy of this models vertex coordinates after all transformations have been applied.
   * 
   * @returns World-space coordinates of model encoded in matrix.
   */
  GraphicsMat getTransformedVertexMat();

  /**
   * Gets the number of vertices that this model has.
   * 
   * @returns Vertex count of model.
   */
  int getVertexCount();

private:
  /**
   * Matrix encoding the local-space coordinates of the model. Matrix has 4 columns, one for each of 
   * the x, y, z, and w components of each vertex.
   */
  GraphicsMat localVertexData = GraphicsMat(4);

  /**
   * Matrix encoding the world-space coordinates of the model. While 2 copies of vertex data must be
   * stored, it saves computing the world-space coordinates repeatedly for mostly-static models.
   */
  GraphicsMat cachedWorldVertexData = GraphicsMat(4);

  /**
   * The number of vertices this model contains.
   */
  int vertexCount;

  /**
   * Mat4 that encodes all transformations this model has undergone.
   */
  Mat4 transformMatrix;

  /**
   * Flag keeping track of whether a new transformation has been added since last call to 
   * getTransformedVertexMat().
   */
  bool seenNewTransform;

  /**
   * Helper method used to compute the values of this models vertices after all transformations have 
   * been applied.
   */
  void computeWorldCoordinates();
};

////////////////////////////////////////////////////////////////////////////////////////////////////