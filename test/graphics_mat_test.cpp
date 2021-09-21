////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 20 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

// Included from src.
#include "rng.hpp"
#include "graphics_mat.hpp"

// Included from external libraries.
#include <boost/test/unit_test.hpp>

/**
 * SET THE NUMBER OF TESTS TO RUN FOR CERTAIN TESTS, I.E. 100 RANDOM TESTS OF METHOD XYZ.
 */
const int NUM_CASES = 100;

/**
 * The amount by which a value can be off from the expected value and still be acceptable.
 */
const float TOLERANCE = 0.00001;

/**
 * Test fixture for graphics vec tests. Reinitializes a 3D vector before each test runs.
 */
struct GraphicsMatFixture 
{
  GraphicsMatFixture() 
  {
    mat = GraphicsMat(4);

    // Set the range of rng for floats to [0, 1] and ints to [0, 1000].
    generator = RandomNumberGenerator(-1.0f, 1.0f, 0, 1000);
  };

  ~GraphicsMatFixture() { };

  GraphicsMat mat = GraphicsMat(4);

  RandomNumberGenerator generator;
};

/**
 * This test suite handles running tests of the GraphicsMat object.
 */
BOOST_FIXTURE_TEST_SUITE(graphics_mat_suite, GraphicsMatFixture)

BOOST_AUTO_TEST_CASE(test_empty_constructor) 
{
  mat = GraphicsMat();
  BOOST_TEST(mat.getCols() == 0);
  BOOST_TEST(mat.getRows() == 0);
}

BOOST_AUTO_TEST_CASE(test_constructor_col) 
{
  generator.setIntRange(1, 1000);
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    const int randCol = generator.getRandInt();
    mat = GraphicsMat(randCol);
    BOOST_TEST(mat.getCols() == randCol);
    BOOST_TEST(mat.getRows() == 0);
  }
}

BOOST_AUTO_TEST_CASE(test_constructor_negative_col) {
  generator.setIntRange(-100, -1);
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    const int randCol = generator.getRandInt();
    BOOST_CHECK_THROW(mat = GraphicsMat(randCol), std::invalid_argument);
  }
}

BOOST_AUTO_TEST_CASE(test_set_element_valid) 
{
  // Range for indices in matrix.
  generator.setIntRange(0, 99);
  
  // Range for generated values to set in matrix.
  generator.setFloatRange(-1000.0f, 1000.0f);

  // Initialize matrix to hold 100 columns of values.
  mat = GraphicsMat(100);

  // Add 100 rows filled with zeros to start.
  for (int i = 0; i < 100; i++) {
    mat.addRow(GraphicsVec(0));
  }
  
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    const int randRow = generator.getRandInt();
    const int randCol = generator.getRandInt();
    const float randVal = generator.getRandFloat();
    mat.setElement(randCol, randRow, randVal);
    BOOST_TEST(mat.getElement(randCol, randRow) == randVal);
  }
}

BOOST_AUTO_TEST_CASE(test_set_element_negative_row) 
{
  generator.setIntRange(-100, -1);

  for (int curCase = 0; curCase < NUM_CASES; curCase++) {
    BOOST_CHECK_THROW(mat.setElement(0, generator.getRandInt(), 0.0f), std::out_of_range);
  }
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////////////////////////