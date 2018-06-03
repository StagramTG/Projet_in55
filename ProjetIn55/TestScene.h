#pragma once

#include <iostream>
#include "./Core/Scene.h"
#include "./Core/ShaderProgram.h"
#include "./Character.h"

class TestScene: public IN::Scene
{
private:
	IN::ShaderProgram shader;
	IN::Character character;

public:
	TestScene(): IN::Scene("Test")
	{
		/* Load Shader */
		shader.init("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");

		/* Load character model and setup */
		character.create("Minion", "Assets/Models/Minion.dae");
	}

	virtual void update() override
	{
		std::cout << "Update scene" << std::endl;
	}
};