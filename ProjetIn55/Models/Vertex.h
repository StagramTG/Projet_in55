#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace IN
{
	/**
	 * Struct Vertex
	 *
	 * Describe a set of data for vertex :
	 * 		- Position
	 * 		- Color (if exists)
	 * 		- Normal
	 */
	struct Vertex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 uv;
	};
}