#pragma once

#include "tree.h"

class abstractNode
{
    public:
        int key;
        abstractNode    *parentNode {nullptr},
                        *leftNode {nullptr},
                        *rightNode {nullptr};

        abstractNode(int, abstractNode*, abstractNode*, abstractNode*);
        abstractNode(int);
        
        ///////////////////////////////////////////

        static  abstractNode    *findNodeSoft(Tree*, int),
                                *findNodeExact(Tree*, int),
                                *findNodeSuccesor(abstractNode*),
                                *minNode(abstractNode*),
                                *maxNode(abstractNode*);
        void    addNode(Tree*),
                deleteNode(Tree*);                 

        ///////////////////////////////////////////

        void cleanAllLinks();

        virtual void printInfo() const = 0;

    protected:
        void    linkLeft(abstractNode*),
                linkRight(abstractNode*);

};