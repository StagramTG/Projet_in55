#include "Node.h"

namespace IN 
{
	Node::Node(std::string name)
	{
		mName = name;
	}

	Node::~Node()
	{
		mChildren.clear();
	}

	void Node::update()
	{
		for (auto child : mChildren)
		{
			child->update();
		}
	}

	void Node::render(ShaderProgram* shader)
	{
		for (auto child : mChildren)
		{
			child->render(shader);
		}
	}

	bool Node::addChild(Node * child)
	{
		if (child->mParent != nullptr)
		{
			return false;
		}

		child->mParent = this;
		mChildren.push_back(child);

		return true;
	}

	bool Node::removeChild(Node * child)
	{
		for (size_t i = 0; i < mChildren.size(); ++i)
		{
			if (mChildren[i] == child)
			{
				mChildren.erase(mChildren.begin() + i);
				return true;
			}
		}

		return false;
	}

	Node * Node::getChild(std::string name)
	{
		for (size_t i = 0; i < mChildren.size(); ++i)
		{
			if (mChildren[i]->mName == name)
			{
				return mChildren[i];
			}
		}

		return nullptr;
	}
}