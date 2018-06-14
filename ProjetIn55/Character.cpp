#include "Character.h"

IN::Character::Character()
{

}

IN::Character::Character(std::string name, std::string modelFile): IN::Node(name)
{
    mModel.create(modelFile);

	if (!texture.loadFromFile("./Assets/Models/textures/uv_minion.png")) {}
}

IN::Character::~Character()
{
    
}

bool IN::Character::create(std::string name, std::string modelFile)
{
	texture.loadFromFile("./Assets/Models/textures/uv_minion.png");

    return mModel.create(modelFile);
}

void IN::Character::update()
{
	mModel.update();
}

void IN::Character::render(ShaderProgram* shader)
{
	texture.bind();
	shader->setUniformInt(shader->getUniformLocation("texture"), texture.getId());

    mModel.render(shader);

	texture.unbind();
}

void IN::Character::PlayAnimation(std::string name_anim)
{
	mModel.PlayAnimation(name_anim);
}

void IN::Character::AddAnimation(Animation anim)
{
	mModel.AddAnimation(anim);
}

void IN::Character::Move(int input)
{
	//Up arrow
	if (input == 265)
		mModel.PlayAnimation("Walk");
	//Shift
	else if (input == 340 || input == 344)
		mModel.PlayAnimation("Jump");
	//Space
	else if (input == 32)
		mModel.PlayAnimation("Run");
}
