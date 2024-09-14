#pragma once

class AVLNode;
#include "avlnode.h"

#include <vector>
#include <iostream>
#include <algorithm>

class AVLTree
{
    friend AVLNode;
    
    public:
        AVLNode* getRoot();
        void printAllInfo();
        size_t getNodesCount();
    protected:
        unsigned treeHeight{0};
        std::vector<AVLNode*> nodesMap;

        void    addToMap(AVLNode*),
                deleteFromMap(AVLNode*),
                updateTreeHeight(unsigned);
};