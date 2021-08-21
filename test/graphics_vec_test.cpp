////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 20 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

// Included from src.
#include "graphics_vec.hpp"

#define BOOST_TEST_MODULE engine_test
// Included from external libraries.
#include <boost/test/included/unit_test.hpp>

#include <stdexcept>
#include <cstdlib>

// TEMP
#include <iostream>

struct GraphicsVecFixture {
  
  GraphicsVecFixture() 
  {
    // Most operations are using 3D vectors, so use that initially. 
    vec = GraphicsVec(3);
  };

  ~GraphicsVecFixture() 
  {

  };

  GraphicsVec vec;

  /*
   * Change this number to run more cases for some tests, usually involving calling a single method
   * many times with different random values.
   */
  const int NUM_CASES = 100;
};

// Helper method that returns a random value between 0.0f and 1.0f inclusive.
float getRand() 
{
  return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

BOOST_FIXTURE_TEST_SUITE(graphics_vec_suite, GraphicsVecFixture)

BOOST_AUTO_TEST_CASE(test_empty_vec_constructor) 
{
  vec = GraphicsVec(0);

  std::cout << "SHOULD BE SIZE 0: " << vec.getSize() << std::endl;

  BOOST_TEST(vec.getSize() == 0);
}

BOOST_AUTO_TEST_CASE(empty_access_x) 
{
  GraphicsVec vec(0);
  BOOST_CHECK_THROW(vec.getX(), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(single_element_constructor) 
{
  vec = GraphicsVec(1);

  // Should have single element
  BOOST_TEST(vec.getSize() == 1);
}

BOOST_AUTO_TEST_CASE(test_initial_value)
{
  // All elements should initially be zero when using vec = GraphicsVec(N)
  for (int i = 0; i < vec.getSize(); i++) {
    BOOST_TEST(vec.getElement(i) == 0.0f);
  }
}

BOOST_AUTO_TEST_CASE(test_four_element_constructor) 
{ 
  for (int i = 0; i < NUM_CASES; i++) {
    float x = getRand();
    float y = getRand();
    float z = getRand();
    float w = getRand();
    vec = GraphicsVec(x, y, z, w);
    BOOST_TEST(vec.getX() == x);
    BOOST_TEST(vec.getY() == y);
    BOOST_TEST(vec.getZ() == z);
    BOOST_TEST(vec.getW() == w);
  } 
}

BOOST_AUTO_TEST_CASE(negative_constructor_size)
{
  BOOST_CHECK_THROW(GraphicsVec vec(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(three_element_constructor) 
{
  for (int i = 0; i < NUM_CASES; i++) {
    float x = getRand();
    float y = getRand();
    float z = getRand();
    vec = GraphicsVec(x, y, z);
    BOOST_TEST(vec.getX() == x);
    BOOST_TEST(vec.getY() == y);
    BOOST_TEST(vec.getZ() == z);
    BOOST_CHECK_THROW(vec.getW(), std::out_of_range);
  }
}

BOOST_AUTO_TEST_CASE(test_set_x) 
{
  for (int i = 0; i < NUM_CASES; i++) {
    float x = getRand();
    vec.setX(x);
    BOOST_TEST(vec.getX() == x);
  }
}

BOOST_AUTO_TEST_CASE(test_set_y) 
{
  for (int i = 0; i < NUM_CASES; i++) {
    float y = getRand();
    vec.setY(y);
    BOOST_TEST(vec.getY() == y);
  }
}

BOOST_AUTO_TEST_CASE(test_set_z) 
{
  for (int i = 0; i < NUM_CASES; i++) {
    float z = getRand();
    vec.setZ(z);
    BOOST_TEST(vec.getZ() == z);
  }
}

BOOST_AUTO_TEST_CASE(test_set_w) 
{
  vec = GraphicsVec(4);
  for (int i = 0; i < NUM_CASES; i++) {
    float w = getRand();
    vec.setW(w);
    BOOST_TEST(vec.getW() == w);
  }
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////////////////////////