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
	mRootNode->update();
}

/* Override */
void IN::Scene::render()
{
	mRootNode->render();
}

std::string IN::Scene::getName()
{
	return mName;
}
