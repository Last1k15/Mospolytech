#pragma once
#include "abstractNode.h"

class AVLNode final : public abstractNode<AVLNode>
{        
    public:
        AVLNode(int, AVLNode*, AVLNode*, AVLNode*);
        AVLNode(int);
        
        AVLNode *findNodeExact(AVLTree*, int) override;

        void    addNodeTo(AVLTree*) override,
                deleteNodeFrom(AVLTree*) override,
                printInfo() const override;
    protected:
        bool isOverloaded {false};

        void    linkLeft(AVLNode*) override,
                linkRight(AVLNode*) override,
                cleanAllLinks() override,
                updateBranchHeights(AVLTree*, AVLNode*) override;
        
        AVLNode *findNodeSoft(AVLTree*, int) override,
                *findNodeSuccesor(AVLNode*) override,
                *minNode(AVLNode*) override,
                *maxNode(AVLNode*) override;         
};