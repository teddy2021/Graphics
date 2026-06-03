
#include <string>
using std::string;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "texture.hpp"

GLuint texture::getID(){
	return id;
}


texture::texture(string path){
	int width = 0;
	int height = 0;
	int chanels = 0;

	unsigned char *data = stbi_load(path.c_str(), &width, &height, &chanels, 0);

	glGenTextures(1, &id);

	glBindTexture(GL_TEXTURE_2D, id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}


void texture::bind(){
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, id);
}


