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
    return mModel.create(modelFile);
}

void IN::Character::update()
{
	mModel.update();
}

void IN::Character::render(ShaderProgram* shader)
{
    mModel.render(shader);
}

void IN::Character::AddAnimation(Animation anim)
{
	mModel.AddAnimation(anim);
}

void IN::Character::Move(int input)
{
	if (input == 265)
		mModel.PlayAnimation("Walk");
}
