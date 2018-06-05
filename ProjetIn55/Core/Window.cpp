#include "Window.h"

#include <iostream>

namespace IN
{
	Window::Window()
	{
		if (!initWindow(854, 480, "IN55: Character animation"))
		{
			std::cerr << "[WINDOW] Error while init window" << std::endl;
			exit(EXIT_FAILURE);
		}

		if (!initContext())
		{
			std::cerr << "[WINDOW] Error while init context" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	Window::Window(int w, int h, const char * t)
	{
		if (!initWindow(w, h, t))
		{
			std::cerr << "[WINDOW] Error while init window" << std::endl;
			exit(EXIT_FAILURE);
		}

		if (!initContext())
		{
			std::cerr << "[WINDOW] Error while init context" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	Window::~Window()
	{
		mScenes.erase(mScenes.begin(), mScenes.end());
	}

	bool Window::addScene(Scene * scene)
	{
		mScenes.push_back(scene);
		return true;
	}

	bool Window::setActiveScene(std::string name)
	{
		for (Scene* s : mScenes)
		{
			if (s->getName() == name)
			{
				mCurrentScene = s;
				return true;
			}
		}

		return false;
	}

	Scene * Window::getScene(std::string name)
	{
		for (Scene* s : mScenes)
		{
			if (s->getName() == name)
			{
				return s;
			}
		}

		return nullptr;
	}

	bool Window::removeScene(Scene * scene)
	{
		std::vector<Scene*>::iterator begin = mScenes.begin();
		for (size_t i = 0; i < mScenes.size(); ++i)
		{
			if (mScenes[i] == scene)
			{
				mScenes.erase(begin + i);
				return true;
			}
		}

		return false;
	}

	void Window::run()
	{
		while (!glfwWindowShouldClose(mWindow))
		{
			glfwPollEvents();
			if (mCurrentScene)
				mCurrentScene->update();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			if (mCurrentScene)
				mCurrentScene->render(nullptr);

			glfwSwapBuffers(mWindow);

			/*float nowTime = glfwGetTime();

			if (nowTime > lastTime) {
				GLOBALS::deltaTime = (nowTime - lastTime) / 1000;
				lastTime = nowTime;
			}*/
		}

		clear();
	}
	
	bool IN::Window::initContext()
	{
		glewExperimental = GL_TRUE;
		if (glewInit() != GLEW_OK)
		{
			return false;
		}

		return true;
	}

	bool Window::initWindow(int w, int h, const char * t)
	{
		if (glfwInit() != GL_TRUE)
		{
			return false;
		}

		mWindow = glfwCreateWindow(w, h, t, NULL, NULL);
		if (!mWindow)
		{
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(mWindow);
		glfwSwapInterval(1);

		//GLOBALS::deltaTime = 0.0;

		return true;
	}

	void IN::Window::clear()
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}
}