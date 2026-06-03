
#include "screen.hpp"
#include "shader.hpp"
#include "Logger.hpp"

#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <vector>
using std::vector;

int main(){
	Logger::GetInstance().SetLevel(debug_level::ERROR);
	
	screen display(800, 600, "Graphics");
	
	shader s("resources/basic");
	
	vector<float> vertices({
			-0.5, -0.5, 0, 1, 1,
			-0.5,  0.5, 0, 1, 0,
			 0.5,  0.5, 0, 0, 0,
			 0.5, -0.5, 0, 0, 1
			});
	vector<GLuint> indeces({
			0, 1, 2,
			2, 3, 0
			});
	mesh square(vertices, indeces, "resources/texture.jpg");
	square.setShader(std::move(s));
	square.setUniform("colour", glm::vec3(1,0,0));
	display.addMesh(std::move(square));
	
	display.mainLoop();
	return 0;
}
