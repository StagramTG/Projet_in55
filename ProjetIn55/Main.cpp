/*
	IN55 Project: Character animation
	Authors: Mathilde Perrot, Jérémy Haelwyn, Thomas Gredin
*/

#include "Core/Window.h"
#include "TestScene.h"

int main(int argc, char** argv)
{
	IN::Window window;

	TestScene* test = new TestScene();
	window.addScene(test);
	window.setActiveScene("Test");

	window.run();

	return 0;
}