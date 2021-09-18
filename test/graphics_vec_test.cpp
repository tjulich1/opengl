////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 20 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

// Included from src.
#include "graphics_vec.hpp"
#include "rng.hpp"
#include "custom_exceptions.hpp"
#include "transformation_builder.hpp"

#define BOOST_TEST_MODULE engine_test
// Included from external libraries.
#include <boost/test/included/unit_test.hpp>

#include <stdexcept>
#include <random>

namespace utf = boost::unit_test;

////////////////////////////////////////////////////////////////////////////////////////////////////

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
struct GraphicsVecFixture 
{
  GraphicsVecFixture() 
  {
    // Most operations are using 3D vectors, so use that initially. 
    vec = GraphicsVec(3);

    // Set the range of rng for floats to [0, 1] and ints to [0, 1000].
    generator = RandomNumberGenerator(-1.0f, 1.0f, 0, 1000);
  };

  ~GraphicsVecFixture() { };

  GraphicsVec vec;

  RandomNumberGenerator generator;
};

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * This test suite handles running tests of the GraphicsVec object.
 */
BOOST_FIXTURE_TEST_SUITE(graphics_vec_suite, GraphicsVecFixture)

BOOST_AUTO_TEST_CASE(test_empty_vec_constructor) 
{
  vec = GraphicsVec(0);
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
    float x = generator.getRandFloat();
    float y = generator.getRandFloat();
    float z = generator.getRandFloat();
    float w = generator.getRandFloat();
    vec = GraphicsVec(x, y, z, w);
    BOOST_TEST(vec.getX() == x);
    BOOST_TEST(vec.getY() == y);
    BOOST_TEST(vec.getZ() == z);
    BOOST_TEST(vec.getW() == w);
  } 
}

BOOST_AUTO_TEST_CASE(negative_get_element) 
{
  BOOST_CHECK_THROW(vec.getElement(-1), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(excess_get_element) 
{
  vec = GraphicsVec(1);
  // Index way above range of vector.
  BOOST_CHECK_THROW(vec.getElement(100000), std::out_of_range);
}

BOOST_AUTO_TEST_CASE(negative_constructor_size)
{
  BOOST_CHECK_THROW(GraphicsVec vec(-1), std::invalid_argument);
}

BOOST_AUTO_TEST_CASE(three_element_constructor) 
{
  for (int i = 0; i < NUM_CASES; i++) {
    float x = generator.getRandFloat();
    float y = generator.getRandFloat();
    float z = generator.getRandFloat();
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
    float x = generator.getRandFloat();
    vec.setX(x);
    BOOST_TEST(vec.getX() == x);
  }
}

BOOST_AUTO_TEST_CASE(test_set_y) 
{
  for (int i = 0; i < NUM_CASES; i++) {
    float y = generator.getRandFloat();
    vec.setY(y);
    BOOST_TEST(vec.getY() == y);
  }
}

BOOST_AUTO_TEST_CASE(test_set_z) 
{
  for (int i = 0; i < NUM_CASES; i++) {
    float z = generator.getRandFloat();
    vec.setZ(z);
    BOOST_TEST(vec.getZ() == z);
  }
}

BOOST_AUTO_TEST_CASE(test_set_w) 
{
  vec = GraphicsVec(4);
  for (int i = 0; i < NUM_CASES; i++) {
    float w = generator.getRandFloat();
    vec.setW(w);
    BOOST_TEST(vec.getW() == w);
  }
}

BOOST_AUTO_TEST_CASE(test_normalize_already_unit_vec, * utf::tolerance(TOLERANCE)) 
{
  vec = GraphicsVec(1);
  vec.setX(1.0f);
  vec = vec.normalize();
  BOOST_TEST(vec.getEuclideanLength() == 1.0f);
}

BOOST_AUTO_TEST_CASE(test_normalize_already_unit_vec_2, * utf::tolerance(TOLERANCE))
{
  vec = GraphicsVec(2);
  vec.setX(-0.979589);
  vec.setY(0.2);
  vec = vec.normalize();
  BOOST_TEST(vec.getEuclideanLength() == 1.0f);
}

BOOST_AUTO_TEST_CASE(test_normalize_2D, * utf::tolerance(TOLERANCE))
{
  vec = GraphicsVec(2);
  vec.setX(185);
  vec.setY(34);
  vec = vec.normalize();
  BOOST_TEST(vec.getEuclideanLength() == 1.0f);
}

BOOST_AUTO_TEST_CASE(test_normalize_2D_both_neg, * utf::tolerance(TOLERANCE))
{
  vec = GraphicsVec(2);
  vec.setX(-2043);
  vec.setY(-39);
  vec = vec.normalize();
  BOOST_TEST(vec.getEuclideanLength() == 1.0f);
}

BOOST_AUTO_TEST_CASE(test_normalize_2D_mismatch) 
{
  vec = GraphicsVec(2);
  vec.setX(-1000.0f);
  vec.setY(1275.0f);
  vec = vec.normalize();
  BOOST_TEST(vec.getEuclideanLength() == 1.0f);
}

BOOST_AUTO_TEST_CASE(normalize_large_vecs_small_values, * utf::tolerance(TOLERANCE))
{
  for (int curCase = 0; curCase < NUM_CASES; curCase++) {

    // Fill vector of length 1000 with random values 
    vec = GraphicsVec(1000);
    for (int i = 0; i < 1000; i++) {
      vec.setElement(i, generator.getRandFloat());
    }
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_large_vecs_large_values, * utf::tolerance(TOLERANCE))
{
  for (int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(1000);
    for (int j = 0; j < 1000; j++) {
      vec.setElement(j, generator.getRandFloat());
    }   
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_single_small_element, * utf::tolerance(TOLERANCE)) 
{
  generator.setFloatRange(0.0f, 1.0f);
  for(int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(1);
    vec.setElement(0, generator.getRandFloat());
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_single_large_element, * utf::tolerance(TOLERANCE))
{
  generator.setFloatRange(-100000, 100000);
  for (int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(1);
    vec.setElement(0, generator.getRandFloat());
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_single_small_negative, * utf::tolerance(TOLERANCE)) 
{
  generator.setFloatRange(-1.0, 0);
  for (int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(1);
    vec.setElement(0, generator.getRandFloat());
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_2D_small_elements, * utf::tolerance(TOLERANCE))
{
  generator.setFloatRange(-1.0, 1.0);
  for (int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(2);
    vec.setElement(0, generator.getRandFloat());
    vec.setElement(1, generator.getRandFloat());
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_2D_large_elements, * utf::tolerance(TOLERANCE))
{
  generator.setFloatRange(-1000000, 1000000);
  for (int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(2);
    vec.setElement(0, generator.getRandFloat());
    vec.setElement(1, generator.getRandFloat());
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_3D_small_elements, * utf::tolerance(TOLERANCE))
{
  generator.setFloatRange(-1.0, 1.0);
  for (int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(3);
    vec.setElement(0, generator.getRandFloat());
    vec.setElement(1, generator.getRandFloat());
    vec.setElement(2, generator.getRandFloat());
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_3D_large_elements, * utf::tolerance(TOLERANCE))
{
  generator.setFloatRange(-1000000, 1000000);
  for (int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(3);
    vec.setElement(0, generator.getRandFloat());
    vec.setElement(1, generator.getRandFloat());
    vec.setElement(2, generator.getRandFloat());
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_4D_small_elements, * utf::tolerance(TOLERANCE))
{
  generator.setFloatRange(-1.0, 1.0);
  for (int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(4);
    vec.setX(generator.getRandFloat());
    vec.setY(generator.getRandFloat());
    vec.setZ(generator.getRandFloat());
    vec.setW(generator.getRandFloat());
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_4D_large_elements, * utf::tolerance(TOLERANCE))
{
  generator.setFloatRange(-1000000, 1000000);
  for (int i = 0; i < NUM_CASES; i++) {
    vec = GraphicsVec(4);
    vec.setElement(0, generator.getRandFloat());
    vec.setElement(1, generator.getRandFloat());
    vec.setElement(2, generator.getRandFloat());
    vec.setElement(3, generator.getRandFloat());
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_empty) 
{
  vec = GraphicsVec(0);
  BOOST_CHECK_THROW(vec.normalize(), InvalidOperationException);
}

BOOST_AUTO_TEST_CASE(normalize_all_negative, * utf::tolerance(TOLERANCE))
{
  const int VEC_SIZE = 100;
  vec = GraphicsVec(VEC_SIZE);
  generator.setFloatRange(-10000.0f, -1.0f);
  for (int i = 0; i < NUM_CASES; i++) {
    for (int j = 0; j < VEC_SIZE; j++) {
      vec.setElement(j, generator.getRandFloat());
    }
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(normalize_all_positive, * utf::tolerance(TOLERANCE))
{
  const int VEC_SIZE = 100;
  vec = GraphicsVec(VEC_SIZE);
  generator.setFloatRange(1.0f, 10000.0f);
  for (int i = 0; i < NUM_CASES; i++) {
    for (int j = 0; j < VEC_SIZE; j++) {
      vec.setElement(j, generator.getRandFloat());
    }
    vec = vec.normalize();
    BOOST_TEST(vec.getEuclideanLength() == 1.0f);
  }
}

BOOST_AUTO_TEST_CASE(cross_test_one, * utf::tolerance(TOLERANCE)) 
{
  vec = GraphicsVec(3, -3, 1);
  GraphicsVec vecTwo = GraphicsVec(4, 9, 2);
  GraphicsVec result = vec.cross(vecTwo);

  BOOST_TEST(result.getX() == -15.0f);
  BOOST_TEST(result.getY() == -2.0f);
  BOOST_TEST(result.getZ() == 39.0f);
}

BOOST_AUTO_TEST_CASE(cross_test_two, * utf::tolerance(TOLERANCE)) 
{
  vec = GraphicsVec(1.23f, 4.95f, 37.4f);
  GraphicsVec vecTwo = GraphicsVec(26.8f, 8.67f, 2.59f);
  GraphicsVec result = vec.cross(vecTwo);

  BOOST_TEST(result.getX() == -311.4375f);
  BOOST_TEST(result.getY() == 999.1343f);
  BOOST_TEST(result.getZ() == -121.9959f);
}

/**
 * Test of the star operator between a graphics vec and a Mat4.
 */
BOOST_AUTO_TEST_CASE(star_op_matrix_one, * utf::tolerance(TOLERANCE)) {
  vec = GraphicsVec(1.0f, 2.0f, 3.0f, 1.0f);

  Mat4 testMat = TransformationBuilder::scale(1.0, 2.0, 3.0);

  vec = vec * testMat;

  BOOST_TEST(vec.getX() == 1.0f);
  BOOST_TEST(vec.getY() == 4.0f);
  BOOST_TEST(vec.getZ() == 9.0f);
  BOOST_TEST(vec.getW() == 1.0f);
}

/**
 * Test of the star operator between a graphics vec and a Mat4.
 */
BOOST_AUTO_TEST_CASE(star_op_matrix_two, * utf::tolerance(TOLERANCE)) {
  vec = GraphicsVec(1.0f, 2.0f, 3.0f, 4.0f);

  Mat4 testMat = TransformationBuilder::Identity();

  testMat.setRow(0, GraphicsVec{1.0f, 5.0f, 17.0f, 0.0f});
  testMat.setRow(1, GraphicsVec{2.0f, 7.0f, -4.0f, 0.0f});
  testMat.setRow(2, GraphicsVec{3.0f, 3.0f, 12.0f, 0.0f});
  testMat.setRow(3, GraphicsVec{4.0f, 2.0f, -1.0f, 1.0f});

  vec = vec * testMat;

  BOOST_TEST(vec.getX() == 30.0f);
  BOOST_TEST(vec.getY() == 36.0f);
  BOOST_TEST(vec.getZ() == 41.0f);
  BOOST_TEST(vec.getW() == 4.0f);
}

/**
 * Test of the graphics vector dot product method.
 */
BOOST_AUTO_TEST_CASE(dot_test_one, * utf::tolerance(TOLERANCE)) {
  vec = GraphicsVec(1.0f, 2.0f, 3.0f, 4.0f);
  GraphicsVec theOther(1.0f, 2.0f, 3.0f, 4.0f);
  float theDot = vec.dot(theOther);
  BOOST_TEST(theDot == 30.0f);
}

/**
 * Test of the graphics vector dot product method.
 */
BOOST_AUTO_TEST_CASE(dot_test_two, * utf::tolerance(TOLERANCE)) {
  generator.setIntRange(1, 100);
  generator.setFloatRange(-100.0f, 100.0f);

  for (int caseNum = 0; caseNum < NUM_CASES; caseNum++) {
    const int vecSize = generator.getRandInt();
    float dotProduct = 0.0f;

    vec = GraphicsVec(vecSize);
    GraphicsVec other = GraphicsVec(vecSize);

    // Populate each vector and compute what the dot product should be.
    for (int i = 0; i < vecSize; i++) {
      const float firstVal  = generator.getRandFloat();
      const float secondVal = generator.getRandFloat();
    
      dotProduct += firstVal * secondVal;
      vec.setElement(i, firstVal);
      other.setElement(i, secondVal);
    }

    BOOST_TEST(vec.dot(other) == dotProduct);
  }
}

/**
 * Test of Graphics vec getSize method.
 */
BOOST_AUTO_TEST_CASE(get_size_test, * utf::tolerance(TOLERANCE)) {
  generator.setIntRange(1, 1000);
  for (int caseNum = 0; caseNum < NUM_CASES; caseNum++) {
    const int vecSize = generator.getRandInt();
    vec = GraphicsVec(vecSize);

    BOOST_TEST(vec.getSize() == vecSize);
  }
}

BOOST_AUTO_TEST_SUITE_END()

////////////////////////////////////////////////////////////////////////////////////////////////////