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
		 * Store vbo id for this mesh, store all data relatives to vertices:
		 * 	- Positions
		 * 	- Normals
		 * 	- Uvs
		 */
		GLuint vbo;

		/**
		 * Store ibo id for this mesh, indices
		 */
		GLuint ibo;

	public:
		Mesh();
		~Mesh();

		void create(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
	};
}