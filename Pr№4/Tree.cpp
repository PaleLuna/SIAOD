#include "Tree.h"

//-----------------------------------------------PUBLIC----------------------------------------------------//

Tree::Tree(char* chars)
{
    const int charsSize = strlen(chars);
    treeSize = charsSize;
    treeLevels = ((charsSize % 2 == 0) ? (charsSize -1)/2 : charsSize /2);

    this->root = GenerationTree(nullptr, charsSize, 0, chars);
}
Tree::~Tree()
{
    DeleteTree(root);
}

void Tree::Print()
{
    if (this->root)
        PrintTree(this->root, 0);
}

void Tree::Rotate()
{
    
    Node* newRoot = root->rightChild;

    root->rightChild = newRoot->leftChild;
    newRoot->leftChild = root;

    root = newRoot;
}

char Tree::getLeft(){ return LeftChild(root); }
int Tree::Find(char required){ return FindNumOfNodeTo(root, required); }
int Tree::FindMax(){ return FindMaxEl(root); }

//-----------------------------------------------PRIVATE---------------------------------------------------//

Tree::Node* Tree::GenerationTree(Node* root, int numOfEl, int startPos, char* data)
{
    if (numOfEl == 0)
        return nullptr;
   
    Node* currentNode = new Node(data[startPos++], root);

    int nl = numOfEl / 2;
    int nr = numOfEl - nl - 1;

    currentNode->leftChild = GenerationTree(currentNode, nl, startPos, data);
    currentNode->rightChild = GenerationTree(currentNode, nr, nl+startPos, data);

    return currentNode;
}

void Tree::PrintTree(Node* tree, int level)
{
    if (tree->rightChild)
        PrintTree(tree->rightChild, level + 1);

    for (int i = 0; i < level; i++) cout << "    ";
    printf("|%c|\n\n", tree->data);

    if (tree->leftChild)
        PrintTree(tree->leftChild, level + 1);
}

char Tree::LeftChild(Node* tree)
{
    if (tree->leftChild)
        return LeftChild(tree->leftChild);

    return tree->data;
}
int Tree::FindNumOfNodeTo(Node* tree, char required, int counter)
{
    if (tree->data == required)
        return counter;

    int leftPath = -1;
    int rightPath = -1;

    if (tree->leftChild)
        leftPath = FindNumOfNodeTo(tree->leftChild, required, counter + 1);
    if (tree->rightChild)
        rightPath = FindNumOfNodeTo(tree->rightChild, required, counter + 1);

    if (leftPath == -1)
        return rightPath;
    else if (rightPath == -1)
        return leftPath;
    else
        return ((leftPath < rightPath) ? leftPath : rightPath);
}
int Tree::FindMaxEl(Node* tree)
{
    if (!tree->leftChild && !tree->rightChild)
        return tree->data;

    int leftChildsMax = -1;
    int rightChildsMax = -1;

    if (tree->leftChild)
        leftChildsMax = FindMaxEl(tree->leftChild);
    if (tree->rightChild)
        rightChildsMax = FindMaxEl(tree->rightChild);

    return ((leftChildsMax > rightChildsMax) ? leftChildsMax : rightChildsMax);
}

void Tree::DeleteTree(Node* tree)
{

    if (tree->leftChild)
        DeleteTree(tree->leftChild);
    if (tree->rightChild)
        DeleteTree(tree->rightChild);

    delete tree;
}