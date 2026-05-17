

#include <GL/glew.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <string>


#pragma once

class shader{
	private:
		GLuint program;
		GLuint compile(std::string path);

	public:
		shader(std::string path);
		~shader();

		bool use();
		int getUniformID(std::string name);
		bool setUniform(std::string name, glm::mat4 val);
		bool setUniform(std::string name, glm::vec3 val);
		bool setUniform(std:: string name, float val);


};
