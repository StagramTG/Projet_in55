#pragma once

#include <iostream>
#include "Core/Scene.h"

class TestScene: public IN::Scene
{
private:

public:
	TestScene(): IN::Scene("Test")
	{

	}

	virtual void update() override
	{
		std::cout << "Update scene" << std::endl;
	}
};