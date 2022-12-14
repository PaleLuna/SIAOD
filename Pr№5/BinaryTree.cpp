#include "BinaryTree.h"
/*******************************************************************PUBLIC********************************************************************/

BinaryTree::BinaryTree(){}

int BinaryTree::Find(int key)
{
    Node* node = FindNode(key);
    return (node ? node->data : 0);
}

void BinaryTree::Add(int key, int data)
{
    if (head)
        AddNote(key, data);
    else
        CreateHead(key, data);
}

bool BinaryTree::Delete(int key)
{
    Node* nodeToDelete = FindNode(key);
    bool result = nodeToDelete;


    if (nodeToDelete)
    {
        if (nodeToDelete->parent)
        {
            if (nodeToDelete->key > nodeToDelete->parent->key)
                nodeToDelete->parent->childRight = nullptr;
            else
                nodeToDelete->parent->childLeft = nullptr;

            DeleteNode(nodeToDelete);

        }
        else
        {
            DeleteNode(nodeToDelete);
            nodeToDelete = nullptr;
        }
    }
    
    return result;
}

bool BinaryTree::DeleteItem(int key)
{
    Node* nodeToDelete = FindNode(key);
    bool result = nodeToDelete;


    if (result)
    {
        Node* childs = nodeToDelete->childRight;
        if (childs)
        {
            while (childs->childLeft)
            {
                childs = childs->childLeft;
            }
            childs->childLeft = nodeToDelete->childLeft;
        }
        
        if (nodeToDelete->parent)
        {
            if (nodeToDelete->key > nodeToDelete->parent->key)
                nodeToDelete->parent->childRight = nodeToDelete->childRight;
            else
                nodeToDelete->parent->childLeft = nodeToDelete->childRight;
        }
        else
        {
            nodeToDelete->childRight->parent = nullptr;
            head = nodeToDelete->childRight;
        }

        delete nodeToDelete;
    }

    return result;
}


/*******************************************************************PRIVATE******************************************************************/

BinaryTree::Node* BinaryTree::FindNode(int key)
{
    Node* currentNode = head;

    while (currentNode && currentNode->key != key)
        currentNode = NextChild(currentNode, key);

    return currentNode;
}

void BinaryTree::CreateHead(int key, int data)
{
    head = new Node(key, data);
}

void BinaryTree::AddNote(int key, int data)
{
    Node* currentNode = head;

    while (true)
    {
        if (currentNode->key > key)
        {
            if (currentNode->childLeft == nullptr)
            {
                currentNode->childLeft = new Node(currentNode, key, data);
                break;
            }
            else
                currentNode = currentNode->childLeft;
        }
        else if (currentNode->key < key)
        {
            if (currentNode->childRight == nullptr)
            {
                currentNode->childRight = new Node(currentNode, key, data);
                break;
            }
            else
                currentNode = currentNode->childRight;
        }

        else
        {
            currentNode->data = data;
            break;
        }
    }
}

BinaryTree::Node*& BinaryTree::NextChild(Tree::Node* currentNode, int key)
{
    if (currentNode->key > key)
        return currentNode->childLeft;
    else
        return currentNode->childRight;
}

void BinaryTree::DeleteNode(Node* head)
{
    if (head->childLeft)
        DeleteNode(head->childLeft);
    if(head->childRight)
        DeleteNode(head->childRight);

    delete head; 
}
