#pragma once
#include "abstractNode.h"

class AVLNode final : public abstractNode<AVLNode>
{        
    public:
        AVLNode(int, AVLNode*, AVLNode*, AVLNode*);
        AVLNode(int);
        
        AVLNode *findNodeSoft(AVLTree*, int) override,
                *findNodeExact(AVLTree*, int) override,
                *findNodeSuccesor(AVLNode*) override,
                *minNode(AVLNode*) override,
                *maxNode(AVLNode*) override;
                            
        void    linkLeft(AVLNode*) override,
                linkRight(AVLNode*) override,
                cleanAllLinks() override,
                addNode(AVLTree*) override,
                deleteNode(AVLTree*) override,
                printInfo() const override,
                updateTree(AVLTree*);               
};