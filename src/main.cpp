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

#include "custom_math.hpp"

/* * * * * * *
 * Constants *
 * * * * * * */

/* Dimensions of main window. */
const static int WIDTH = 500;
const static int HEIGHT = 500;

const static std::string TITLE = "OpenGL test";;

const static Uint32 WINDOW_FLAGS = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL;  

/* * * * * * * * * * * *
 * Method Declarations *
 * * * * * * * * * * * */

int create_vertex_shader(GLuint shaderProgram);
int create_fragment_shader(GLuint shaderProgram);
void printProgramLog(GLuint program);
void printShaderLog(GLuint shader);
bool initSDL();
bool initGLEW();
std::string open_shader(std::string path);

/* * * * * * * * * * * *
 * Method Definitions  *
 * * * * * * * * * * * */

/**
 * Main entry point of program. Accepts no arguments.
 */
int main(int argc, char* argv[]) {
  // Code that is returned by the program.
  int success = 0;

  custom_math::Mat4 xrotate = custom_math::Mat4::XRotation(90);
  custom_math::Mat4 yrotate = custom_math::Mat4::YRotation(90);
  custom_math::Mat4 zrotate = custom_math::Mat4::ZRotation(90);

  std::cout << xrotate << std::endl;

  if (initSDL()) {
    
    // Set SDL version info.
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

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
              
              GLfloat vertices[] = {
                -1.0f, -1.0f, 0.0f,
                1.0f, -1.0f, 0.0f,
                0.0f,  1.0f, 0.0f,
              };

              // Generate vertex buffer object.
              unsigned int VBO;
              glGenBuffers(1, &VBO);

              // Set vertex buffer object as the current one.
              glBindBuffer(GL_ARRAY_BUFFER, VBO);

              // Pass vertex information to opengl.
              glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

              glEnableVertexAttribArray(0);
              glBindBuffer(GL_ARRAY_BUFFER, VBO);

              glVertexAttribPointer(
                0,
                3,
                GL_FLOAT,
                GL_FALSE,
                0,
                (void *)0
              );

              // Main loop of engine.
              while (true) {
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

void printProgramLog( GLuint program )
{
    //Make sure name is shader
    if( glIsProgram( program ) == GL_TRUE)
    {
        //Program log length
        int infoLogLength = 0;
        int maxLength = infoLogLength;
        
        //Get info string length
        glGetProgramiv( program, GL_INFO_LOG_LENGTH, &maxLength );
        
        //Allocate string
        char* infoLog = new char[ maxLength ];
        
        //Get info log
        glGetProgramInfoLog( program, maxLength, &infoLogLength, infoLog );
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
        printf( "Name %d is not a program\n", program );
    }
}

int create_vertex_shader(GLuint shaderProgram) {
  int success;

  std::string vertexShader = open_shader("res/shaders/default.vert");

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
  std::string fragmentShader = open_shader("res/shaders/default.frag");

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