// Trent Julich ~ 21 July 2021

#ifndef CUSTOM_MATH_HPP
#define CUSTOM_MATH_HPP

#include <iostream>
#include <string>
#include <gl/GL.h>
#include <array>

namespace custom_math {
  /**
   * Class representing a 4D vector used in graphics programming.
   */
  class Vec4 {
  public:

    static const int MAX_ELEMENTS = 4;

    /* * * * * * * * *
    * Constructors  *
    * * * * * * * * */
    Vec4();
    Vec4(float x, float y, float z, float w);
    Vec4(float initialValue);

    /* * * * * * *
    * Mutators  *
    * * * * * * */
    void setX(float newX);
    void setY(float newY);
    void setZ(float newZ);
    void setW(float newW);

    /* * * * * * *
    * Accessors *
    * * * * * * */
    float getX();
    float getY();
    float getZ();
    float getW();
    float getElement(int element);

  private:
    /* * * * * * * * *
    * Member fields *
    * * * * * * * * */
    float values[MAX_ELEMENTS];
  };

  /**
   * Class representing a 4x4 matrix used for transformations in graphics programming.
   */
  class Mat4 {
  public:
    /* * * * * * * * *
    * Constructors  *
    * * * * * * * * */
    Mat4();
    Mat4(float initialValue);

    static Mat4 Identity();
    static Mat4 Translation(float xTranslate, float yTranslate, float zTranslate);
    static Mat4 Scale(float xFactor, float yFactor, float zFactor);
    static Mat4 XRotation(int angleOfRotation);
    static Mat4 YRotation(int angleOfRotation);
    static Mat4 ZRotation(int angleOfRotation);
    static Mat4 RotateFromAxisAngle(int angleOfRotation, Vec4 axis);

    /* * * * * * *
    * Mutators  *
    * * * * * * */
    void setElement(int col, int row, float value);
    void setRow(int row, Vec4 rowValues);

    /* * * * * * *
    * Accessors *
    * * * * * * */
    float getElement(int col, int row) const;
    GLfloat* getFloats(GLfloat dest[]);

    Mat4 operator*(const Mat4& other);

  private:
    /* * * * * * * * *
    * Member fields *
    * * * * * * * * */
    float values[16];
  };
}; 

std::ostream& operator<< (std::ostream& stream, const custom_math::Mat4& matrix);

#endif