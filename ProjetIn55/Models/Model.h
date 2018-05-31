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
#include <assimp/scene.h>
#include <assimp/mesh.h>

#include "../Core/Renderable.h"
#include "Mesh.h"

namespace IN
{
	class Model: public Renderable
	{
	private:
		std::vector<Mesh> meshes;
		
		Mesh createMesh(aiMesh mesh);

	public:
		Model(std::string file);
		~Model();

		virtual void render() override;
	};
}