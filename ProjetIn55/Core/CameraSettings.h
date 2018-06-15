#pragma once

#include <glm\vec3.hpp>

namespace IN
{
	struct CameraSettings
	{
		/*Perspective settings*/
		float fov = 45.f;
		float aspect = 16.f / 9.f;
		float znear = 0.1f;
		float zfar = 100.f;

		float phi = 0.0f;
		float theta = 0.0f;

		float fact = 0.0f;

		float sensitivity = 0.1f;
		float speed = 2.5f;

		glm::vec3 position = glm::vec3(3.f, 3.f, 3.f);
		glm::vec3 target = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 orientation = glm::vec3(0.f, 0.f, -1.f);

		glm::vec3 verticalAxe = glm::vec3(0.0f, 1.0f, 0.f);
		glm::vec3 lateralMovement = glm::vec3(0.f, 0.f, 0.f);
		glm::vec3 up = glm::vec3(0.f, 1.0f, 0.f);

		int left = 0;
		int right = 854;
		int top = 0;
		int bottom = 480;
	};
}