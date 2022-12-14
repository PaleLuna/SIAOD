#pragma once

#include "DirectionOfStudy.h"
#include "BinaryFile.h"


class HashTable
{
	struct TableCell
	{
		int key;
		DirectionOfStudy data;
		bool isFree;

		TableCell() {
			key = 0;
			isFree = true; 
		}
		TableCell(const TableCell& otherObj) {
			operator=(otherObj);
		}

		void Add(int key, DirectionOfStudy* data)
		{
			this->key = key;
			this->data = *data;
			isFree = false;
		}

		void Delete()
		{
			isFree = true;
		}

		void operator=(const TableCell& otherObj)
		{
			this->key = otherObj.key;
			this->data = otherObj.data;
			this->isFree = otherObj.isFree;
		}
	};

	public:
		HashTable(int capacity);
		~HashTable();

		bool push(int key, DirectionOfStudy* directionOfStudy);
		DirectionOfStudy* get(int key);

		int* getKeys(int& size);

		void PrintTable();

		bool deleteAtKey(int key);


	private:
		TableCell* table;
		int capacity;
		int size;
		int realSize;
		
		int Find(int key);

		void ReHash();
		int Hash(int key);
		int MainHashFunc(int key);
		int AdditionalHashFunc(int key);
};

