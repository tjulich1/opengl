////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 7 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <vector>

/**
 * Class adding operations to vector that are needed for graphics transformations.
 */
class GraphicsVec 
{
public:

  /**
   * Default constructor for empty graphics vector.
   */
  GraphicsVec();

  /**
   * Constructor which takes the size of the desired vector.
   */
  GraphicsVec(int size);

  /**
   * Constructor for 3D vector, taking intial values for each element.
   */
  GraphicsVec(float x, float y, float z);

  /**
   * Constructor for 4D vector, taking initial values for each element.
   */
  GraphicsVec(float x, float y, float z, float w);

  /**
   * Method used to get the size of the vector.
   */
  int getSize();

  /**
   * Accesses the vector element corresponding to its x component. Vector must have size at least 
   * 1 to access x element.
   *
   * returns: x component of vector. 
   */
  float getX();

  /**
   * Accesses the vector element corresponding to its y component. Vector must have size at least 
   * 2 to access y element.
   *
   * returns: y component of vector. 
   */
  float getY();

  /**
   * Accesses the vector element corresponding to its z component. Vector must have size at least 
   * 3 to access z element.
   *
   * returns: z component of vector. 
   */
  float getZ();

  /**
   * Accesses the vector element corresponding to its w component. Vector must have size at least 
   * 4 to access w element.
   *
   * returns: w component of vector. 
   */
  float getW();

  /**
   * Method used to assign a new value to the vectors x component. Vector must have size at least 1.
   * 
   * newX: The value to assign to the x component.
   */
  void setX(float newX);

  /**
   * Method used to assign a new value to the vectors y component. Vector must have size at least 2.
   * 
   * newY: The value to assign to the y component.
   */
  void setY(float newY);
  
  /**
   * Method used to assign a new value to the vectors z component. Vector must have size at least 3.
   * 
   * newZ: The value to assign to the z component.
   */
  void setZ(float newZ);

  /**
   * Method used to assign a new value to the vectors w component. Vector must have size at least 4.
   * 
   * newW: The value to assign to the w component.
   */
  void setW(float newW);

private:

  /**
   * Number of elements in the vector.
   */
  int numElements;

  /**
   * Vector that holds the 
   */
  std::vector<float> elements; 
};

////////////////////////////////////////////////////////////////////////////////////////////////////