#include "avltree.h"


/* Выводит информацию о всех узлах, их количество и высоту древа */
void AVLTree::printAllInfo()
{
        for (size_t i = 0; i < getNodesCount(); i++) nodesMap.at(i)->printInfo();
        std::cout << "NODES COUNT: " << getNodesCount() << "\n";
        std::cout << "TREE HEIGHT: " << treeHeight << "\n\n";
        std::cout << "\n\n\n\n";
}


/* Возвращает первый элемент nodesMap */
AVLNode* AVLTree::getRoot(){return nodesMap.at(0);}


/* Добавляет ненулевой узел в nodesMap */
void AVLTree::addToMap(AVLNode* node){if (node) nodesMap.push_back(node);}


/* Возвращает узел по индексу из nodesMap */
AVLNode* AVLTree::getNodebyIndex(size_t i){if (i < 0 && i >= nodesMap.size()) return nullptr; return nodesMap.at(i);}


/* Удаляет ненулевой узел из nodesMap */
void AVLTree::deleteFromMap(AVLNode* node){if (node) nodesMap.erase(std::find(nodesMap.begin(), nodesMap.end(), node));}


/* Устанавливает новое значение высоты древа */
void AVLTree::setTreeHeight(unsigned h) {treeHeight = h;}


/* Сортирует nodesMap относительно высоты узлов по убыванию */
void AVLTree::sortNodesMap(){std::sort(nodesMap.begin(), nodesMap.end(), [](AVLNode* a, AVLNode* b){return a->nodeHeight > b->nodeHeight;});}


/* Возвращает размер nodesMap */
size_t AVLTree::getNodesCount(){return nodesMap.size();}


/* Выводит ключи узлов по порядку из nodesMap */
void AVLTree::printTaskAnswer(){for (auto n : nodesMap) std::cout << n->key << '\t';}