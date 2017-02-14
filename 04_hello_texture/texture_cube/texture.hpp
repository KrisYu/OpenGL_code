//
//  texture.hpp
//  OpenGL_Cube
//
//  Created by 雪 禹 on 2/14/17.
//  Copyright © 2017 XueYu. All rights reserved.
//

#ifndef texture_hpp
#define texture_hpp

#include <gl/glew.h>

GLuint loadBMP_custom(const char* imagepath);
GLuint loadDDS(const char * imagepath);

#endif /* texture_hpp */
