#pragma once

#include <vector>
#include <iostream>
#include <algorithm>

class abstractNode;

class Tree
{
        protected:
                std::vector<abstractNode*> nodesMap;
        public:
                abstractNode* getRoot();
                void    addToMap(abstractNode*),
                        deleteFromMap(abstractNode*);
                size_t getNodesCount();
};
