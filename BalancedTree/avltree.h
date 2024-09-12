#pragma once

#include "node.h"

class AVLTree final : public Tree 
{
    public:
        unsigned treeHeight {0};
        Node* getRoot();
        void printAllInfo();
};