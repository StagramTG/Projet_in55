#pragma once

#include "./Core/Node.h"

namespace IN
{
    class Character: public Node
    {
    private:

    public:
        Character();
        ~Character();

        virtual void update() override;
		virtual void render() override;
    };
}