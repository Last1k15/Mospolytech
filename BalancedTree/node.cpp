#include "node.h"

Node::Node(int ikey, Node* lN, Node* rN, Node* pN)
    :   abstractNode(ikey, lN, rN, pN){}

Node::Node(int ikey)
    :   abstractNode(ikey){}

void Node::printInfo() const
{
        std::cout << "---------------------\n";
        std::cout << "KEY: " << key << '\n';
        std::cout << "PARENT BRANCH: " << (parentNode ? std::to_string(parentNode->key) : "UNDEFINED") << '\n';
        std::cout << "LEFT BRANCH: " << (leftNode ? std::to_string(leftNode->key) : "UNDEFINED") << '\t';
        std::cout << "RIGHT BRANCH: " << (rightNode ? std::to_string(rightNode->key) : "UNDEFINED") << '\n';
        std::cout << "---------------------\n\n";
}