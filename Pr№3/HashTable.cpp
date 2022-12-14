#include "HashTable.h"

HashTable::HashTable(int capacity)
{
	this->capacity = capacity;
	this->size = 0;
	this->realSize = 0;

	this->table = new TableCell[this->capacity];
}

HashTable::~HashTable()
{
	delete[] table;
}

bool HashTable::push(int key, DirectionOfStudy* directionOfStudy)
{
	bool isPushed = false;
	int index;
	if (size < capacity)
	{
		index = Hash(key);
		isPushed = index > -1;
	}

	if (isPushed)
	{
		table[index].Add(key, directionOfStudy);
		realSize++;
		size++;
	}
	return isPushed;
}

DirectionOfStudy* HashTable::get(int key)
{
	DirectionOfStudy* result = nullptr;
	int index = Find(key);

	if (index > -1)
		result = new DirectionOfStudy(table[index].data);

	return result;
}

int* HashTable::getKeys(int& size)
{
	int* keys = new int[this->size];
	int counter = 0;

	for (int i = 0; (i < capacity) && counter < this->size; i++)
		if (!table[i].isFree)
		{
			keys[counter++] = table[i].key;
		}

	size = this->size;
	return keys;
}

void HashTable::PrintTable()
{
	for (int i = 0; i < capacity; i++)
		if (!table[i].isFree)
			printf("Key%i: %s\n", i, table[i].data.getDirectionCode().c_str());
}

bool HashTable::deleteAtKey(int key)
{
	bool isDelete = false;
	int index = Find(key);

	if (index > -1)
	{
		table[index].Delete();
		size--;

		if (((float)realSize / capacity) > 0.55F)
			ReHash();

		isDelete = true;
	}

	return isDelete;
}

int HashTable::Find(int key)
{
	int firstHashKey = MainHashFunc(key);
	int secondHashKey = AdditionalHashFunc(key);

	int index = -1;

	for (int i = 0; i < capacity; ++i)
	{
		index = (firstHashKey + i * secondHashKey) % capacity;
		if (!table[index].isFree && (table[index].key == key))
			break;
		index = -1;
	}

	return index;
}

void HashTable::ReHash()
{
	TableCell* tempTable = new TableCell[capacity];

	for (int i = 0; i < capacity; i++)
		if (!table[i].isFree)
			tempTable[i] = table[i];

	delete[] table;

	table = tempTable;
}

int HashTable::Hash(int key)
{
	int firstHashKey = MainHashFunc(key);
	int secondHashKey = AdditionalHashFunc(key);

	int index = -1;

	for (int i = 0; i < capacity; ++i)
	{
		index = (firstHashKey + i * secondHashKey) % capacity;
		if (table[index].isFree)
			break;
		index = -1;
	}

	return index;
}

int HashTable::MainHashFunc(int key)
{
	double mltp = 0.6180339887F;
	return (int)(capacity * fmod(key * mltp, 1));
}
int HashTable::AdditionalHashFunc(int key)
{
	return (key % (capacity - 1)) + 1;
}
