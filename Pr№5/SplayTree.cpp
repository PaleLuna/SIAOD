#include "SplayTree.h"

/*******************************************************************PUBLIC********************************************************************/

SplayTree::SplayTree(){}

void SplayTree::Add(int key, int data)
{
	if (head)
		AddNote(key, data);
	else
		CreateHead(key, data);
}

int SplayTree::Find(int key)
{
    FindNode(key);
	return head->data;
}

bool SplayTree::Delete(int key)
{
    return false;
}

bool SplayTree::DeleteItem(int key)
{
    FindNode(key);
    if (head->key == key)
    {
        Node* nodeTodelete = head;

        if (!head->childLeft) // Случай, когда левого ребенка не существует
        {
            Node* tempHead = head->childLeft;
            
            head->childRight = nullptr;
            delete head;

            head = tempHead;
        }
        else if (!head->childLeft->childRight) // Случай, когда правого внука не существует
        {
            Node* child = head->childLeft;
            child->childRight = head->childRight;

            head->childRight->parent = child;
            child->parent = nullptr;

            head->childLeft = nullptr;
            head->childRight = nullptr;
            delete head;
            head = child;
        }
        else // В остальном случае...
        {
            Node* tempParent = head->childLeft;
            tempParent->parent = nullptr;

            while (tempParent->childRight)
                tempParent = tempParent->childRight;

            tempParent = Splay(tempParent);
            
            tempParent->childRight = head->childRight;
            head->childRight->parent = tempParent;

            head->childRight = nullptr;
            head->childLeft = nullptr;

            delete head;

            head = tempParent;
        }
        return true;
    }
    return false;
}

/*******************************************************************PRIVATE******************************************************************/

void SplayTree::CreateHead(int key, int data)
{
	head = new Node(key, data);
}
void SplayTree::AddNote(int key, int data)
{
    Node* currentNode = head;

    while (true)
    {
        if (currentNode->key > key)
        {
            if (currentNode->childLeft == nullptr)
            {
                currentNode->childLeft = new Node(currentNode, key, data);
                head = Splay(currentNode->childLeft);
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
                head = Splay(currentNode->childRight);
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

SplayTree::Node* SplayTree::FindNode(int key)
{
    Node* currentNode = head;
    Node* previousNode = nullptr;
    bool result;

    while (currentNode && currentNode->key != key)
    {
        if (currentNode)
            previousNode = currentNode;
        currentNode = NextChild(currentNode, key);
    }

    result = currentNode;

    if (result)
        head = Splay(currentNode);
    else
        head = Splay(previousNode);

    return head;
}

SplayTree::Node*& SplayTree::NextChild(Tree::Node* currentNode, int key)
{
    if (currentNode->key > key)
        return currentNode->childLeft;
    else
        return currentNode->childRight;
}

SplayTree::Node* SplayTree::LeftRotate(Node* node)
{
    Node* tempNode = node->childRight;
    node->childRight = tempNode->childLeft;

    if(tempNode->childLeft)
        tempNode->childLeft->parent = node;
    
    tempNode->childLeft = node;

    SwapParents(node, tempNode);
    return tempNode;
}

SplayTree::Node* SplayTree::RightRotate(Node* node)
{
    Node* tempNode = node->childLeft;
    node->childLeft = tempNode->childRight;

    if(tempNode->childRight)
        tempNode->childRight->parent = node;
    
    tempNode->childRight = node;

    SwapParents(node, tempNode);
    return tempNode;
}

SplayTree::Node* SplayTree::Splay(Node* root)
{
    if (!root->parent)
        return root;

    Node* parent = root->parent;
    Node* grandparent = parent->parent;

    if (!grandparent) //Повороты относительно главного корня
    {
        if (parent->childLeft == root)
            RightRotate(parent);
        else
            LeftRotate(parent);

        return root;
    }
    else
    {
        if (grandparent->childLeft == parent && parent->childLeft == root) // Zig-Zig
        {
            RightRotate(grandparent);
            RightRotate(parent);
        }
        else if (grandparent->childRight == parent && parent->childRight == root) // Zag-Zag
        {
            LeftRotate(grandparent);
            LeftRotate(parent);
        }
        else if (grandparent->childLeft == parent && parent->childRight == root) // Zig-Zag
        {
            LeftRotate(parent);
            RightRotate(grandparent);
        }
        else if (grandparent->childRight == parent && parent->childLeft == root) // Zag-Zig
        {
            RightRotate(parent);
            LeftRotate(grandparent);
        }
    }
    return Splay(root); //Рекурсивное поднятие нода в корень
}

void SplayTree::SwapParents(Node* parent, Node* child)
{
    Node* grandParent = parent->parent;

    if (grandParent)
    {
        if (grandParent->childLeft == parent)
            grandParent->childLeft = child;
        else
            grandParent->childRight = child;
    }
   
    parent->parent = child;
    child->parent = grandParent;

}

void SplayTree::DeleteNode(Node* head)
{
}
