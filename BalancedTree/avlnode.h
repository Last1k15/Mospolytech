#pragma once
#include "abstractNode.h"

class AVLNode final : public abstractNode<AVLNode>
{        
    public:
        AVLNode(int, AVLNode*, AVLNode*, AVLNode*);
        AVLNode(int);
        

        static  AVLNode     *findNodeSoft(AVLTree*, int),
                            *findNodeExact(AVLTree*, int),
                            *findNodeSuccesor(AVLNode*),
                            *minNode(AVLNode*),
                            *maxNode(AVLNode*);
                            
        void    linkLeft(AVLNode*) override,
                linkRight(AVLNode*) override,
                cleanAllLinks() override,
                addNode(AVLTree*) override,
                deleteNode(AVLTree*) override,
                printInfo() const override,
                updateTree(AVLTree*);               
};