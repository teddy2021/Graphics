
#pragma once

#include <glm/ext/vector_float3.hpp>
#include <glm/glm.hpp>

class camera{
	private:
		glm::vec3 position;
		glm::vec3 target;
		glm::vec3 up;

		glm::mat4 view;

		void createViewMatrix();

	public:

		camera();
		camera(glm::vec3 spot);
		camera(glm::vec3 spot, glm::vec3 facing);
		camera(glm::vec3 spot, glm::vec3 facing, glm::vec3 upwards);


		void move(glm::vec3 movement);
		void place(glm::vec3 spot, glm::vec3 direction, glm::vec3 upwards);

		void roll(glm::vec3 axis, float radians);

		glm::mat4 viewMatrix();

};
