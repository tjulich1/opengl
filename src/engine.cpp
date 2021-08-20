////////////////////////////////////////////////////////////////////////////////////////////////////
/* Trent Julich ~ 1 August 2021                                                                   */
////////////////////////////////////////////////////////////////////////////////////////////////////

#include <glew.h>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Included from src.
#include "camera.hpp"
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
  myCamera = std::make_shared<Camera>(Camera(CAMERA_START, CAMERA_LOOK));
  frustum = Frustum(LEFT, RIGHT, TOP, BOTTOM, NEAR_VAL, FAR_VAL);
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
      
      /*
       * Values for transforming the model.
       */
      float translateX = 0.0f;
      float translateY = 0.0f;
      float translateZ = 0.0f;

      float scaleX = 1.0f;
      float scaleY = 1.0f;
      float scaleZ = 1.0f;

      int rotationAngle = 0;

      // Generate vertex buffer object.
      unsigned int VBO;
      glGenBuffers(1, &VBO);

      // Set vertex buffer object as the current one.
      glBindBuffer(GL_ARRAY_BUFFER, VBO);

      glEnableVertexAttribArray(0);

      glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        0,
        (void *)0
      );

      inputHandler.linkCamera(myCamera.get());

      bool running = true;

      GLfloat g_vertex_buffer_data[] = {
          -1.0f,-1.0f,-1.0f, // triangle 1 : begin
          -1.0f,-1.0f, 1.0f,
          -1.0f, 1.0f, 1.0f, // triangle 1 : end
          1.0f, 1.0f,-1.0f, // triangle 2 : begin
          -1.0f,-1.0f,-1.0f,
          -1.0f, 1.0f,-1.0f, // triangle 2 : end
          1.0f,-1.0f, 1.0f,
          -1.0f,-1.0f,-1.0f,
          1.0f,-1.0f,-1.0f,
          1.0f, 1.0f,-1.0f,
          1.0f,-1.0f,-1.0f,
          -1.0f,-1.0f,-1.0f,
          -1.0f,-1.0f,-1.0f,
          -1.0f, 1.0f, 1.0f,
          -1.0f, 1.0f,-1.0f,
          1.0f,-1.0f, 1.0f,
          -1.0f,-1.0f, 1.0f,
          -1.0f,-1.0f,-1.0f,
          -1.0f, 1.0f, 1.0f,
          -1.0f,-1.0f, 1.0f,
          1.0f,-1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          1.0f,-1.0f,-1.0f,
          1.0f, 1.0f,-1.0f,
          1.0f,-1.0f,-1.0f,
          1.0f, 1.0f, 1.0f,
          1.0f,-1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          1.0f, 1.0f,-1.0f,
          -1.0f, 1.0f,-1.0f,
          1.0f, 1.0f, 1.0f,
          -1.0f, 1.0f,-1.0f,
          -1.0f, 1.0f, 1.0f,
          1.0f, 1.0f, 1.0f,
          -1.0f, 1.0f, 1.0f,
          1.0f,-1.0f, 1.0f
        };

      Model testModel(g_vertex_buffer_data, sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]));

      Mat4 perspectiveMatrix = frustum.createPerspectiveMatrix();

      // Tell the model the order and type of transformations to apply to vertices.
      testModel.translate(scaleX, scaleY, scaleZ);

      SDL_Event e;

      // Main loop of engine.
      while (running) {
        Mat4 view = myCamera->getLookat();

        // std::cout << testModel.getVertexMat() << std::endl;

        // Apply transformations to model. (Model -> World).
        // Each model keeps track of its own transformations, and a "world-space" vertex list for 
        // each model can be retrieved via a method.
        // std::cout << testModel.getTransformedVertexMat() << std::endl;
        
        // Model vertex data from after transformations.

        // View transformation (World -> Camera)


        // Projection

        // Pass vertex information to opengl.
        glBufferData(GL_ARRAY_BUFFER,
                     sizeof(GLfloat)*12*9,
                     g_vertex_buffer_data, 
                     GL_STATIC_DRAW); 

        while (SDL_PollEvent(&e)) {

          // Check if the user has requested to quit the program.
          if (e.type == SDL_QUIT) {
            running = false;
          } 
          // Otherwise handle all other user events.
          else {
            inputHandler.handleEvent(e);
          }
        }

        glClear(GL_COLOR_BUFFER_BIT);
        
        // Set program object as current shader program.
        glUseProgram(shaderProgram);

        // Draw triangle using 3 vertices.
        glDrawArrays(GL_TRIANGLES, 0, 12*3);
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