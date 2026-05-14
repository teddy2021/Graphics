
#include "screen.hpp"
#include "Logger.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>
using std::string;


void screen::init(int w, int h, const string& title){
	Logger::GetInstance().log("[screen::init] begin", debug_level::DEBUG);

	if(!glfwInit()){
		Logger::GetInstance().log("[screen::init]: failed to initialize glfw", debug_level::ERROR);
		glfwTerminate();
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window.reset(glfwCreateWindow(w, h, title.c_str(), NULL, NULL));

	if(window == nullptr){
		Logger::GetInstance().log("[screen::init] Failed to create window", debug_level::ERROR);
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window.get());

	glewExperimental = GL_TRUE;
	const GLenum err = glewInit(); 
	if(err != GLEW_OK){
	Logger::GetInstance().log("[screen::init] unable to initialize glew: " + string(reinterpret_cast<const char*>( glewGetErrorString(err) )), debug_level::ERROR);
		glfwTerminate();
		return;
	}

	glfwSetInputMode(window.get(), GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0, 0, 0, 1);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


screen::screen(int w, int h){
	Logger::GetInstance().log("[screen::screen] constructor entered with args w: " + std::to_string(w) + " and h: " + std::to_string(h), debug_level::DEBUG);
	init(w, h, "No Title");
}

screen::screen(int w, int h, string title){
	Logger::GetInstance().log("[screen::screen] constructor entered with args w: " + std::to_string(w) + ", h: " + std::to_string(h) + ", and title '"+ title +"'", debug_level::DEBUG);
	init(w, h, title);
}

void screen::mainLoop(){
	Logger::GetInstance().log("[screen::main loop] begin", debug_level::DEBUG);
	int i = 0;
	while(!glfwWindowShouldClose(window.get())){
		i += 1;
		Logger::GetInstance().log("[screen::mainLoop] iteration: " + std::to_string(i) + " top of loop.", debug_level::DEBUG);
		enterDrawState();
		draw();
		exitDrawState();
	}
}

void screen::enterDrawState(){
	Logger::GetInstance().log("[screen::enterDrawState] begin", debug_level::DEBUG);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void screen::draw(){
	Logger::GetInstance().log("[screen::draw] begin", debug_level::DEBUG);
}

void screen::exitDrawState(){
	Logger::GetInstance().log("[screen::exitDrawState] begin", debug_level::DEBUG);
	glfwSwapBuffers(window.get());
	glfwPollEvents();
}


