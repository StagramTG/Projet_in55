#pragma once

/**
 * Class Model.
 *
 * Is a Renderable (Need to render itself using OpenGL)
 *
 * Create two subclass :
 * 	- ModelTextured
 * 	- ModelColored
 *
 * A model is composed of several Meshes.
 */

#include <GL/glew.h>
#include "../Core/Updatable.h"

namespace IN
{
	class Model: public Updatable
	{
	private:

	public:
		Model();
		~Model();

		virtual void update() override;
	};
}