////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 16 September 2021                                                               */
////////////////////////////////////////////////////////////////////////////////////////////////////

// Included from src.
#include "mat4.hpp"
#include "rng.hpp"

// Included from external libraries.
#include <boost/test/unit_test.hpp>

#include <stdexcept>

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
      randomVals.push_back(randVal);
    }
    
    GraphicsVec theColumn = mat.getCol(col);
    for (int j = 0; j < 4; j++) {
      BOOST_TEST(theColumn.getElement(j) == randomVals.at(j));
    }
  }
}

BOOST_AUTO_TEST_CASE(test_get_row_valid) 
{
  generator.setFloatRange(-100.0f, 100.0f);
  generator.setIntRange(0, 3);

  for (int i = 0; i < NUM_CASES; i++) {
    const int row = generator.getRandInt();
    std::vector<float> randomVals;
    for (int j = 0; j < 4; j++) {
      float randVal = generator.getRandFloat();
      mat.setElement(j, row, randVal);
      randomVals.push_back(randVal);
    }
    
    GraphicsVec theRow = mat.getRow(row);
    for (int j = 0; j < 4; j++) {
      BOOST_TEST(theRow.getElement(j) == randomVals.at(j));
    }
  }
}

BOOST_AUTO_TEST_CASE(test_mult_mat4) 
{
  generator.setFloatRange(-100.0f, 100.0f);
  generator.setIntRange(0, 3);

  Mat4 other;
  
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    for (int col = 0; col < 4; col++) {
      for (int row = 0; row < 4; row++) {
        mat.setElement(col, row, generator.getRandFloat());
        other.setElement(col, row, generator.getRandFloat());
      }
    }
    Mat4 result = mat * other;

    // Test 5 random elements in the result vector.
    for (int test = 0; test < 5; test++) {
      const int row = generator.getRandInt();
      const int col = generator.getRandInt();
      BOOST_TEST(mat.getRow(row).dot(other.getCol(col)) == result.getElement(col, row));
    }
  }
}

/**
 * Test to ensure indices < 0 passed to getCol raise an exception. 
 */
BOOST_AUTO_TEST_CASE(get_col_negative) 
{
  generator.setIntRange(-10000, -1);
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    BOOST_CHECK_THROW(mat.getCol(generator.getRandInt()), std::out_of_range);
  }
}

/**
 * Test to ensure indices > 3 passed to getCol raise an exception.
 */
BOOST_AUTO_TEST_CASE(get_col_excess) 
{
  generator.setIntRange(4, 10000);
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    BOOST_CHECK_THROW(mat.getCol(generator.getRandInt()), std::out_of_range);
  }
}

/**
 * Test to ensure indices < 0 passed to getRow raise an exception.
 */
BOOST_AUTO_TEST_CASE(get_row_negative) 
{
  generator.setIntRange(-10000, -1);
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    BOOST_CHECK_THROW(mat.getRow(generator.getRandInt()), std::out_of_range);
  }
}

/**
 * Test to ensure indices > 3 passed to getRow raise an exception.
 */
BOOST_AUTO_TEST_CASE(get_row_excess) 
{
  generator.setIntRange(4, 10000);
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    BOOST_CHECK_THROW(mat.getRow(generator.getRandInt()), std::out_of_range);
  }
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////////////////////////