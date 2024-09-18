#pragma once

class AVLNode;
#include "avlnode.h"

#include <vector>
#include <algorithm>

class AVLTree
{
        friend AVLNode;
    
        public:
                AVLNode *getRoot(),
                        *getNodebyIndex(size_t);
                void    printAllInfo(),
                        printTaskAnswer();
                size_t getNodesCount();


        protected:
                unsigned treeHeight{0};
                std::vector<AVLNode*> nodesMap;

                void    addToMap(AVLNode*),
                        deleteFromMap(AVLNode*),
                        setTreeHeight(unsigned),
                        sortNodesMap();
};