#include "Character.h"

IN::Character::Character()
{

}

IN::Character::Character(std::string name, std::string modelFile): IN::Node(name)
{
    mModel.create(modelFile);
}

IN::Character::~Character()
{
    
}

bool IN::Character::create(std::string name, std::string modelFile)
{
    mModel.create(modelFile);
}

void IN::Character::update()
{

}

void IN::Character::render(ShaderProgram* shader)
{
    mModel.render(shader);
}