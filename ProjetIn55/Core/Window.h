#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

#include "Scene.h"
#include "../Globals.h"

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

		float lastTime = 0;
		
		bool initContext();
		bool initWindow(int w, int h, const char* t);
		void clear();

		/* Collection of all scenes of application */
		std::vector<Scene*> mScenes;
		/* Scene that is currently active in application */
		Scene* mCurrentScene;

		std::vector<double> lastMousePosition{0,0};

	public:
		Window();
		Window(int w, int h, const char* t);

		~Window();

		/**
		 * add new scene to use later in the window
		 * @param  scene the scene to add to the window
		 * @return       true if the scene have been add
		 */
		bool addScene(Scene* scene);

		/**
		 * give the name of the scene to use in window
		 * @param  name the name of the scene to use
		 * @return      true if the scene is found and used
		 */
		bool setActiveScene(std::string name);

		/**
		 * get the scene with the given name
		 * @param  name the name of the scene to get
		 * @return      the scene or null of there is no scene with the given name
		 */
		Scene* getScene(std::string name);

		/**
		 * remove the given scene
		 * @param  scene the scene to remove 
		 * @return       true if the scene is found and remove
		 */
		bool removeScene(Scene* scene);

		/**
		 * launch the infinite loop for the render and the update of the window and the whole logic
		 */
		void run();

		void ButtonPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
		void CursorMoved(GLFWwindow* window, double xpos, double ypos);
	};
}
#endif