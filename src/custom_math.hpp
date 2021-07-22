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
    Vec4(int x, int y, int z, int w);
    Vec4(int initialValue);

    /* * * * * * *
    * Mutators  *
    * * * * * * */
    void setX(int newX);
    void setY(int newY);
    void setZ(int newZ);
    void setW(int newW);

    /* * * * * * *
    * Accessors *
    * * * * * * */
    int getX();
    int getY();
    int getZ();
    int getW();

  private:
    /* * * * * * * * *
    * Member fields *
    * * * * * * * * */
    int x;
    int y;
    int z;
    int w;
  };

  /**
   * Class representing a 4x4 matrix used for transformations in graphics programming.
   */
  class Mat4 {
  public:

  };
}; 

#endif