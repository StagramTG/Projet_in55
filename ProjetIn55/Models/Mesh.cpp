#include "Mesh.h"

IN::Mesh::Mesh()
{

}

IN::Mesh::~Mesh()
{

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

	// Unbind vao
	glBindVertexArray(0);
}