// Trent Julich ~ 12 July 2021

/* * * * * * *
 * Includes  *
 * * * * * * */

#include <SDL.h>
#include <glew.h>
#include <gl\GL.h>
#include <SDL_opengl.h>
#include <gl\GLU.h>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

// Included from source
#include "custom_math.hpp"
#include "util.hpp"
#include "model.hpp"
#include "shader.hpp"
#include "transformation_builder.hpp"

/* * * * * * *
 * Constants *
 * * * * * * */

/* Dimensions of main window. */
const static int WIDTH = 500;
const static int HEIGHT = 500;

const static std::string TITLE = "OpenGL test";;

const static Uint32 WINDOW_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;  

const static int MAJOR_VERSION = 3;
const static int MINOR_VERSION = 2;

/* * * * * * * * * * * *
 * Method Declarations *
 * * * * * * * * * * * */

int create_vertex_shader(GLuint shaderProgram);
int create_fragment_shader(GLuint shaderProgram);
void printShaderLog(GLuint shader);
void setGLVersion();
bool initSDL();
bool initGLEW();

/* * * * * * * * * * * *
 * Method Definitions  *
 * * * * * * * * * * * */

/**
 * Main entry point of program. Accepts no arguments.
 */
int main(int argc, char* argv[]) {
  // Code that is returned by the program.
  int success = 0;

  if (initSDL()) {
    setGLVersion();

    SDL_Window* gWindow = SDL_CreateWindow(TITLE.c_str(), SDL_WINDOWPOS_UNDEFINED, 
      SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, WINDOW_FLAGS);

    if (gWindow) {
      SDL_GLContext gContext = SDL_GL_CreateContext(gWindow);

      // Check if an SDL context was successfully created.
      if (gContext == nullptr || !initGLEW()) {
        std::cout << "Failed to create context: " << SDL_GetError() << std::endl;
        success = -1;
      } else {
        /*
        * Use Vsync
        */
        if (SDL_GL_SetSwapInterval(1) < 0) {
          std::cout << "Unable to use vsync: " << SDL_GetError() << std::endl;
          success = -1;
        } else {
          // Create the opengl program object.
          unsigned int shaderProgram;
          shaderProgram = glCreateProgram();

          // Try to create vertex and fragment shader.
          if (create_fragment_shader(shaderProgram) && create_vertex_shader(shaderProgram)) {
            
            // Try linking shader program.
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
            
              custom_math::Mat4 testTriangle;
              
              custom_math::Vec4 firstPoint(-1.0f, -1.0f, 0.0f, 0.0f);
              custom_math::Vec4 secondPoint(1.0f, -1.0f, 0.0f, 0.0f);
              custom_math::Vec4 thirdPoint(0.0f, 1.0f, 0.0f, 0.0f);

              std::vector<custom_math::Vec4> testList{firstPoint, secondPoint, thirdPoint};
              Model testModel(testList);
              testModel.listVertices();

              testTriangle.setRow(0, firstPoint);
              testTriangle.setRow(1, secondPoint);
              testTriangle.setRow(2, thirdPoint);
              testTriangle.setElement(3, 3, 1);

              TransformationBuilder transformer;

              custom_math::Mat4 testScale = transformer.scale(0.5f, 0.5f, 0.5f);
              custom_math::Mat4 testScale2 = transformer.scale(4, 0.5f, 0.5f);

              custom_math::Mat4 testRotate = transformer.yRotation(45);

              custom_math::Vec4 testCameraLocation(-1, 7, 0, 0);
              custom_math::Vec4 dest(0, 0, 0, 0);
              custom_math::Mat4 lookAt = custom_math::Mat4::LookAt(testCameraLocation, dest);

              testTriangle = testTriangle * testScale * testRotate * lookAt;

              GLfloat pleaseGodWork[16];
              testTriangle.getFloats(pleaseGodWork);

              // Strip homogeneous coordinates to draw to screen.
              GLfloat* vertices = util::convertToScreen(pleaseGodWork, 3);

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
                SDL_GL_SwapWindow(gWindow);
              }

              glDisableVertexAttribArray(0);
              
            }
          }
        }
      }
    }
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
  }
  return success;
}

/**
 * Called to attempt to initialize SDL.  
 * 
 * returns: true if SDL was initialized, else false.
 */
bool initSDL() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) == -1) {
    success = false;
    std::cout << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
  }
  return success;
}

/**
 * Called to attempt to initialize GLEW. 
 * 
 * returns: true if GLEW was initialized, else false.
 */
bool initGLEW() {
  bool success = true;
  glewExperimental = GL_TRUE;
  GLenum glewError = glewInit();

  if (glewError != GLEW_OK) {
    std::cout << "Error initializing GLEW: " << glewGetErrorString(glewError) << std::endl;
    success = false;
  }
  return success;
}

int create_vertex_shader(GLuint shaderProgram) {
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
int create_fragment_shader(GLuint shaderProgram) {
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

void printShaderLog( GLuint shader )
{
    //Make sure name is shader
    if( glIsShader( shader ) )
    {
        //Shader log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        
        //Get info string length
        glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &maxLength );
        
        //Allocate string
        char* infoLog = new char[ maxLength ];
        
        //Get info log
        glGetShaderInfoLog( shader, maxLength, &infoLogLength, infoLog );
        if( infoLogLength > 0 )
        {
            //Print Log
            printf( "%s\n", infoLog );
        }

        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "Name %d is not a shader\n", shader );
    }
}

/**
 * Reads in a shader that is located at the given path.
 * 
 * args: std::string path = path to the shader that should be opened.
 * returns: std::string shader = string contents of shader that was read. Empty string if shader 
 *              cannot be found at path.
 */
std::string open_shader(std::string path) {
  // Init shader with empty string in case of failure to open file.
  std::string shader = "";

  // Try to open file.
  std::fstream shaderFile(path);
  
  // If the file was successfully opened
  if (shaderFile.is_open()) {
    // Read and store shader file.
    std::stringstream buffer;
    buffer << shaderFile.rdbuf();
    shader = buffer.str();    
  } 
  return shader;
}

/**
 * Helper method used to set the version of OpenGL to be used by SDL.
 */
void setGLVersion() {
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, MAJOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, MINOR_VERSION);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
}