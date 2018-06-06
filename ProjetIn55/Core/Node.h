#pragma once

#include <string>
#include <vector>

#include "Updatable.h"
#include "Renderable.h"

namespace IN
{
	class Node : public Updatable, public Renderable
	{
	protected:
		std::string mName;
		Node* mParent;
		std::vector<Node*> mChildren;

	public:
		Node();
		Node(std::string name);
		~Node();

		virtual void update() override;
		virtual void render(ShaderProgram* shader) override;

		bool addChild(Node* child);
		bool removeChild(Node* child);
		Node* getChild(std::string name);

		virtual void move_camera(int input);
		virtual void move_camera(int x, int y);
		virtual void move_character(int input);
	};
}