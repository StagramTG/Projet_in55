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
        Character();
        Character(std::string name, std::string modelFile);
        ~Character();

        bool create(std::string name, std::string modelFile);

        virtual void update() override;
		virtual void render(ShaderProgram* shader) override;
    };
}