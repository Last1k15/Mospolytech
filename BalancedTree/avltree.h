#pragma once

class AVLNode;
#include "avlnode.h"

#include <vector>
#include <iostream>
#include <algorithm>

class AVLTree
{
    protected:
        unsigned treeHeight{0};
        std::vector<AVLNode*> nodesMap;
    public:
        AVLNode* getRoot();
        void    addToMap(AVLNode*),
                deleteFromMap(AVLNode*),
                printAllInfo();
        size_t getNodesCount();
};