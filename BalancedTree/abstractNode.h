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

        virtual void    printInfo() const = 0,
                        addNodeTo(AVLTree*) = 0,
                        deleteNodeFrom(AVLTree*) = 0;
                        
    protected:
        int key;
        unsigned nodeHeight {0};

        Derived *parentNode {nullptr},
                *leftNode {nullptr},
                *rightNode {nullptr};

        virtual void    linkLeft(Derived*) = 0,
                        linkRight(Derived*) = 0,
                        cleanAllLinks() = 0,
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

// template <typename Derived>
// Derived* abstractNode<Derived>::findNodeSoft(AVLTree*, int){static_cast<Derived*>(this)->findNodeSoft();}

// template <typename Derived>
// Derived* abstractNode<Derived>::findNodeExact(AVLTree*, int){static_cast<Derived*>(this)->findNodeExact();}

// template <typename Derived>
// Derived* abstractNode<Derived>::findNodeSuccesor(Derived*){static_cast<Derived*>(this)->findNodeSuccesor();}

// template <typename Derived>
// Derived* abstractNode<Derived>::minNode(Derived*){static_cast<Derived*>(this)->minNodeTree();}

// template <typename Derived>
// Derived* abstractNode<Derived>::maxNode(Derived*){static_cast<Derived*>(this)->maxNode();}