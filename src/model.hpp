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

class Model 
{
public:

  /**
   * Constructor for model that should be rendered with the given vertex data. 
   * 
   * vertices: Array of GLfloats, with each consecutive group of 3 numbers corresponding to a single
   *           model vertex. If numValues % 3 != 0, any remaining values will not be used.
   * 
   * numValues: The number of data points in the given buffer. 
   */
  Model(GLfloat* vertexBuffer = 0, int numValues = 0);

  /**
   * Used to get a matrix containing vertex information of the model in its local coordinate space.
   * 
   * returns: Local-space coordinates of model encoded in matrix.
   */
  GraphicsMat getVertexMat();

  /**
   * Moves the model from its previous position by the desired amounts along each axis.
   * 
   * x: amount to shift x.
   * y: amount to shift y.
   * z: amount to shift z.
   */
  void translate(float x, float y, float z = 0);

  /**
   * Used to get a matrix containing vertex information of the model in world space, or after 
   * transformations have been applied and the model has been positioned in place.
   * 
   * returns: World-space coordinates of model encoded in matrix.
   */
  GraphicsMat getTransformedVertexMat();

  /**
   * Used to multiply an additional transformation matrix into this models current matrix. Callers 
   * of this method are responsible for order dependent transformations, e.g. rotations before 
   * translations vs. translations before rotations.
   *
   * theTransformation: The Mat4 encoding the desired transformation.
   */
  void transform(Mat4 theTransformation);

  /**
   * Gets the number of vertices that this model has.
   * 
   * returns: Vertex count of model.
   */
  int getVertexCount();

private:

  /**
   * Matrix encoding the local-space coordinates of the model.
   */
  GraphicsMat localVertexData;

  /**
   * The number of vertices this model contains.
   */
  int vertexCount;

  /**
   * Mat4 that has all previous transformations (except for rotations) that have been applied to,
   * this model encoded.
   */
  Mat4 transformMatrix;

  /**
   * Flag keeping track of whether a new transformation has been added since last call to 
   * getTransformedVertexMat().
   */
  bool seenNewTransform;



};

////////////////////////////////////////////////////////////////////////////////////////////////////