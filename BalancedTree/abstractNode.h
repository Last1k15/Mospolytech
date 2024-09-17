#pragma once

#include <iostream>

class AVLTree;
#include "avltree.h"

template <typename Derived>
class abstractNode
{
    public:
        abstractNode(int, Derived*, Derived*, Derived*);
        abstractNode(int);

        virtual Derived *findNodeExact(AVLTree*, int) = 0;

        virtual void    printInfo() = 0,
                        addNodeTo(AVLTree*) = 0,
                        deleteNodeFrom(AVLTree*) = 0;
                        
    protected:
        int key;
        unsigned nodeHeight {0};

        Derived *parentNode {nullptr},
                *leftNode {nullptr},
                *rightNode {nullptr};

        virtual int getNodeHeight(Derived*) = 0;
        
        virtual void    linkLeft(Derived*) = 0,
                        linkRight(Derived*) = 0,
                        cleanAllLinks() = 0,
                        updateNodeHeight(AVLNode*) = 0,
                        updateBranchHeights(AVLTree*, Derived*) = 0;

        virtual Derived *findNodeSoft(AVLTree*, int) = 0,
                        *findNodeSuccesor(Derived*) = 0,
                        *minNode(Derived*) = 0,
                        *maxNode(Derived*) = 0;

                        
};

template <typename Derived>
abstractNode<Derived>::abstractNode(int ikey, Derived* lN, Derived* rN, Derived* pN)
    :   key {ikey},
        leftNode {lN},
        rightNode {rN},
        parentNode {pN}{}

template <typename Derived>
abstractNode<Derived>::abstractNode(int ikey)
    :   key {ikey}{}