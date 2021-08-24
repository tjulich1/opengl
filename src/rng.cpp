////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 23 August 2021                                                                  */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <chrono>

// Included from src.
#include "rng.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

RandomNumberGenerator::RandomNumberGenerator(float initialFloatMin, float initialFloatMax, 
                                              int initialIntMin, int initialIntMax)
{
  std::random_device randDevice;
  
  float defMaxAsFloat = static_cast<float>(DEFAULT_MAX);
  float defMinAsFloat = static_cast<float>(DEFAULT_MIN);

  /** 
   * Check if initial mins/maxs differ from the defaults, and initialize member mins/maxs
   * accordingly.
   */
  minFloat = initialFloatMin != defMinAsFloat ? initialFloatMin : defMinAsFloat;
  maxFloat = initialFloatMax != defMaxAsFloat ? initialFloatMax : defMaxAsFloat;
  minInt = initialIntMin != DEFAULT_MIN ? initialIntMin : DEFAULT_MIN;
  maxInt = initialIntMax != DEFAULT_MAX ? initialIntMax : DEFAULT_MAX;

  // Initialize and seed random device.
  randEngine = std::default_random_engine(randDevice());
  randEngine.seed(std::chrono::system_clock::now().time_since_epoch().count());

  // Initialize float distribution with range [minFloat, maxFloat] exclusive.
  setFloatRange(minFloat, maxFloat);

  // Initialize int distribution with range [minInt, maxInt] exclusive.
  setIntRange(minInt, maxInt);
}

////////////////////////////////////////////////////////////////////////////////////////////////////