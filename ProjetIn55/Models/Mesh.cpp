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

	if (mTextures.size() == 0)
	{
		Texture texture;
		mTextures.push_back(texture);
	}

	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create VBO + bind + attrib pointer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mVertices.size(), &mVertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, weight));

	glEnableVertexAttribArray(3);
	glVertexAttribIPointer(3, 4, GL_INT, sizeof(Vertex), (void*)offsetof(Vertex, id));

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
	loaderSkeleton.UpdateBoneMatsVector();

	glUseProgram(shader->getId());

	glBindVertexArray(vao);

	//GLint vertex = glGetAttribLocation(shader->getId(), "vertex");
	//GLint UV = glGetAttribLocation(shader->getId(), "UV");
	//GLint weight = glGetAttribLocation(shader->getId(), "weight");
	//GLint ids = glGetAttribLocation(shader->getId(), "ids");

	glEnable(GL_TEXTURE_2D);

	if (loaderSkeleton.m_boneMats.size() > 0)
	{
		
	}

	GLuint bone = shader->getUniformLocation("gBones");
	glUniformMatrix4fv(
		bone,
		loaderSkeleton.m_boneMats.size(),
		GL_FALSE,
		&loaderSkeleton.m_boneMats[0][0][0]
	);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

	glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);

	glDisable(GL_TEXTURE_2D);

	glBindVertexArray(0);

	glUseProgram(0);
}

IN::Skeleton* IN::Mesh::GetLoaderSkeleton()
{
	return &loaderSkeleton;
}
