#include "Texture.h"

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
    // Load texture from file
    FIBITMAP* bitmap = FreeImage_Load(FIF_PNG, file.c_str());
    if(!bitmap)
    {
        return false;
    }

    // Load it in memory
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE0, id);

    int width = FreeImage_GetWidth(bitmap);
    int height = FreeImage_GetHeight(bitmap);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, bitmap->data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    FreeImage_Unload(bitmap);

    return true;
}

void IN::Texture::bind(int index)
{
    glEnableTexture(GL_TEXTURE0 + index);
    glBindTexture(GL_TEXTURE_2D, id);
}

void IN::Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}