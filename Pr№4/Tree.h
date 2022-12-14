#pragma once

#include <iostream>
#include <string.h>

using namespace std;

class Tree
{
	struct Node
	{
		Node* parent;
		Node* leftChild;
		Node* rightChild;

		char data;

		Node(char data, Node* parent = nullptr, Node* leftChild = nullptr, Node* rightChild = nullptr)
		{
			this->data = data;

			this->parent = parent;
			this->leftChild = leftChild;
			this->rightChild = rightChild;
		}
	};

	public:
		Tree(char*);
		~Tree();

		void Print();
		void Rotate();

		char getLeft();
		int Find(char);
		int FindMax();

	private:
		Node* root;
		int treeSize;
		int treeLevels;

		Node* GenerationTree(Node*, int, int, char*);

		void PrintTree(Node*, int);

		char LeftChild(Node*);
		int FindNumOfNodeTo(Node*, char, int counter = 0);
		int FindMaxEl(Node*);

		void DeleteTree(Node*);
};

