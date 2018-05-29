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
#include "../Core/Renderable.h"

namespace IN
{
	class Model: public Renderable
	{
	private:

	public:
		Model();
		~Model();

		virtual void render() override;
	};
}