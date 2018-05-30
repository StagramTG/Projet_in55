#pragma once

#include <GL/glew.h>

namespace IN 
{
	class Texture
	{
	private:
		GLuint id;

	public:
		Texture();
		~Texture();
	};
}