#pragma once

#include <glm/vec3.hpp>

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
		glm::vec3 color;
		glm::vec3 normal;
	};
}