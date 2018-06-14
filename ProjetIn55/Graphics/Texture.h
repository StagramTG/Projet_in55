#pragma once

#include <GL/glew.h>
#include <string>
#include <FreeImage.h>

namespace IN 
{
	/**
	 * Class that handle texture
	 */
	class Texture
	{
	private:
		/**
		 * Id of the texture
		 */
		GLuint id;

	public:
		Texture();
		~Texture();

		/**
		 * Method to load texture from file.
		 */
		bool loadFromFile(std::string file);

		/**
		 * Bind the texture to be used
		 */
		void bind();

		/**
		 * Unbind texture
		 */
		void unbind();

		GLuint getId();
	};
}