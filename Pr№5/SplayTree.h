#pragma once
#include "Tree.h"
class SplayTree : public Tree
{
public:
	SplayTree();

	int Find(int key) override;
	void Add(int key, int data) override;

	bool Delete(int key) override;
	bool DeleteItem(int key) override;


private:
	void CreateHead(int key, int data) override;
	void AddNote(int key, int data) override;

	Node* FindNode(int key) override;
	Node*& NextChild(Tree::Node* currentNode, int key);

	Node* LeftRotate(Node* node);
	Node* RightRotate(Node* node);

	Node* Splay(Node* root);

	void SwapParents(Node* firstNode, Node* secondNode);
	
	void DeleteNode(Node* head) override;
};

