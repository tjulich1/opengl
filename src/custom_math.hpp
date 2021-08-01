////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 21 July 2021                                                                    */
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <gl/GL.h>
#include <array>

////////////////////////////////////////////////////////////////////////////////////////////////////

namespace custom_math 
{
  /**
   * Class representing a 4D vector used in graphics programming.
   */
  class Vec4 
  {
  public:
    static const int MAX_ELEMENTS = 4;

    /**
     * Default constructor, sets all elements equal to zero.
     */
    Vec4();

    /**
     * Constructor which initializes all elements to the same initial value.
     * 
     * initialValue: The value to initialize with.
     */
    Vec4(float initialValue);

    /**
     * Constructor which initializes Vec4 with given arguments.
     * 
     * x, y, z, w: initial values for corresponding elements.
     */
    Vec4(float x, float y, float z, float w);

    /**
     * Returns a new Vec4 containing the same elements as the Vec4 the method was called on.
     */
    Vec4 copy();

    /**
     * Calculates the cross product between the two vectors. 
     * 
     * other: The other matrix involved in the cross product. This matrix will be on the right hand
     *        side.
     */
    Vec4 cross(Vec4 other);

    /**
     * Turns a Vec4 into a unit vector, dividing each element by the original length of the vector.
     */
    void normalize();

    /**
     * Sets the Vec4's x element.
     * 
     * newX: New x element value.
     */
    inline void setX(float newX) { values[0] = newX; }

    /**
     * Sets the Vec4's y element.
     * 
     * newY: New y element value.
     */
    inline void setY(float newY) { values[1] = newY; }

    /**
     * Sets the Vec4's z element.
     * 
     * newZ: New z element value.
     */
    inline void setZ(float newZ) { values[2] = newZ; }

    /**
     * Sets the Vec4's w element.
     * 
     * newW: New w element value.
     */
    inline void setW(float newW) { values[3] = newW; }

    /**
     * Returns the Vec4's current x value.
     */
    inline float getX() { return values[0]; }

    /**
     * Returns the Vec4's current y value.
     */
    inline float getY(){ return values[1]; }

    /**
     * Returns the Vec4's current z value.
     */
    inline float getZ() { return values[2]; }

    /**
     * Returns the Vec4's current w value.
     */
    inline float getW(){ return values[3]; }

    /**
     * Used to access the Vec4's elements by index. Takes an index within [0, 3] inclusive. If an 
     * index outside this range is provided, an arbitrary value will be returned.
     * 
     * element: Index of the element to access.
     */
    inline float getElement(int element) 
    {
      float result = 0;
      if (element >= 0 && element < MAX_ELEMENTS) {
        result = values[element];
      }
      return result;
    }

  private:
    /**
     * Simple float array containing the elements of the Vec4.
     */
    float values[MAX_ELEMENTS];
  };

  /**
   * Class representing a 4x4 matrix used for transformations in graphics programming.
   */
  class Mat4 
  {
  public:
    /**
     * Default constructor, initializes all matrix elements to zero.
     */
    Mat4();

    /**
     * Constructor which sets all elements of the matrix to the same value.
     * 
     * initialValue: The value to initialize the matrix with.
     */
    Mat4(float initialValue);
    
    /**
     * Factory method used to generate Identity matrices, or matrices with the value 1 along the 
     * diagonal (from top left to bottom right).
     */
    static Mat4 Identity();
    
    /**
     * Factory method used to generate LookAt matrices. When this matrix is multiplied with a model 
     * matrix, it 
     */
    static Mat4 LookAt(Vec4 cameraPosition, Vec4 viewDirection);

    /**
     * Sets a single element within the Mat4.
     * 
     * col:   Column of element to set.
     * row:   Row of element to set.
     * value: The value to assign to the element.
     */
    void setElement(int col, int row, float value);
    
    /**
     * Sets an entire row of the Mat4 using values from a Vec4.
     * 
     * row:       The row to set.
     * rowValues: Vec4 containing values to assign to elements.
     */
    void setRow(int row, Vec4 rowValues);

    /**
     * Retrieves an element from the Mat4.
     * 
     * col: Column of element to retrieve.
     * row: Row of element to retrieve.
     */
    float getElement(int col, int row) const;

    /**
     * Fills an array with the values stored in the Mat4.
     * 
     * dest: GLfloat array to store the values into.
     */
    GLfloat* getFloats(GLfloat dest[]);

    /**
     * Override of the * operator. When used, it will perform matrix multiplication between the 
     * two matrices.
     * 
     * other: The other matrix to multiply with.
     */
    Mat4 operator*(const Mat4& other);

  private:
    /**
     * Array containing the float values of the 4x4 matrix.  
     */
    float values[16];
  };
}; 

/**
 * Override of the << operator, used to put a representation of the Mat4 to the output stream.
 * 
 * matrix: Matrix to print to output.
 * stream: Output stream to write to.
 */
std::ostream& operator<< (std::ostream& stream, const custom_math::Mat4& matrix);

////////////////////////////////////////////////////////////////////////////////////////////////////