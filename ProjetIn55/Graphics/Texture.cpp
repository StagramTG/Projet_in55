#include "Texture.h"
#include <iostream>

IN::Texture::Texture()
{
    id = 0;
}

IN::Texture::~Texture()
{
	if(id != 0)
        glDeleteTextures(1, &id);
}

bool IN::Texture::loadFromFile(std::string file)
{
	std::cout << "Chargement depuis mémoire" << std::endl;
	FREE_IMAGE_FORMAT imageFormat = FreeImage_GetFileType(file.c_str());
	FIBITMAP* image(0);

	image = FreeImage_Load(imageFormat, file.c_str());
	if (image == NULL)
	{
		std::cout << "Erreur chargement image" << std::endl;
	}

	std::cout << "Transfert tableau de bytes: " << FreeImage_GetBPP(FreeImage_ConvertTo32Bits(image)) << std::endl;
	BYTE* data = FreeImage_GetBits(FreeImage_ConvertTo32Bits(image));

	/*Generate OpenGL texture*/
	glGenTextures(1, &id);
	bind();

	std::cout << "Création texture, mise en place réglages" << std::endl;
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	/*Load image from file*/
	int width, height;
	/*Load data from file*/
	width = FreeImage_GetWidth(image);
	height = FreeImage_GetHeight(image);

	std::cout << "Renseignement des données" << std::endl;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, (void*)data);
	glGenerateMipmap(GL_TEXTURE_2D);

	unbind();

	std::cout << "Libération de l'image" << std::endl;
	FreeImage_Unload(image);

	return true;
}

void IN::Texture::bind()
{
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}

void IN::Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint IN::Texture::getId()
{
	return id;
}
