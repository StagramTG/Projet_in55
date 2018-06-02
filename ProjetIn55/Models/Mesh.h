#pragma once

#include <GL/glew.h>
#include <vector>

#include "Vertex.h"
#include "../Graphics/Texture.h"
#include "../Core/Renderable.h"

namespace IN
{
	class Mesh: public Renderable
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

		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<Texture> textures;

	public:
		Mesh();
		~Mesh();

		void create(std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
		virtual void render(ShaderProgram* shader) override;
	};
}