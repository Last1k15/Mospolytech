#include "avlnode.h"

AVLNode::AVLNode(int ikey, AVLNode* lN, AVLNode* rN, AVLNode* pN)
    :   abstractNode(ikey, lN, rN, pN){}

AVLNode::AVLNode(int ikey)
    :   abstractNode(ikey){}

void AVLNode::printInfo()
{
        std::cout << "---------------------\n";
        std::cout << "KEY: " << key << '\n';
        std::cout << "NODE HEIGHT: " << nodeHeight << '\n';
        std::cout << "BALANCE RATE: " << getBalanceRate(this) << "\n\n";
        std::cout << "PARENT BRANCH: " << (parentNode ? std::to_string(parentNode->key) : "UNDEFINED") << '\n';
        std::cout << "LEFT BRANCH: " << (leftNode ? std::to_string(leftNode->key) : "UNDEFINED") << '\t';
        std::cout << "RIGHT BRANCH: " << (rightNode ? std::to_string(rightNode->key) : "UNDEFINED") << '\n';
        std::cout << "---------------------\n\n";
}

void AVLNode::linkLeft(AVLNode* node)
{
    if (this == node) return;
    if (leftNode != nullptr) leftNode->parentNode = nullptr;
    leftNode = node;
    if (node != nullptr)
    {
        if (node->parentNode != nullptr)
        {
            if (node->parentNode->key < node->key) node->parentNode->rightNode = nullptr;
            else node->parentNode->leftNode = nullptr;
        }
        node->parentNode = this;
    }
}
void AVLNode::linkRight(AVLNode* node)
{
    if (this == node) return;
    if (rightNode != nullptr) rightNode->parentNode = nullptr;
    rightNode = node;
    if (node != nullptr)
    {
        if (node->parentNode != nullptr)
        {
            if (node->parentNode->key < node->key) node->parentNode->rightNode = nullptr;
            else node->parentNode->leftNode = nullptr;
        }
        node->parentNode = this;
    }
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
    // Ловим некорректные аргумнеты
    if (tree == nullptr) return;
    // Если древо пустое, значит этот узел станет его корнем
    if (tree->getNodesCount() == 0) {tree->addToMap(this);return;};

    // Значение ключа goalNode равно либо ключу узла, если он есть в древе, либо ключу будущего родителя узла
    AVLNode* goalNode {findNodeSoft(tree, this->key)};

    // Узел уже есть в древе, завершаем за ненадобностью
    if (goalNode->key == this->key) return;

    // Является ли родитель нового узла листом
    bool isLeaf { (goalNode->leftNode == nullptr) && (goalNode->rightNode == nullptr) };
    // Узла нет в древе, добавляем в зависимости от значения ключа к нужному поддреву 
    if (this->key < goalNode->key) goalNode->linkLeft(this);
    else goalNode->linkRight(this);

    // Добавляем новый узел в карту древа
    tree->addToMap(this);

    // Если родитель нового узла был листом, значит высоты надо обновить
    if (isLeaf) updateBranchHeights(tree, this);
    
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
                
                // После удаления сразу обновим высоты деревьев и при надобности сбалансируем древо
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
                
                // После удаления сразу обновим высоты деревьев и при надобности сбалансируем древо
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

                // Сводим задачу к удалению последователя (случаи #1 или #2)
                succesor->deleteNodeFrom(tree);

                // После удаления сразу обновим высоты деревьев и при надобности сбалансируем древо
                updateBranchHeights(tree, succesor);
                break;
            }

        }
}

/* Приравнивает высоту узла к максимальной высоте потомков + 1*/
void AVLNode::updateNodeHeight(AVLNode* node){if (node) node->nodeHeight = std::max(getNodeHeight(node->leftNode), getNodeHeight(node->rightNode)) + 1;}

/* Проходится циклом от node до корня, обновляя высоты и при надобности балансируя ветки. При балансировке высота перемещенных узлов обновляется заново*/
void AVLNode::updateBranchHeights(AVLTree* tree, AVLNode* node)
{
    // Узел для итерации
    AVLNode* currentNode {node};

    // Опускаемся по веткам до корня
    while(currentNode != nullptr)
    {
        // Обновляем высоту текущего узла
        updateNodeHeight(currentNode);

        // Балансируем ветку при надобности, либо выходим из функции без изменений
        balanceTree(tree,currentNode);

        // Если достигли корня..
        if (currentNode->parentNode == nullptr)
        {
            // ..Обновляем высоту древа
            tree->updateTreeHeight(currentNode->nodeHeight);
            return;
        }

        // Иначе опускаемся ниже
        currentNode = currentNode->parentNode;
    }
    
}

/* Обертка для получения высоты, при пустом указателе вернёт -1 */
int AVLNode::getNodeHeight(AVLNode* node){return (node) ? node->nodeHeight : -1;}

/* Вычисляет и возвращает рейтинг баланса как разность высот потомков */
int AVLNode::getBalanceRate(AVLNode* node)
{
    if (node == nullptr) return 0;
    return (getNodeHeight(node->rightNode) - getNodeHeight(node->leftNode));
}

/* При необходимости поворачивает ветки и обновляет корень древа */
void AVLNode::balanceTree(AVLTree* tree, AVLNode* node)
{
    int bRate {getBalanceRate(node)};

    switch (bRate)
    {
        case -2:
            if (getBalanceRate(node->leftNode) > 0){node->leftNode = turnLeft(node->leftNode);}
            turnRight(node);
            tree->sortNodesMap();
            break;
        case 2:
            if (getBalanceRate(node->rightNode) < 0) node->rightNode = turnRight(node->rightNode);
            turnLeft(node);
            tree->sortNodesMap();
            break;
    }
}

AVLNode* AVLNode::turnLeft(AVLNode* node)
{
    AVLNode *rightChild {node->rightNode},
            *branchParent {node->parentNode};
    
    node->linkRight(rightChild->leftNode);

    if (branchParent != nullptr)
    {
        if (branchParent->leftNode == node) branchParent->linkLeft(rightChild);
        else branchParent->linkRight(rightChild);
    }

    rightChild->linkLeft(node);
    
    updateNodeHeight(node);
    updateNodeHeight(rightChild);

    return rightChild;
}

AVLNode* AVLNode::turnRight(AVLNode* node)
{
    AVLNode *leftChild {node->leftNode},
            *branchParent {node->parentNode};


    node->linkLeft(leftChild->rightNode);

    if (branchParent != nullptr)
    {
        if (branchParent->leftNode != nullptr) branchParent->linkLeft(leftChild);
        else branchParent->linkRight(leftChild);
    }

    leftChild->linkRight(node);

    updateNodeHeight(node);
    updateNodeHeight(leftChild);

    return leftChild;
}