#include "Scene.h"

IN::Scene::Scene(std::string name)
{
	mName = name;
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
