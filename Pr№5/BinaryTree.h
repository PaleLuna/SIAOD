#pragma once

#include "Tree.h"

using namespace std;

class BinaryTree : public Tree
{
	public: 
		BinaryTree();

		int Find(int key) override;
		void Add(int key, int data) override;

		bool Delete(int key) override;
		bool DeleteItem(int key) override;


	private:

		Node* FindNode(int key) override;

		void CreateHead(int key, int data) override;

		void AddNote(int key, int data) override;

		Node*& NextChild(Tree::Node* currentNode, int key);

		void DeleteNode(Node* head) override;

};

