#include "avltree.h"

void AVLTree::printAllInfo()
{
        std::cout << "NODES COUNT: " << getNodesCount() << "\n";
        std::cout << "TREE HEIGHT: " << treeHeight << "\n\n";
        for (size_t i = 0; i < getNodesCount(); i++) nodesMap.at(i)->printInfo();
        std::cout << "\n\n\n\n";
}