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

	void IN::Window::ButtonPressed(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		
		if (action == GLFW_PRESS)
		{
			if (key == GLFW_KEY_ESCAPE)
			{
				glfwDestroyWindow(mWindow);
				glfwTerminate();
			}
			else
			{
				mCurrentScene->move_camera(key);
				mCurrentScene->move_character(key);
			}
		}				
	}

	void IN::Window::CursorMoved(GLFWwindow* window, double xpos, double ypos)
	{
		std::vector<double> currentMousePosition = std::vector<double>({ xpos, ypos });
		std::vector<double> deltaPosition = std::vector<double>({ xpos - lastMousePosition.at(0), ypos - lastMousePosition.at(1) });
		lastMousePosition = currentMousePosition;
		mCurrentScene->move_camera(deltaPosition.at(0), deltaPosition.at(1));
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

			float nowTime = (float)glfwGetTime();
			if (nowTime > lastTime) {
				GLOBALS::deltaTime = (nowTime - lastTime);
				lastTime = nowTime;
			}
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


		glfwSetWindowUserPointer(mWindow, this);

		auto ButtonEvent = [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->ButtonPressed(window, key, scancode, action, mods);
		};
		glfwSetKeyCallback(mWindow, ButtonEvent);

		auto MouseEvent = [](GLFWwindow* window, double x, double y)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->CursorMoved(window, x, y);
		};
		glfwSetCursorPosCallback(mWindow, MouseEvent);

		lastMousePosition = std::vector<double>({ (double)w / 2, (double)h / 2 });

		return true;
	}

	void IN::Window::clear()
	{
		glfwDestroyWindow(mWindow);
		glfwTerminate();
	}

}