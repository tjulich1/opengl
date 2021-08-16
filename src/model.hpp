////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 12 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "graphics_mat.hpp"
#include "graphics_vec.hpp"
#include "mat4.hpp"

#include <vector>
#include <gl/GL.h>

////////////////////////////////////////////////////////////////////////////////////////////////////

class Model 
{
public:

  /**
   * Constructor for empty model object.
   */
  Model();

  /**
   * Constructor for model that should be rendered with the given vertex data. 
   * 
   * vertices: Array of GLfloats, with each consecutive group of 3 numbers corresponding to a single
   *           model vertex. If numValues % 3 != 0, any remaining values will not be used.
   * 
   * numValues: The number of data points in the given buffer. 
   */
  Model(GLfloat* vertexBuffer, int numValues);

  /**
   * Used to get a matrix containing vertex information of the model in its local coordinate space.
   * 
   * returns: Local-space coordinates of model encoded in matrix.
   */
  GraphicsMat getVertexMat();

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
   * Mat4 that has all previous transformations that have been applied to this model encoded.
   */
  Mat4 transformMatrix;

  /**
   * Flag keeping track of whether a new transformation has been added since last call to 
   * getTransformedVertexMat().
   */
  bool seenNewTransform;
};

////////////////////////////////////////////////////////////////////////////////////////////////////