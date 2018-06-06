#include "Scene.h"

IN::Scene::Scene(std::string name)
{
	mName = name;
	mRootNode = new Node();
}

IN::Scene::~Scene()
{
	if (mRootNode)
	{
		delete mRootNode;
	}
}

/* Override */
void IN::Scene::update()
{
	if (mRootNode)
		mRootNode->update();
}

/* Override */
void IN::Scene::render(ShaderProgram* shader)
{
	if (mRootNode)
		mRootNode->render(shader);
}

std::string IN::Scene::getName()
{
	return mName;
}

void IN::Scene::move_camera(int input)
{
	mRootNode->move_camera(input);
}

void IN::Scene::move_camera(int x, int y)
{
	mRootNode->move_camera(x, y);
}

void IN::Scene::move_character(int input)
{
	mRootNode->move_character(input);
}
