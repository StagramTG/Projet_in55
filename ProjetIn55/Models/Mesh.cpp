#include "Mesh.h"

IN::Mesh::Mesh()
{
	vao = 0;
	vbo = 0;
	loaderSkeleton = new Skeleton();
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

void IN::Mesh::create(
	std::vector<Vertex> vertices, 
	std::vector<GLuint> indices, 
	std::vector<Texture> textures)
{
	// Create VAO
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create VBO + bind + attrib pointer
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Pointer for vertices positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	// Pointer for vertices normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	// Pointer to texture uvs
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

	// Pointer for vertices weights
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, weight));

	// Pointer for vertices ids
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_INT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, id));

	// Create IBO + bind + push data
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// Unbind vao
	glBindVertexArray(0);
}

void IN::Mesh::render(ShaderProgram* shader)
{
	// Bind vao
	glBindVertexArray(vao);

	// Shader stuff ?
	glUniformMatrix4fv(shader->getUniformLocation("gBones"), loaderSkeleton->m_boneMats.size(), GL_FALSE, glm::value_ptr(loaderSkeleton->m_boneMats[0]));

	// Draw elements
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

IN::Skeleton* IN::Mesh::GetLoaderSkeleton()
{
	return loaderSkeleton;
}

void IN::Mesh::SetLoaderSkeleton(IN::Skeleton* skeleton)
{
	loaderSkeleton = skeleton;
}
