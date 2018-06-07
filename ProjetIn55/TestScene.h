#pragma once

#include <iostream>
#include "./Core/Scene.h"
#include "./Core/ShaderProgram.h"
#include "./Character.h"
#include "./Core/Animation.h"
#include "./Core/Camera.h"
#include "./Core/Node.h"

class TestScene: public IN::Scene
{
private:
	IN::ShaderProgram shader;
	IN::Character character;
	IN::Camera* m_camera;

public:
	TestScene(): IN::Scene("Test")
	{
		/* Load Shader */
		shader.init("Assets/Shaders/vertex.glsl", "Assets/Shaders/fragment.glsl");

		IN::CameraSettings settings;
		settings.znear = 1.f;

		m_camera = new IN::Camera(settings);
		m_camera->setPosition(glm::vec3(-30.f, -30.f, -30.f));
		m_camera->setTarget(glm::vec3(0.f, 0.f, 0.f));

		/* Load character model and setup */
		character.create("Minion", "Assets/Models/Test.dae");

		/* An animation*/
		static IN::Animation Anim_Walk("Walk", IN::FramesToTime(glm::vec2(1, 45)), 2);
		character.AddAnimation(Anim_Walk);
	}

	virtual void update() override
	{
		std::cout << "Update scene" << std::endl;

		m_camera->update();
		character.update();

		IN::Scene::update();
	}

	virtual void render(IN::ShaderProgram* in_shader) override
	{
		GLuint loc = shader.getUniformLocation("MVPMatrix");
		shader.setUniformMat4(loc, m_camera->getMatrix());

		shader.use();
		character.render(&shader);
		IN::Scene::render(&shader);
	}

	IN::Character* GetCharacter()
	{
		return &character;
	}

	void move_camera(int input) override
	{
		m_camera->move(input);
	}

	void move_camera(int x, int y) override
	{
		m_camera->move(x,y);
	}

	virtual void move_character(int input) override
	{
		character.Move(input);
	}
};