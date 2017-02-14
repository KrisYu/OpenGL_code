#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>
using namespace glm;
using namespace std;


int main(){
	// Create Vector
    vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    mat4 trans;
    
    // translate matrix is created by this function →  identity matrix + translate vector
    trans = translate(trans, vec3(1.0f, 1.0f, 0.0f));
    // Matrix * Vector to get new Vector
    vec = trans * vec;
    cout << vec.x << vec.y << vec.z << endl;
}