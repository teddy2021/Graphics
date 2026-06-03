
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <memory>
#include <vector>
#include <string>


#include "shader.hpp"
#include "texture.hpp"
class mesh{

	private:
		std::vector<float> vertices;
		std::vector<GLuint> indeces;

		std::unique_ptr<texture> tex;
		std::unique_ptr<shader> shader_prog;

		GLuint vao;
		GLuint vbo;
		GLuint ebo;

		bool bind();

	public:
		~mesh();
		mesh(std::string path);
		mesh(std::vector<float> vertices, std::vector<GLuint> indeces);
		mesh(std::vector<float> vertices, std::vector<GLuint> indeces, std::string path);
		mesh(mesh && other) noexcept:
			ebo(other.ebo),
			vbo(other.vbo),
			vao(other.vao),
			shader_prog(std::make_unique<shader>(std::move(*other.shader_prog))),
			indeces(other.indeces),
			vertices(other.vertices),
			tex(std::make_unique<texture>(std::move(*other.tex))){
				other.ebo = 0;
				other.vbo = 0;
				other.vao = 0;
			};


		void setShader(shader&& s);
		void setShader(std::unique_ptr<class shader> s);

		bool draw();

		bool operator==(const mesh& other) const;

		bool setUniform(std::string name, glm::mat4 val);
		bool setUniform(std::string name, glm::vec3 val);
		bool setUniform(std::string name, float val);

};
