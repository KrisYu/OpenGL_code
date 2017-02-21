//
//  load_obj.hpp
//  OpenCG-HW1
//
//  Created by 雪 禹 on 2/17/17.
//  Copyright © 2017 XueYu. All rights reserved.
//

#ifndef load_obj_hpp
#define load_obj_hpp

#include <string>
#include <vector>
using namespace std;


struct Vertex {
    // Position
    glm::vec3 Position;
    // Normal
    glm::vec3 Normal;
    // TexCoords
    glm::vec2 TexCoods;
};

void load_obj(string obj_path, vector<Vertex> &vertices);

#endif /* load_obj_hpp */
