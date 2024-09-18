#pragma once
#include "abstractNode.h"
#include <iostream>

class AVLNode final : public abstractNode<AVLNode>
{   
        friend AVLTree;
        
        public:
                AVLNode(int, AVLNode*, AVLNode*, AVLNode*);
                AVLNode(int);
                
                AVLNode *findNodeExact(AVLTree*, int) override;

                void    addNodeTo(AVLTree*) override,
                        deleteNodeFrom(AVLTree*) override,
                        printInfo() override;
    
    
        protected:
                unsigned nodeHeight {0};
                
                int     getBalanceRate(AVLNode*),
                        getNodeHeight(AVLNode*) override;

                void    linkLeft(AVLNode*) override,
                        linkRight(AVLNode*) override,
                        cleanAllLinks() override,
                        updateSubtreeHeights(AVLTree*, AVLNode*),
                        updateNodeHeight(AVLNode*),
                        balanceTree(AVLTree*, AVLNode*);
                
                AVLNode *findNodeSoft(AVLTree*, int) override,
                        *findNodeSuccesor(AVLNode*) override,
                        *minNode(AVLNode*) override,
                        *maxNode(AVLNode*) override,
                        *turnLeft(AVLNode*),
                        *turnRight(AVLNode*);      
};