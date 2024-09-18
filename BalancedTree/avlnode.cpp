#include "avlnode.h"

AVLNode::AVLNode(int ikey, AVLNode* lN, AVLNode* rN, AVLNode* pN)
    :   abstractNode(ikey, lN, rN, pN){}


AVLNode::AVLNode(int ikey)
    :   abstractNode(ikey){}


/* Выводит информацию о узле: ключ, высоту, рейтинг баланса, ключи родителя и потомков */
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


/* Взаимно соединяет узел, вызывающий метод (родитель), и переданный узел-аргумент (потомок) слева. */
void AVLNode::linkLeft(AVLNode* node)
{
    // Избегаем самоприсваивания
    if (this == node) return;

    // Убираем связь предыдущего потомка с родителем
    if (leftNode != nullptr) leftNode->parentNode = nullptr;
    
    // Связываем родителя с потомком
    leftNode = node;

    // Если потомок существует..
    if (node != nullptr)
    {
        // ..и у него был другой родитель..
        if (node->parentNode != nullptr)
        {
            // ..удаляем связь с предыдущим родителем 
            if (node->parentNode->key < node->key) node->parentNode->rightNode = nullptr;
            else node->parentNode->leftNode = nullptr;
        }

        // ..cвязываем потомка с родителем
        node->parentNode = this;
    }
}


/* Взаимно соединяет узел, вызывающий метод (родитель), и переданный узел-аргумент (потомок) справа. */
void AVLNode::linkRight(AVLNode* node)
{
    // Избегаем самоприсваивания
    if (this == node) return;
    
    // Убираем связь предыдущего потомка с родителем
    if (rightNode != nullptr) rightNode->parentNode = nullptr;
    
    // Связываем родителя с потомком
    rightNode = node;
    
    // Если потомок существует..
    if (node != nullptr)
    {
        // ..и у него был другой родитель..
        if (node->parentNode != nullptr)
        {
            // ..удаляем связь с предыдущим родителем 
            if (node->parentNode->key < node->key) node->parentNode->rightNode = nullptr;
            else node->parentNode->leftNode = nullptr;
        }

        // ..cвязываем потомка с родителем
        node->parentNode = this;
    }
}


/* Удаляет связи ненулевого узла с потомками и родителем */
void AVLNode::cleanAllLinks()
{
    if (this == nullptr) return;

    parentNode = nullptr;
    leftNode = nullptr;
    rightNode = nullptr;
}


/* Находит минимальный ключ в поддреве с корнем node */
AVLNode* AVLNode::minNode(AVLNode* node)
{
    // Избегаем нулевые указатели
    if (node == nullptr) return nullptr;

    // Указатель на узел для итерации
    AVLNode *currentNode {node};

    // Поднимаемся по древу пока существует левый потомок
    while (currentNode->leftNode != nullptr) currentNode = currentNode->leftNode;
    
    // Возвращаем узел, на котором остановились
    return currentNode;
}


/* Находит максимальный ключ в поддреве с корнем node */
AVLNode* AVLNode::maxNode(AVLNode* node)
{
    // Избегаем нулевые указатели
    if (node == nullptr) return nullptr;
    
    // Указатель на узел для итерации
    AVLNode *currentNode {node};

    // Поднимаемся по древу пока существует левый потомок
    while (currentNode->rightNode != nullptr) currentNode = currentNode->rightNode;

    // Возвращаем узел, на котором остановились
    return currentNode;
}


/* Находит узел по ключу. Если такого в древе нет, возвращает узел, на котором остановился поиск */
AVLNode* AVLNode::findNodeSoft(AVLTree* tree, int key)
{
    // Избегаем нулевых указателей
    if (tree == nullptr) return nullptr;

    // Указатель на узел currentNode для итерации, prevNode для буферизации, начинаем поиск с корня 
    AVLNode *currentNode {tree->getRoot()},
            *prevNode{nullptr};

    // Пока не поднимемся до вершины древа или пока не найдем узел..
    while (currentNode != nullptr && key != currentNode->key)
    {
        // ..сохраняем предыдущее значение currentNode
        prevNode = currentNode;
        
        // Поднимаемся по нужной ветви
        currentNode = (key < currentNode->key) ? currentNode->leftNode : currentNode->rightNode;
    }

    // Если не достигли вершины древа, значит узел был найден, возвращаем его
    if (currentNode != nullptr) return currentNode;

    // Иначе возвращаем узел, на котором остановились
    return prevNode;
}


/* Находит узел по ключу. Если такого в древе нет, возвращает нулевой указатель */
AVLNode* AVLNode::findNodeExact(AVLTree* tree, int key)
{
    // Избегаем нулевых указателей
    if (tree == nullptr) return nullptr;

    // Указатель на узел для итерации, начинаем с корня
    AVLNode *currentNode {tree->getRoot()};

    // Пока не поднимемся до вершины древа или пока не найдем узел..
    while (currentNode != nullptr && key != currentNode->key)
        // ..поднимаемся по нужной ветви
        currentNode = (key < currentNode->key) ? currentNode->leftNode : currentNode->rightNode;

    // Возвращем найденный узел или nullptr, если достигли вершины древа
    return currentNode;
}


/* Находит последователя узла (Узел с минимальным ключом, который больше, чем ключ node) */
AVLNode* AVLNode::findNodeSuccesor(AVLNode* node)
{
    // Избегаем нулевых указателей
    if (node == nullptr) return nullptr;

    // Если правое поддрево существует, результат - минимальный элемент правого поддрева
    if (node->rightNode != nullptr) {return minNode(node->rightNode);}

    // Указатель на узел для итерации, начинаем с node
    AVLNode *currentNode {node};
    
    // Опускаемся по древу, пока не уткнемся в корни или пока текущее поддрево не будет левым для следующего
    while (currentNode->parentNode != nullptr && currentNode->parentNode->leftNode != currentNode)
        currentNode = currentNode->parentNode;

    // Если не уткнулись к корни - возвращаем родителя как последователя узла
    if (currentNode->parentNode != nullptr) return currentNode->parentNode;

    // Иначе возвращаем корни
    return currentNode;

}


// Добавляет узел к древу
void AVLNode::addNodeTo(AVLTree* tree)
{
    // Избегаем нулевых указателей
    if (tree == nullptr) return;

    // Если древо пустое, значит узел станет его корнем
    if (tree->getNodesCount() == 0) {tree->addToMap(this);return;};

    // Значение ключа goalNode равно либо ключу узла, если он есть в древе, либо ключу будущего родителя узла
    AVLNode* goalNode {findNodeSoft(tree, this->key)};

    // Если узел уже есть в древе - завершаем за ненадобностью
    if (goalNode->key == this->key) return;

    // Является ли родитель нового узла листом
    bool isLeaf { (goalNode->leftNode == nullptr) && (goalNode->rightNode == nullptr) };

    // Узла нет в древе, добавляем в зависимости от значения ключа к нужному поддреву 
    if (this->key < goalNode->key) goalNode->linkLeft(this);
    else goalNode->linkRight(this);

    // Добавляем новый узел в карту древа
    tree->addToMap(this);

    // Если родитель нового узла был листом, значит высоты предыдущих узлов изменились
    if (isLeaf) updateSubtreeHeights(tree, this);
    
}


/* Удаляет узел из древа */
void AVLNode::deleteNodeFrom(AVLTree* tree)
{
        // Избегаем нулевых указателей
        if (tree == nullptr) return;

        // Количество существующих потомков
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
                
                // После удаления сразу обновим высоты узлов и при надобности сбалансируем древо
                updateSubtreeHeights(tree, parentNode);
                
                // Удаляем связь узла с родителем
                parentNode = nullptr;

                // Удаляем узел из карты дерева
                tree->deleteFromMap(this);
                
                // Удаляем узел из памяти
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
                
                // После удаления сразу обновим высоты узлов и при надобности сбалансируем древо
                updateSubtreeHeights(tree, childPtr);
                break;
            }

            // Случай #3 - 2 потомка
            case 2:
            {
                // Находим последователя узла
                AVLNode* succesor {findNodeSuccesor(this)};
                
                // Меняемся с ним ключами
                std::swap(key, succesor->key);

                // Сводим задачу к удалению последователя
                succesor->deleteNodeFrom(tree);

                // После удаления сразу обновим высоты деревьев и при надобности сбалансируем древо
                updateSubtreeHeights(tree, succesor);
                break;
            }

        }
}


/* Приравнивает высоту узла к максимальной высоте потомков + 1*/
void AVLNode::updateNodeHeight(AVLNode* node){if (node) node->nodeHeight = std::max(getNodeHeight(node->leftNode), getNodeHeight(node->rightNode)) + 1;}


/* Проходится циклом от node до корня, обновляя высоты и при надобности балансируя ветки. При балансировке высота перемещенных узлов рассчитывается заново*/
void AVLNode::updateSubtreeHeights(AVLTree* tree, AVLNode* node)
{
    // Узел для итерации
    AVLNode* currentNode {node};

    // Опускаемся по ветвям до корня
    while(currentNode != nullptr)
    {
        // Обновляем высоту текущего узла
        updateNodeHeight(currentNode);

        // Балансируем ветку при надобности
        balanceTree(tree,currentNode);

        // Если достигли корня..
        if (currentNode->parentNode == nullptr)
        {
            // ..обновляем высоту древа
            tree->setTreeHeight(currentNode->nodeHeight);
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


/* При необходимости поворачивает поддрева и обновляет порядок карты древа */
void AVLNode::balanceTree(AVLTree* tree, AVLNode* node)
{
    // Вычисляем рейтинг баланса
    int bRate {getBalanceRate(node)};

    switch (bRate)
    {
        // Случай #1 - древо перегружено влево
        case -2:
            // Если у потомка положительный рейтинг баланса, то необходимо сперва выпрямить поддерево левым поворотом (Выполняется LR-поворот)
            if (getBalanceRate(node->leftNode) > 0){node->leftNode = turnLeft(node->leftNode);}
            
            // Поворачиваем древо вправо относительно node
            turnRight(node);

            // При балансировке порядок узлов изменился, обновим порядок карты древа
            tree->sortNodesMap();
            
            break;
        
        // Случай #2 - древо перегружено вправо
        case 2:
            // Если у потомка отрицательный рейтинг баланса, то необходимо сперва выпрямить поддерево правым поворотом (Выполняется RL-поворот)
            if (getBalanceRate(node->rightNode) < 0) node->rightNode = turnRight(node->rightNode);
            
            // Поворачиваем древо вправо относительно node
            turnLeft(node);

            // При балансировке порядок узлов изменился, обновим порядок карты древа 
            tree->sortNodesMap();

            break;
    }
}


/* Поворачивает поддрево влево */
AVLNode* AVLNode::turnLeft(AVLNode* node)
{
    
    // При левом повороте фигурируют три основные стороны: subtreeParent -> node -> rightChild
    // В результате поворота порядок станет таким: subtreeParent -> rightChild -> node
    // subtreeParent - родитель поддрева - крайний узел, который лишь частично участвует в повороте - меняется только его потомок

    AVLNode *rightChild {node->rightNode},
            *subtreeParent {node->parentNode};
    
    // Присоеднияем левого внука к node справа, так как он является последователем node
    node->linkRight(rightChild->leftNode);

    // Если родитель поддрева существует..
    if (subtreeParent != nullptr)
    {
        // ..заранее связываем его с новым потомком (rightChild)
        if (subtreeParent->leftNode == node) subtreeParent->linkLeft(rightChild);
        else subtreeParent->linkRight(rightChild);
    }

    // Связываем rightChild с node слева, фактически меняя их местами
    rightChild->linkLeft(node);
    
    // Обновляем высоты затронутых узлов
    updateNodeHeight(node);
    updateNodeHeight(rightChild);

    // Возвращаем ближайший к корню измененный узел
    return rightChild;
}


/* Поворачивает древо вправо */
AVLNode* AVLNode::turnRight(AVLNode* node)
{

    // При правом повороте фигурируют три основные стороны: subtreeParent -> node -> leftChild
    // В результате поворота порядок станет таким: subtreeParent -> leftChild -> node
    // subtreeParent - родитель поддрева - крайний узел, который лишь частично участвует в повороте - меняется только его потомок

    AVLNode *leftChild {node->leftNode},
            *subtreeParent {node->parentNode};

    // Присоеднияем правого внука к node слева, так как node является его последователем
    node->linkLeft(leftChild->rightNode);

    // Если родитель поддрева существует..
    if (subtreeParent != nullptr)
    {
        // ..заранее связываем его с новым потомком (leftChild)
        if (subtreeParent->leftNode != nullptr) subtreeParent->linkLeft(leftChild);
        else subtreeParent->linkRight(leftChild);
    }

    // Связываем leftChild с node слева, фактически меняя их местами
    leftChild->linkRight(node);

    // Обновляем высоты затронутых узлов
    updateNodeHeight(node);
    updateNodeHeight(leftChild);

    // Возвращаем ближайший к корню измененный узел
    return leftChild;
}