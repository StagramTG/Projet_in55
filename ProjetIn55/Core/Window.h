#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.h"

namespace IN
{
	/*
		Management des scenes :
			- Collection de scenes
			- Scene courante (active)
	*/
	class Window
	{
	private:
		GLFWwindow * mWindow;

		bool initContext();
		bool initWindow(int w, int h, const char* t);
		void clear();

		/* Collection of all scenes of application */
		std::vector<Scene*> mScenes;
		/* Scene that is currently active in application */
		Scene* mCurrentScene;

	public:
		Window();
		Window(int w, int h, const char* t);

		~Window();

		/* Do not handle name conflicts between scenes */
		bool addScene(Scene* scene);
		bool setActiveScene(std::string name);
		Scene* getScene(std::string name);
		bool removeScene(Scene* scene);

		void run();
	};
}