#pragma once

#include "./Core/Node.h"
#include "./Models/Model.h"

namespace IN
{
    class Character: public Node
    {
    private:
        Model mModel;

    public:
        Character(std::string name, std::string modelFile);
        ~Character();

        virtual void update() override;
		virtual void render() override;
    };
}