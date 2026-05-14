

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
		bool setUniform(glm::mat4 val);
		bool setUniform(glm::vec3 val);
		bool setUniform(float val);


};
