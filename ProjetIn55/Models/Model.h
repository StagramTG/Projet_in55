#pragma once

/**
 * Class Model.
 *
 * Is a Renderable (Need to render itself using OpenGL)
 *
 * Create two subclass (We really need these ? I don't think but...):
 * 	- ModelTextured
 * 	- ModelColored
 *
 * A model is composed of several Meshes.
 */

#include <GL/glew.h>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Core/Renderable.h"
#include "Mesh.h"

namespace IN
{
	class Model: public Renderable
	{
	private:
		std::vector<Mesh> meshes;
		
		/**
		 * Method to create all meshes from the content of the loaded file.
		 * These Meshes compose the model.
		 */
		Mesh createMeshes(aiMesh* mesh, aiMaterial* material);

	public:
		Model();
		Model(std::string file);
		~Model();

		bool create(std::string file);

		virtual void render(ShaderProgram* shader) override;
	};
}