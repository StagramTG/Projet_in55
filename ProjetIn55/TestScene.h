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
		m_camera->setPosition(glm::vec3(2.f, 4.f, 15.f));
		m_camera->setTarget(glm::vec3(0.f, 0.f, 0.f));

		/* Load character model and setup */
		character.create("Minion", "Assets/Models/Minion.dae");

		/*static IN::Animation Anim_Test_Walk("Walk", IN::FramesToTime(glm::vec2(1, 45)), 2);
		character.AddAnimation(Anim_Test_Walk);*/

		/* Add animations*/
		static IN::Animation Anim_Walk("Walk", IN::FramesToTime(glm::vec2(50, 150)), 3);
		character.AddAnimation(Anim_Walk);

		static IN::Animation Anim_Jump("Jump", IN::FramesToTime(glm::vec2(2, 50)), 1);
		character.AddAnimation(Anim_Jump);

		static IN::Animation Anim_Run("Run", IN::FramesToTime(glm::vec2(150, 250)), 2);
		character.AddAnimation(Anim_Run);
		//Start and end frames (or times) to update according the values defined in Blender for each action
	}

	virtual void update() override
	{
		m_camera->update();
		character.update();

		IN::Scene::update();
	}

	virtual void render(IN::ShaderProgram* in_shader) override
	{
		shader.use();

		GLuint loc = shader.getUniformLocation("MVPMatrix");
		glm::mat4 model = glm::mat4();
		model = glm::rotate(model, -90.f, glm::vec3(1, 0, 0));

		shader.setUniformMat4(loc, m_camera->getMatrix() * model);

		glUseProgram(0);

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