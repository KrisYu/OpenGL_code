/*
 
 This code takes from https://github.com/opengl-tutorials/ogl/
 
 */



#ifndef CONTROLS_HPP
#define CONTROLS_HPP

# include <glm/glm.hpp>
void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();

#endif
