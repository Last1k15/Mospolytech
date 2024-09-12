#include "abstractNode.h"

// void abstractNode::linkLeft(abstractNode* node)
// {
//     if (this == node) return;

//     this->leftNode = node;
//     node->parentNode = this;
// }

// void abstractNode::linkRight(abstractNode* node)
// {
//         if (this == node || node == nullptr) return;

//         this->rightNode = node;
//         node->parentNode = this;
// }

// void abstractNode::cleanAllLinks()
// {
//     if (this == nullptr) return;

//     parentNode = nullptr;
//     leftNode = nullptr;
//     rightNode = nullptr;
// }

// abstractNode* abstractNode::minNode(abstractNode* node)
// {
//     if (node == nullptr) return nullptr;

//     abstractNode *currentNode {node};
//     while (currentNode->leftNode != nullptr) currentNode = currentNode->leftNode;
//     return currentNode;
// }

// abstractNode* abstractNode::maxNode(abstractNode* node)
// {
//     if (node == nullptr) return nullptr;
    
//     abstractNode *currentNode {node};
//     while (currentNode->rightNode != nullptr) currentNode = currentNode->rightNode;
//     return currentNode;
// }

// abstractNode* abstractNode::findNodeSoft(Tree* tree, int key)
// {
//     if (tree == nullptr) return nullptr;

//     abstractNode    *currentNode {tree->getRoot()},
//                     *prevNode{nullptr};

//     while (currentNode != nullptr && key != currentNode->key)
//     {
//         prevNode = currentNode;
//         currentNode = (key < currentNode->key) ? currentNode->leftNode : currentNode->rightNode;
//     }

//     if (currentNode != nullptr) prevNode = currentNode;
//     return prevNode;
// }
// abstractNode* abstractNode::findNodeExact(Tree* tree, int key)
// {
//     if (tree == nullptr) return nullptr;

//     abstractNode *currentNode {tree->getRoot()};

//     while (currentNode != nullptr && key != currentNode->key)
//         currentNode = (key < currentNode->key) ? currentNode->leftNode : currentNode->rightNode;

//     return currentNode;
// }

// abstractNode* abstractNode::findNodeSuccesor(abstractNode* node)
// {
//     if (node == nullptr) return nullptr;

//     // Если правое поддрево существует, результат - минимальный элемент правого поддрева
//     if (node->rightNode != nullptr) {return minNode(node->rightNode);}

//     abstractNode *currentNode {node};
    
//     // Опускаемся по древу, пока не уткнемся в корни или пока текущая ветка не будет левой для следующей
//     while (currentNode->parentNode != nullptr && currentNode->parentNode->leftNode != currentNode)
//         currentNode = currentNode->parentNode;

//     // Если не уткнулись к корни - возвращаем родителя как последователя узла, иначе вернем корни
//     if (currentNode->parentNode != nullptr) currentNode = currentNode->parentNode;

//     return currentNode;

// }
// void abstractNode::addNode(Tree* tree)
// {
//     if (tree == nullptr || this == nullptr) return;

//     // Древо пустое - узел стал корнем
//     if (tree->getNodesCount() == 0) {tree->addToMap(this);return;};

//     // Значение ключа goalNode равно либо ключу узла, если он есть в древе, либо ключу будущего родителя узла
//     abstractNode* goalNode {findNodeSoft(tree, this->key)};
    
//     // node уже есть в древе, завершаем за ненадобностью
//     if (goalNode->key == this->key) return;

//     // node нет в древе, добавляем в зависимости от значения ключа к нужному поддреву 
//     if (this->key < goalNode->key) goalNode->linkLeft(this);
//     else goalNode->linkRight(this);

//     tree->addToMap(this);
// }

// void abstractNode::deleteNode(Tree* tree)
// {
//         if (tree == nullptr || this == nullptr) return;

//         int childCount {(leftNode != nullptr) + (rightNode != nullptr)};
        
//         // Указатель на единственного потомка (случай #2)
//         abstractNode *childPtr {(parentNode->leftNode == nullptr) ? rightNode : leftNode};
        
//         // Возможные случаи в зависимости от количества потомков
//         switch (childCount)
//         {
//             // Случай #1 - "Лист" (0 потомков)
//             case 0:
                
//                 // Удаляем связь родителя с узлом
//                 if (parentNode->leftNode == this) parentNode->leftNode = nullptr;
//                 else parentNode->rightNode = nullptr;
                
//                 // Удаляем связь узла с родителем
//                 parentNode = nullptr;

//                 // Удаляем из карты дерева
//                 tree->deleteFromMap(this);
                
//                 // Удаляем из памяти
//                 delete this;

//                 break;

//             // Случай #2 - 1 потомок
//             case 1:
//                 // 3 фигурирующих стороны: Дед -> Отец (текущий узел) -> Внук
                
//                 // Теперь родитель внука - дед
//                 childPtr->parentNode = parentNode;

//                 // Теперь потомок деда - внук
//                 if (parentNode->leftNode == nullptr) parentNode->rightNode = childPtr;
//                 else parentNode->leftNode = childPtr;

//                 // Очищаем все связи отца
//                 cleanAllLinks();

//                 // Удаляем отца из карты дерева
//                 tree->deleteFromMap(this);

//                 // Удаляем отца из памяти
//                 delete this;

//                 break;

//             // Случай #3 - 2 потомка
            
//             case 2:
//                 // Находим последователя узла
//                 abstractNode* succesor {findNodeSuccesor(this)};
                
//                 // Меняемся с ним ключами
//                 std::swap(key, succesor->key);
//                 succesor->deleteNode(tree);
//                 break;
//         }
// }
