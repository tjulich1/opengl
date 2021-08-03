////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 1 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <glew.h>
#include <iostream>
#include <string>
#include <vector>

/**
 * Included from src.
 */
#include "camera.hpp"
#include "custom_math.hpp"
#include "engine.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "transformation_builder.hpp"
#include "util.hpp"
#include "frustum.hpp"

////////////////////////////////////////////////////////////////////////////////////////////////////

int create_vertex_shader(GLuint shaderProgram);
int create_fragment_shader(GLuint shaderProgram);

////////////////////////////////////////////////////////////////////////////////////////////////////

Engine::Engine(SDL_Window* window) 
{
  mainWindow = window;
}

void Engine::start()
{
  shaderProgram = glCreateProgram();
  if (create_fragment_shader(shaderProgram) && create_vertex_shader(shaderProgram)) {
    glLinkProgram(shaderProgram);
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    // Check if the shader program linked successfully.
    if (!success) {
      std::cout << "Failed to link program" << std::endl;
    } else {
      // Generate a single VAO object.
      unsigned int VAO;
      glGenVertexArrays(1, &VAO);

      // Set the VAO as the current one.
      glBindVertexArray(VAO);

      // Change color used to clear buffer.
      glClearColor(0.2, 0.0, 0.0, 1.0);
    
////////////////////////////////////////////////////////////////////////////////////////////////////

      /*
        * Setup model vertex data.
        */ 
      custom_math::Mat4 testTriangle;
      
      // Triangle with base at bottom of screen.
      custom_math::Vec4 firstPoint(-1.0f, -1.0f, 0.0f, 1.0f);
      custom_math::Vec4 secondPoint(1.0f, -1.0f, 0.0f, 1.0f);
      custom_math::Vec4 thirdPoint(0.0f, 1.0f, 0.0f, 1.0f);

      std::vector<custom_math::Vec4> testList{firstPoint, secondPoint, thirdPoint};
      Model testModel(testList);
      testModel.listVertices();

      testTriangle.setRow(0, firstPoint);
      testTriangle.setRow(1, secondPoint);
      testTriangle.setRow(2, thirdPoint);
      testTriangle.setElement(3, 3, 1);

////////////////////////////////////////////////////////////////////////////////////////////////////

      /*
        * Values for transforming the model.
        */
      float translateX = -0.2f;
      float translateY = 0.0f;
      float translateZ = 0.0f;

      float scaleX = 1.0f;
      float scaleY = 2.0f;
      float scaleZ = 1.0f;

      int rotationAngle = 0;

////////////////////////////////////////////////////////////////////////////////////////////////////

      TransformationBuilder transformer;
      Camera camera(0, 1, 1, 0, 0, 0);

      Frustum testFrustum(-1.0f, 1.0f, 1.0f, -1.0f, 0.1, 100);
      custom_math::Mat4 perspectiveMatrix = testFrustum.createPerspectiveMatrix();

      custom_math::Mat4 testTranslate = 
        transformer.translation(translateX, translateY, translateZ);

      custom_math::Mat4 testScale = 
        transformer.scale(scaleX, scaleY, scaleZ);

      custom_math::Mat4 view = camera.getLookat();

      std::cout << "Lookat matrix: " << view << std::endl;
      std::cout << "Translate: "  << testTranslate << std::endl;
      std::cout << "Scale: " << testScale << std::endl;
      std::cout << "Perspective matrix: " << perspectiveMatrix << std::endl;
      std::cout << "Model start: " << testTriangle << std::endl;
    
      // Apply transformations to model. (Model -> World).
      testTriangle = testTriangle * testScale * testTranslate;
      std::cout << "Model after transformations: " << testTriangle << std::endl;

      // View transformation (World -> Camera)
      testTriangle = testTriangle * view;
      std::cout << "Model after view: " << testTriangle << std::endl;
      
      // Projection
      testTriangle = testTriangle * perspectiveMatrix;
      std::cout << "Model after projection: " << testTriangle << std::endl;

      GLfloat pleaseGodWork[16];
      testTriangle.getFloats(pleaseGodWork);

      // Strip homogeneous coordinates to draw to screen.
      GLfloat* vertices = util::convertToScreen(pleaseGodWork, 3);

      for (int i = 0; i < 12; i++) {
        std::cout << vertices[i] << std::endl;
      }

////////////////////////////////////////////////////////////////////////////////////////////////////

      // Generate vertex buffer object.
      unsigned int VBO;
      glGenBuffers(1, &VBO);

      // Set vertex buffer object as the current one.
      glBindBuffer(GL_ARRAY_BUFFER, VBO);

      // Pass vertex information to opengl.
      glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 9, vertices, GL_STATIC_DRAW);

      glEnableVertexAttribArray(0);

      glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void *)0
      );

      bool running = true;

      // Main loop of engine.
      while (running) {

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
          if (e.type == SDL_QUIT) {
            running = false;
          }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        
        // Set program object as current shader program.
        glUseProgram(shaderProgram);

        // Draw triangle using 3 vertices.
        glDrawArrays(GL_TRIANGLES, 0, 3);
        SDL_GL_SwapWindow(mainWindow);
      }
      glDisableVertexAttribArray(0);
      SDL_DestroyWindow(mainWindow);
      SDL_Quit();
    }
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////
/* Helper methods                                                                                 */
////////////////////////////////////////////////////////////////////////////////////////////////////

int create_vertex_shader(GLuint shaderProgram) 
{
  int success;

  std::string vertexShader = openShader("res/shaders/default.vert");

  if (!vertexShader.empty()) {
    const char* vertSource = vertexShader.c_str();

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
      std::cout << "Failed to compile vertex shader" << std::endl;
      char infoLog[512];
      glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
      std::cout << infoLog << std::endl;
    } else {
      glAttachShader(shaderProgram, vertexShader);
      glDeleteShader(vertexShader);
   } 
  } else {
    success = 0;
    std::cout << "Unable to open vertex shader file" << std::endl;
  }
  return success;
}

/**
 * Creates a fragment shader and attaches it to shaderProgram.
 */
int create_fragment_shader(GLuint shaderProgram) 
{
  int success;

  // Read in the shader from file.
  std::string fragmentShader = openShader("res/shaders/default.frag");

  // Make sure the shader that was read in actually has content.
  if (!fragmentShader.empty()) {
    // char array containing source code of fragment shader.
    const char* fragmentShaderSource = fragmentShader.c_str();

    // Create an empty shader.
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Link the source code to the new shader.
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    
    //  Attempt to compile the shader.
    glCompileShader(fragmentShader);

    /* Check if the shader successfully compiled.
     *
     * param 1: shader to get attribute of
     * param 2: property to get from shader.
     * param 3: variable used to store property value.
    */
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
      std::cout << "Failed to compile fragment shader" << std::endl;
    } else {
      // Attach the shader to the program
      glAttachShader(shaderProgram, fragmentShader);
      glDeleteShader(fragmentShader);
    }
  }
  return success;
}

void printShaderLog(GLuint shader)
{
  //Make sure name is shader
  if(glIsShader(shader)) {
    //Shader log length
    int infoLogLength = 0;
    int maxLength = infoLogLength;
      
    //Get info string length
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);
      
    //Allocate string
    char* infoLog = new char[maxLength];
      
      //Get info log
      glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
    if (infoLogLength > 0) {
      //Print Log
      std::cout << infoLog << std::endl;
    }
    //Deallocate string
    delete[] infoLog;
  } else {
    std::cout << "Name %d is not a shader: " << shader << std::endl;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////