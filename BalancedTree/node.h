#pragma once

#include "abstractNode.h"

class Node final : public abstractNode
{        
    public:
        unsigned nodeHeight {0};
        Node(int, Node*, Node*, Node*);
        Node(int);
        
        void    printInfo() const override,
                updateTree(Tree*);               
};