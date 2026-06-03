
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>

#include <memory>
#include <string>
#include <utility>
using std::string;
#include <vector>
using std::vector;

#include "mesh.hpp"
#include "shader.hpp"

mesh::~mesh(){

}

mesh::mesh(vector<float> verts, vector<GLuint> idxs): vertices(verts), indeces(idxs){
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
}

mesh::mesh(vector<float> verts, vector<GLuint>idxs, string path): vertices(verts), indeces(idxs), tex(std::make_unique<texture>(path)){
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
}


mesh::mesh(string path){}


bool mesh::bind(){
	if(tex != nullptr){
		tex->bind();
	}
	glBindVertexArray(vao);

	int stride = 0;
	if(tex != nullptr){
		stride = 5 * sizeof(GLfloat);
	}
	else{
		stride = 3 * sizeof(GLfloat);
	}
	
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,stride, (void*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indeces.size(), &indeces[0], GL_STATIC_DRAW);

	if(tex != nullptr){
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, stride, (void*)(3*sizeof(float)));
	}
	return true;
}


void mesh::setShader(shader&& s){
	shader_prog = std::make_unique<class shader>(std::move(s));
}


void mesh::setShader(std::unique_ptr<class shader> s){
	shader_prog = std::move(s);
}


bool mesh::draw(){
	if(shader_prog != nullptr){
		shader_prog->use();
	}
	bind();
	glDrawElements(GL_TRIANGLES, indeces.size(), GL_UNSIGNED_INT, 0);
	return true;
};

bool mesh::operator==(const mesh& other) const{
	bool verts = true;
	bool inds = true;
	for(int i = 0; i < vertices.size() && verts; i +=1){
		verts = vertices[i] == other.vertices[i];
	}

	for(int i = 0; i < indeces.size() && inds; i += 1){
		inds = indeces[i] == other.indeces[i];
	}

	return verts && inds;
}


bool mesh::setUniform(string name, glm::mat4 val){
	return shader_prog->setUniform(name, val);
};

bool mesh::setUniform(string name, glm::vec3 val){
	return shader_prog->setUniform(name, val);
};

bool mesh::setUniform(string name, float val){
	return shader_prog->setUniform(name, val);
};






