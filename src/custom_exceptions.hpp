////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 7 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <exception>
#include <string>

#pragma once

////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * Exception that is thrown when a method is called on an object that's state doesn't currently
 * support calling the method.
 */
struct InvalidOperationException : public std::exception
{

  /**
   * Additional message that is displayed after the exception type (if a message is supplied).
   */
  std::string exceptionMessage;

  /**
   * Constructor for new InvalidOperationException. Takes optional message to display in order to 
   * provide more information to cause of exception.
   * 
   * @param message Optional string containing additional information related to cause of exception.
   */
  InvalidOperationException(std::string message = 0) 
  {
    exceptionMessage = message;
  }

	const char * what () const throw ()
  {
    std::string result = "Invalid Operation Exception";
    if (!exceptionMessage.empty()) {
      result += (": " + exceptionMessage);
    } 
    return result.c_str();
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////