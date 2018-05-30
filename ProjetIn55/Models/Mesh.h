#pragma once

#include <GL/glew.h>
#include <vector>

#include "Vertex.h"
#include "../Graphics/Texture.h"

namespace IN
{
	class Mesh
	{
	private:
		/**
		 * Store the vao id for this mesh
		 */
		GLuint vao;

		/**
		 * Store vbo id for this mesh
		 */
		GLuint vbo;

		/**
		 * Store ibo id for this mesh
		 */
		GLuint ibo;

		/**
		 * Store nbo for this mesh
		 */
		GLuint nbo;

		/**
		 * Store tbo id for this mesh
		 */
		GLuint tbo;

	public:
		Mesh();
		~Mesh();

		void create(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	};
}