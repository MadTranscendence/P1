#ifndef NODE_HPP
#define NODE_HPP

#include "../core/transform.hpp"
#include "../core/types.hpp"

#include <vector>


namespace Game
{
    struct Node
    {
        Core::Transform   m_transform;
        std::vector<uint> m_gameObjects;
        std::vector<Node> m_children;
    };
}

#endif
