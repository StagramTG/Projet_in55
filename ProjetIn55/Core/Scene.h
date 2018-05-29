#pragma once

#include "Node.h"

namespace IN 
{
	class Scene: public Updatable, public Renderable
	{
	private:
		/* Name of the scene, should be unique */
		std::string mName;
		/* Base node in the scene, only one */
		Node* mRootNode;

	public:
		Scene(std::string name);
		~Scene();

		virtual void update() override;
		virtual void render() override;

		std::string getName();
	};
}