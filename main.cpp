
#include "screen.hpp"
#include "shader.hpp"

int main(){
	screen display(800, 600, "Graphics");
	shader s("resources/basic");
	s.use();
	s.setUniform("colour", glm::vec3(1,0,0));
	display.mainLoop();
	return 0;
}
