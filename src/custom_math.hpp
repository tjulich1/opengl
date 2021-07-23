// Trent Julich ~ 21 July 2021

#ifndef CUSTOM_MATH_HPP
#define CUSTOM_MATH_HPP

namespace custom_math {
  /**
   * Class representing a 4D vector used in graphics programming.
   */
  class Vec4 {
  public:
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

  private:
    /* * * * * * * * *
    * Member fields *
    * * * * * * * * */
    float x;
    float y;
    float z;
    float w;
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

    /* * * * * * *
    * Mutators  *
    * * * * * * */
    void setElement(int col, int row, float value);

    /* * * * * * *
    * Accessors *
    * * * * * * */
    float getElement(int col, int row);

  private:
    /* * * * * * * * *
    * Member fields *
    * * * * * * * * */
    float values[16];
  };
}; 

#endif