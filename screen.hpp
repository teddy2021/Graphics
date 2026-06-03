
#include <memory>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

#include "mesh.hpp"

#pragma once

struct DestroyglfwWin{
	void operator()(GLFWwindow* ptr){
		glfwDestroyWindow(ptr);
	}
};

class screen{
	private:
		std::unique_ptr<GLFWwindow, DestroyglfwWin> window;

		std::vector<std::unique_ptr<mesh>> drawn_objects;

		void init(int w, int h, const std::string& title);

		void enterDrawState();
		void draw();
		void exitDrawState();

	public:
		screen(int w, int h);
		screen(int w, int h, std::string title);

		void addMesh(mesh && m);
		void removeMesh(const mesh & m);

		void mainLoop();
};
