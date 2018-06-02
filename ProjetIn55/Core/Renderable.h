#pragma once

#include "ShaderProgram.h"

namespace IN
{
	class Renderable
	{
	public:
		virtual void render(ShaderProgram* shader) = 0;
	};
}