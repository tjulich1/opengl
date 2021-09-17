////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 16 September 2021                                                               */
////////////////////////////////////////////////////////////////////////////////////////////////////

// Included from src.
#include "mat4.hpp"
#include "rng.hpp"

#include <boost/test/unit_test.hpp>
#include <iostream>

namespace utf = boost::unit_test;

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * The amount by which a value can be off from the expected value and still be acceptable.
 */
const float TOLERANCE = 0.00001;

/**
 * SET THE NUMBER OF TESTS TO RUN FOR CERTAIN TESTS, I.E. 100 RANDOM TESTS OF METHOD XYZ.
 */
const int NUM_CASES = 100;

struct Mat4Fixture 
{
  Mat4Fixture() 
  {
    mat = Mat4();
  }

  Mat4 mat;

  RandomNumberGenerator generator;

};

BOOST_FIXTURE_TEST_SUITE(mat4_test_suite, Mat4Fixture)

BOOST_AUTO_TEST_CASE(test_empty_mat_constructor, * utf::tolerance(TOLERANCE)) 
{
  // Check that the default constructor initialized matrix with all zeros.
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      BOOST_TEST(mat.getElement(i, j) == 0.0f);
    }
  }
}

BOOST_AUTO_TEST_CASE(test_initial_value_positive, * utf::tolerance(TOLERANCE)) 
{
  generator.setFloatRange(1.0f, 1000.0f);
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    const float randValue = generator.getRandFloat();
    mat = Mat4(randValue);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        BOOST_TEST(mat.getElement(i, j) == randValue);
      }
    }
  }
}

BOOST_AUTO_TEST_CASE(test_initial_value_negative, * utf::tolerance(TOLERANCE)) 
{
  generator.setFloatRange(-1000.0f, -1.0f);
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    const float randValue = generator.getRandFloat();
    mat = Mat4(randValue);
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; j++) {
        BOOST_TEST(mat.getElement(i, j) == randValue);
      }
    }
  }
}

BOOST_AUTO_TEST_CASE(test_get_col_valid) 
{
  generator.setFloatRange(-100.0f, 100.0f);
  generator.setIntRange(0, 3);
  
  for (int i = 0; i < NUM_CASES; i++) {
    const int col = generator.getRandInt();
    std::vector<float> randomVals;
    for (int j = 0; j < 4; j++) {
      float randVal = generator.getRandFloat();
      mat.setElement(col, j, randVal);
      std::cout << "Value written: " << mat.getElement(col, j) << std::endl;
      randomVals.push_back(randVal);
    }
    
    GraphicsVec theColumn = mat.getCol(col);
    for (int j = 0; j < 4; j++) {
      BOOST_TEST(theColumn.getElement(j) == randomVals.at(j));
    }
  }
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////////////////////////