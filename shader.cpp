
#include "shader.hpp"
#include "Logger.hpp"

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using std::string;


shader::shader(string path): program(compile(path)){
}

GLuint shader::compile(string path){
	const string vertex_path = path + ".vs";
	GLuint program = 0;

	GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);

	string VertexCode;
	std::ifstream VertexStream(vertex_path, std::ios::in);
	if(VertexStream.is_open()){
		std::stringstream str;
		str << VertexStream.rdbuf();
		VertexCode = str.str();
		VertexStream.close();
	}
	else {
		Logger::GetInstance().log("[shader::compile] could not open vertex shader file for " + path, debug_level::ERROR);
		return 0;
	}

	const string fragment_path = path + ".fs";
	GLuint fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
	string fragmentCode;
	std::ifstream fragmentStream(fragment_path, std::ios::in);
	if(fragmentStream.is_open()){
		std::stringstream str;
		str << fragmentStream.rdbuf();
		fragmentCode = str.str();
		fragmentStream.close();
	}
	else{
		Logger::GetInstance().log("[shader::compile] could not open fragment shader file for " + path, debug_level::ERROR);
		return 0;
	}

	GLint res = GL_FALSE;
	int infoLogLen;

	char const * vs_ptr = VertexCode.c_str();
	glShaderSource(vertexId, 1, &vs_ptr, NULL);
	glCompileShader(vertexId);
	glGetShaderiv(vertexId, GL_COMPILE_STATUS, &res);
	if(!res){
		glGetShaderiv(vertexId, GL_INFO_LOG_LENGTH, &infoLogLen);
		std::vector<char> err_msg(infoLogLen + 1);
		glGetShaderInfoLog(vertexId, infoLogLen, NULL, &err_msg[0]);
		Logger::GetInstance().log("[shader::compile] failed to compile vertex shader " + vertex_path + "\n\t" + string(err_msg.begin(), err_msg.end()), debug_level::ERROR);
		return 0;
	}


	char const * fs_ptr = fragmentCode.c_str();
	glShaderSource(fragmentId, 1, &fs_ptr, NULL);
	glCompileShader(fragmentId);
	glGetShaderiv(fragmentId, GL_COMPILE_STATUS, &res);
	if(!res){
		glGetShaderiv(fragmentId, GL_INFO_LOG_LENGTH, &infoLogLen);
		std::vector<char> err_msg(infoLogLen + 1);
		glGetShaderInfoLog(fragmentId, infoLogLen, NULL, &err_msg[0]);
		Logger::GetInstance().log("[shader::compile] failed to compile fragment shader " + fragment_path + "\n\t" + string(err_msg.begin(), err_msg.end()), debug_level::ERROR);
		return 0;
	}

	program = glCreateProgram();
	glAttachShader(program, vertexId);
	glAttachShader(program, fragmentId);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &res);
	if(!res){
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
		std::vector<char> err_msg(infoLogLen + 1);
		glGetShaderInfoLog(fragmentId, infoLogLen, NULL, &err_msg[0]);
		Logger::GetInstance().log("[shader::compile] failed to compile fragment shader " + fragment_path + "\n\t" + string(err_msg.begin(), err_msg.end()), debug_level::ERROR);
		return 0;
	}

	glDeleteShader(vertexId);
	glDeleteShader(fragmentId);

	return program;
}
