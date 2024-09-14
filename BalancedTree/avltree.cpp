#include "avltree.h"

void AVLTree::printAllInfo()
{
        std::cout << "NODES COUNT: " << getNodesCount() << "\n";
        std::cout << "TREE HEIGHT: " << treeHeight << "\n\n";
        for (size_t i = 0; i < getNodesCount(); i++) nodesMap.at(i)->printInfo();
        std::cout << "\n\n\n\n";
}

AVLNode* AVLTree::getRoot(){{return nodesMap.at(0);}}

void AVLTree::addToMap(AVLNode* node)
{
    if (node == nullptr) throw std::invalid_argument{"Cant add nullptr to map"};
    nodesMap.push_back(node);
}
void AVLTree::deleteFromMap(AVLNode* node)
{
    if (node == nullptr) return;
    nodesMap.erase(std::find(nodesMap.begin(), nodesMap.end(), node));
}
void AVLTree::updateTreeHeight(unsigned h) {treeHeight = h;}
size_t AVLTree::getNodesCount(){return nodesMap.size();}
