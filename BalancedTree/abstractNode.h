#pragma once

#include <iostream>
#include "avltree.h"

template <typename Derived>
class abstractNode
{
    public:
        abstractNode(int, Derived*, Derived*, Derived*);
        abstractNode(int);

        static  Derived     *findNodeSoft(AVLTree*, int),
                            *findNodeExact(AVLTree*, int),
                            *findNodeSuccesor(Derived*),
                            *minNode(Derived*),
                            *maxNode(Derived*);
                            
        virtual void    linkLeft(Derived*) = 0,
                        linkRight(Derived*) = 0,
                        cleanAllLinks() = 0,
                        addNode(AVLTree*) = 0,
                        deleteNode(AVLTree*) = 0,
                        printInfo() const = 0;
    protected:
        int key;
        unsigned nodeHeight {0};

        Derived *parentNode {nullptr},
                *leftNode {nullptr},
                *rightNode {nullptr};

                        
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

template <typename Derived>
Derived* abstractNode<Derived>::findNodeSoft(AVLTree*, int){static_cast<Derived*>(this)->findNodeSoft();}

template <typename Derived>
Derived* abstractNode<Derived>::findNodeExact(AVLTree*, int){static_cast<Derived*>(this)->findNodeExact();}

template <typename Derived>
Derived* abstractNode<Derived>::findNodeSuccesor(Derived*){static_cast<Derived*>(this)->findNodeSuccesor();}

template <typename Derived>
Derived* abstractNode<Derived>::minNode(Derived*){static_cast<Derived*>(this)->minNodeTree();}

template <typename Derived>
Derived* abstractNode<Derived>::maxNode(Derived*){static_cast<Derived*>(this)->maxNode();}