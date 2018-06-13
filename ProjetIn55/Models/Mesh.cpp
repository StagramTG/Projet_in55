#include "Mesh.h"

#include <iostream>

IN::Mesh::Mesh(
	std::vector<Vertex> vertices,
	std::vector<unsigned int> indices,
	std::vector<Texture> textures)
{
	// Keep data
	mVertices = vertices;
	mIndices = indices;
	mTextures = textures;

	std::cout << mVertices.size() << std::endl;

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create VBO + bind + attrib pointer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertices.size(), &mVertices[0], GL_STATIC_DRAW);

	// Create IBO + bind + push data
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mIndices.size(), &mIndices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// Unbind vao
	glBindVertexArray(0);
}

IN::Mesh::~Mesh()
{
	// Clean up VBO
	if(vbo != 0)
		glDeleteBuffers(1, &vbo);

	// Clean up VAO
	if(vao != 0)
		glDeleteVertexArrays(1, &vao);
}

void IN::Mesh::render(ShaderProgram* shader)
{


	glBindVertexArray(vao);

	int vertex = glGetAttribLocation(shader->getId(), "vertex");
	int normal = glGetAttribLocation(shader->getId(), "normal");
	int UV = glGetAttribLocation(shader->getId(), "UV");
	int weight = glGetAttribLocation(shader->getId(), "weight");
	int ids = glGetAttribLocation(shader->getId(), "ids");

	if (loaderSkeleton.m_boneMats.size() > 0)
	{
		GLuint bone = shader->getUniformLocation("gBones");
		glUniformMatrix4fv(
			bone,
			loaderSkeleton.m_boneMats.size(),
			GL_FALSE,
			glm::value_ptr(loaderSkeleton.m_boneMats[0])
		);
		
		if (mTextures.size() > 0)
		{
			mTextures.at(0).loadFromFile("./Assets/Models/textures/uv_minion.jpg");
			glUniform1i(glGetUniformLocation(shader->getId(), "texture"), 0);
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glEnableVertexAttribArray(vertex);
	glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(normal);
	glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(UV);
	glVertexAttribPointer(UV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glEnableVertexAttribArray(weight);
	glVertexAttribPointer(weight, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, weight));

	glEnableVertexAttribArray(ids);
	glVertexAttribPointer(ids, 4, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, id));

	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(vertex);
	glDisableVertexAttribArray(normal);
	glDisableVertexAttribArray(UV);
	glDisableVertexAttribArray(weight);
	glDisableVertexAttribArray(ids);

	glBindVertexArray(0);
}

IN::Skeleton* IN::Mesh::GetLoaderSkeleton()
{
	return &loaderSkeleton;
}
