#include "avlnode.h"


AVLNode::AVLNode(int ikey, AVLNode* lN, AVLNode* rN, AVLNode* pN)
    :   abstractNode(ikey, lN, rN, pN){}

AVLNode::AVLNode(int ikey)
    :   abstractNode(ikey){}

void AVLNode::printInfo() const
{
        std::cout << "---------------------\n";
        std::cout << "KEY: " << key << '\n';
        std::cout << "NODE HEIGHT: " << nodeHeight << '\n';
        std::cout << "PARENT BRANCH: " << (parentNode ? std::to_string(parentNode->key) : "UNDEFINED") << '\n';
        std::cout << "LEFT BRANCH: " << (leftNode ? std::to_string(leftNode->key) : "UNDEFINED") << '\t';
        std::cout << "RIGHT BRANCH: " << (rightNode ? std::to_string(rightNode->key) : "UNDEFINED") << '\n';
        std::cout << "---------------------\n\n";
}

void AVLNode::linkLeft(AVLNode* node)
{
    if (this == node) return;

    this->leftNode = node;
    node->parentNode = this;
}

void AVLNode::linkRight(AVLNode* node)
{
        if (this == node || node == nullptr) return;

        this->rightNode = node;
        node->parentNode = this;
}

void AVLNode::cleanAllLinks()
{
    if (this == nullptr) return;

    parentNode = nullptr;
    leftNode = nullptr;
    rightNode = nullptr;
}

AVLNode* AVLNode::minNode(AVLNode* node)
{
    if (node == nullptr) return nullptr;

    AVLNode *currentNode {node};
    while (currentNode->leftNode != nullptr) currentNode = currentNode->leftNode;
    return currentNode;
}

AVLNode* AVLNode::maxNode(AVLNode* node)
{
    if (node == nullptr) return nullptr;
    
    AVLNode *currentNode {node};
    while (currentNode->rightNode != nullptr) currentNode = currentNode->rightNode;
    return currentNode;
}

AVLNode* AVLNode::findNodeSoft(AVLTree* tree, int key)
{
    if (tree == nullptr) return nullptr;

    AVLNode *currentNode {tree->getRoot()},
            *prevNode{nullptr};

    while (currentNode != nullptr && key != currentNode->key)
    {
        prevNode = currentNode;
        currentNode = (key < currentNode->key) ? currentNode->leftNode : currentNode->rightNode;
    }

    if (currentNode != nullptr) prevNode = currentNode;
    return prevNode;
}
AVLNode* AVLNode::findNodeExact(AVLTree* tree, int key)
{
    if (tree == nullptr) return nullptr;

    AVLNode *currentNode {tree->getRoot()};

    while (currentNode != nullptr && key != currentNode->key)
        currentNode = (key < currentNode->key) ? currentNode->leftNode : currentNode->rightNode;

    return currentNode;
}

AVLNode* AVLNode::findNodeSuccesor(AVLNode* node)
{
    if (node == nullptr) return nullptr;

    // Если правое поддрево существует, результат - минимальный элемент правого поддрева
    if (node->rightNode != nullptr) {return minNode(node->rightNode);}

    AVLNode *currentNode {node};
    
    // Опускаемся по древу, пока не уткнемся в корни или пока текущая ветка не будет левой для следующей
    while (currentNode->parentNode != nullptr && currentNode->parentNode->leftNode != currentNode)
        currentNode = currentNode->parentNode;

    // Если не уткнулись к корни - возвращаем родителя как последователя узла, иначе вернем корни
    if (currentNode->parentNode != nullptr) currentNode = currentNode->parentNode;

    return currentNode;

}
void AVLNode::addNodeTo(AVLTree* tree)
{
    if (tree == nullptr || this == nullptr) return;

    // Древо пустое - узел стал корнем
    if (tree->getNodesCount() == 0) {tree->addToMap(this);return;};

    // Значение ключа goalNode равно либо ключу узла, если он есть в древе, либо ключу будущего родителя узла
    AVLNode* goalNode {findNodeSoft(tree, this->key)};
    
    // node уже есть в древе, завершаем за ненадобностью
    if (goalNode->key == this->key) return;

    // node нет в древе, добавляем в зависимости от значения ключа к нужному поддреву 
    if (this->key < goalNode->key) goalNode->linkLeft(this);
    else goalNode->linkRight(this);

    tree->addToMap(this);
    updateBranchHeights(tree, this);
}

void AVLNode::deleteNodeFrom(AVLTree* tree)
{
        if (tree == nullptr || this == nullptr) return;

        int childCount {(leftNode != nullptr) + (rightNode != nullptr)};
        
        // Возможные случаи в зависимости от количества потомков
        switch (childCount)
        {
            // Случай #1 - "Лист" (0 потомков)
            case 0:
            {
                // Удаляем связь родителя с узлом
                if (parentNode->leftNode == this) parentNode->leftNode = nullptr;
                else parentNode->rightNode = nullptr;
                
                updateBranchHeights(tree, parentNode);
                
                // Удаляем связь узла с родителем
                parentNode = nullptr;

                // Удаляем из карты дерева
                tree->deleteFromMap(this);
                
                // Удаляем из памяти
                delete this;
                
                break;
            }


            // Случай #2 - 1 потомок
            case 1:
            {
                // 3 фигурирующих стороны: Дед -> Отец (текущий узел) -> Внук

                // Указатель на внука
                AVLNode *childPtr {(leftNode == nullptr) ? rightNode : leftNode};

                // Теперь родитель внука - дед
                childPtr->parentNode = parentNode;

                // Теперь потомок деда - внук
                if (parentNode->leftNode == nullptr) parentNode->rightNode = childPtr;
                else parentNode->leftNode = childPtr;

                // Очищаем все связи отца
                cleanAllLinks();

                // Удаляем отца из карты дерева
                tree->deleteFromMap(this);

                // Удаляем отца из памяти
                delete this;
                updateBranchHeights(tree, childPtr);
                break;
            }


            // Случай #3 - 2 потомка
            
            case 2:
            {
                // Находим последователя узла
                AVLNode* succesor {findNodeSuccesor(this)};
                
                // Меняемся с ним ключами
                std::swap(key, succesor->key);
                succesor->deleteNodeFrom(tree);
                updateBranchHeights(tree, succesor);
                break;
            }

        }
}

void AVLNode::updateBranchHeights(AVLTree* tree, AVLNode* node)
{
    // Ловим некорректные аргументы 
    if (node == nullptr || tree == nullptr) return;

    // Узел для итерации по дереву
    AVLNode* currentNode {node};
    
    // Счетчик детей
    int childCount;

    while(currentNode != nullptr)
    {
        // Считаем существующих потомков
        childCount = (currentNode->leftNode != nullptr) + (currentNode->rightNode != nullptr);
        
        switch (childCount)
        {
            case 0:
            {
                // Если потомков нет, значит узел - лист, и его высота равна нулю
                currentNode->nodeHeight = 0;
                break;
            }

            case 1:
            {
                // Если потомок один, то высота узла будет равна высоте его потомка + 1
                AVLNode *childPtr = (currentNode->leftNode == nullptr) ? currentNode->rightNode : currentNode->leftNode;
                currentNode->nodeHeight = childPtr->nodeHeight + 1;
                break;
            }

            case 2:
            {
                // Если потомков два, то высота узла будет на один больше максимальной из высот потомков
                unsigned    leftNodeHeight {currentNode->leftNode->nodeHeight},
                            rightNodeHeight {currentNode->rightNode->nodeHeight};
                
                currentNode->nodeHeight = std::max(leftNodeHeight, rightNodeHeight) + 1;
                break;
            }
        };

        // Если достигли корня - обновляем высоту дерева и выходим
        if (currentNode->parentNode == nullptr)
        {
            tree->updateTreeHeight(currentNode->nodeHeight);
            return;
        }
        
        // Опускаемся к корню
        currentNode = currentNode->parentNode;
    }
}