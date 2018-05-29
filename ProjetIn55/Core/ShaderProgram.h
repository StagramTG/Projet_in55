#pragma once

#include <GL\glew.h>
#include <fstream>
#include <string>
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

namespace IN
{
	class ShaderProgram
	{
	private:
		GLuint m_id;

	public:
		ShaderProgram();
		~ShaderProgram();

		bool init(const char* vertex_file, const char* fragment_file);
		void use();
		void done();

		GLuint getUniformLocation(const char* name);
		void setUniformMat4(GLuint location, glm::mat4 mvp);

		/* Subroutines */
		GLuint getSubroutineLocation(GLenum shaderType, const char* name);
		void setUniformSubroutine(GLenum shaderType, GLuint index);

		/* Textures */
		void setUniformInt(GLuint location, GLuint value);

		/* Float value */
		void setUniformFloat(GLuint location, GLfloat value);
		void setUniformVec3Float(GLuint location, glm::vec3 value);
	};
}