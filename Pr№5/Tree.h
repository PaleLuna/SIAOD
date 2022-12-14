#pragma once

#include <iostream>

#include "Cursor.h"

using namespace std;

class Tree
{
	public:
		virtual int Find(int key) = 0;
		virtual void Add(int key, int data) = 0;

		virtual bool Delete(int key) = 0;
		virtual bool DeleteItem(int key) = 0;

		void Print();

	protected:
		struct Node
		{
			Node(int key, int data)
			{
				this->key = key;
				this->data = data;
			}
			
			Node(Node* parent, int key, int data)
			{
				this->parent = parent;
				this->key = key;
				this->data = data;
			}

			~Node()
			{
				delete childRight;
				delete childLeft;
			}

			int key;
			int data;

			Node* parent = nullptr;
			Node* childLeft = nullptr;
			Node* childRight = nullptr;
		};
		Node* head = nullptr;


		virtual Node* FindNode(int key) = 0;

		virtual void CreateHead(int key, int data) = 0;
		virtual void AddNote(int key, int data) = 0;
		virtual void DeleteNode(Node* head) = 0;


	private:
		void PrintTree(Node* root, short x, short y, short a, char c);
};

