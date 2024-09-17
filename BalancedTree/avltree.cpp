#include "avltree.h"

void AVLTree::printAllInfo()
{
        for (size_t i = 0; i < getNodesCount(); i++) nodesMap.at(i)->printInfo();
        std::cout << "NODES COUNT: " << getNodesCount() << "\n";
        std::cout << "TREE HEIGHT: " << treeHeight << "\n\n";
        std::cout << "\n\n\n\n";
}

AVLNode* AVLTree::getRoot(){return nodesMap.at(0);}

void AVLTree::addToMap(AVLNode* node){if (node) nodesMap.push_back(node);}

AVLNode* AVLTree::getNodebyIndex(size_t i){if (i < 0 && i >= nodesMap.size()) return nullptr; return nodesMap.at(i);}

void AVLTree::deleteFromMap(AVLNode* node){if (node) nodesMap.erase(std::find(nodesMap.begin(), nodesMap.end(), node));}

void AVLTree::updateTreeHeight(unsigned h) {treeHeight = h;}

void AVLTree::sortNodesMap()
{
    std::sort(nodesMap.begin(), nodesMap.end(), [](AVLNode* a, AVLNode* b){return a->nodeHeight > b->nodeHeight;});
}

size_t AVLTree::getNodesCount(){return nodesMap.size();}

void AVLTree::printTaskAnswer(){for (auto n : nodesMap) std::cout << n->key << '\t';}