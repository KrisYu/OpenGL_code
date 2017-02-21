//
//  main.cpp
//  OpenCG-HW1
//
//  Created by 雪 禹 on 2/11/17.
//  Copyright © 2017 XueYu. All rights reserved.
//


// Include standard headers
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
GLFWwindow* window;

// Include LoadShader
#include "shader.hpp"
#include "controls.hpp"
#include "load_obj.hpp"


// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

int main(int argc, const char * argv[]) {
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Tutorial 02 - Red triangle", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Hide the mouse and enable unlimited mouvement
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set the mouse at the center of the screen
    
    glfwPollEvents();
    glfwSetCursorPos(window, 1024/2, 768/2);
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    
    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "/Users/XueYu/Developer/OpenGL/Proj1/Proj1/shader.vs", "/Users/XueYu/Developer/OpenGL/Proj1/Proj1/shader.frag" );
    
    
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    
    vector<glm::vec3> vertices;
    vector<glm::vec2> uvs;
    vector<glm::vec3> normals;
    
    vector<Vertex> LoadedObjVertices;
    load_obj("/Users/XueYu/Developer/OpenGL/Proj1/cyborg.obj", LoadedObjVertices);
    
    for (int i = 0; i < LoadedObjVertices.size(); i++) {
        vertices.push_back(LoadedObjVertices[i].Position);
        uvs.push_back(LoadedObjVertices[i].TexCoods);
        normals.push_back(LoadedObjVertices[i].Normal);
    }
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    

    do{
        
        // Clear the screen
        glClear( GL_COLOR_BUFFER_BIT );
        
        // Use our shader
        glUseProgram(programID);
        
        
        // Compute the MVP matrix from keyboard and mous input
        computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = getProjectionMatrix();
        glm::mat4 ViewMatrix = getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
      

        
        
        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 3 * LoadedObjVertices.size()); // 3 indices starting at 0 -> 1 triangle
        
        glDisableVertexAttribArray(0);

        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
    
}
