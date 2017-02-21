//
//  load_obj.cpp
//  OpenCG-HW1
//
//  Created by 雪 禹 on 2/11/17.
//  Copyright © 2017 XueYu. All rights reserved.
//

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <strstream>
#include <sstream>

using namespace std;

#include "load_obj.hpp"


void load_obj(string obj_path, vector<Vertex> &vertices){
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> normals;
    std::vector<glm::vec2> tex_coords;
    
    ifstream ifs;
    try {
        ifs.open(obj_path);
        string one_line;
        while (getline(ifs, one_line)) {
            stringstream ss(one_line);
            string type;
            ss >> type;
            if (type == "v") {
                glm::vec3 vert_pos;
                ss >> vert_pos[0] >> vert_pos[1] >> vert_pos[2] ;
                positions.push_back(vert_pos);
            } else if (type == "vt"){
                glm::vec2 tex_coord;
                ss >> tex_coord[0] >> tex_coord[1];
                tex_coords.push_back(tex_coord);
            } else if (type == "vn"){
                glm::vec3 vert_norm;
                ss >> vert_norm[0] >> vert_norm[1] >> vert_norm[2];
                normals.push_back(vert_norm);
            } else if (type == "f"){
                string s_vertex_0, s_vertex_1, s_vertex_2;
                ss >> s_vertex_0 >> s_vertex_1 >> s_vertex_2;
                int pos_idx ,tex_idx, normal_idx;
                sscanf(s_vertex_0.c_str(), "%d%d%d", &pos_idx, &tex_idx, &normal_idx);
                // We have to use index - 1 because the obj index starts at 1
                Vertex vertex_0;
                vertex_0.Position = positions[pos_idx - 1];
                vertex_0.TexCoods = tex_coords[tex_idx - 1];
                vertex_0.Normal = normals[normal_idx - 1];
                sscanf(s_vertex_1.c_str(), "%d%d%d", &pos_idx, &tex_idx, &normal_idx);
                Vertex vertex_1;
                vertex_1.Position = positions[pos_idx - 1];
                vertex_1.TexCoods = tex_coords[tex_idx - 1];
                vertex_1.Normal = normals[normal_idx - 1];
                vertex_0.Normal = normals[normal_idx - 1];
                sscanf(s_vertex_2.c_str(), "%d%d%d", &pos_idx, &tex_idx, &normal_idx);
                Vertex vertex_2;
                vertex_2.Position = positions[pos_idx - 1];
                vertex_2.TexCoods = tex_coords[tex_idx - 1];
                vertex_2.Normal = normals[normal_idx - 1];
                vertices.push_back(vertex_0);
                vertices.push_back(vertex_1);
                vertices.push_back(vertex_2);
            }
        }
    } catch (const std::exception&) {
        cout << "Error: Obj file cannot be read\n" ;
    }
    
}
