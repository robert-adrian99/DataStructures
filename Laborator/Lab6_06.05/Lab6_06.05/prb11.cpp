// TEMA 6 || PROBLEMA 1
#include <iostream>
#include <array>
#include <random>
using namespace std;

template<class KeyType,class ValueType>
struct Pair
{
	KeyType key;
	ValueType value;
};

template<class KeyType,class ValueType>
struct Nod
{
	Pair<KeyType, ValueType> information;
	Nod<KeyType, ValueType> *next, *prev;
	Nod()
	{
		next = NULL;
		prev = NULL;
	}
	Nod(KeyType key, ValueType value)
	{
		information.key = key;
		information.value = value;
	}
};

template<class KeyType,class ValueType>
class HashTable
{
private:
	array<Nod<KeyType, ValueType>*> table;
	KeyType hash(KeyType k)
	{
		return k % 11;
	}
	unsigned int djb_hash(char* key)
	{
		unsigned int len = strlen(key);
		unsigned int h = 2166136261;
		for (int i = 0; i < len; i++)
			h = (h * 16777619) ^ key[i];
		return h;
	}
	unsigned int add_hash(char* key)
	{
		unsigned int len = strlen(key);
		unsigned int h = 0;
		for (int i = 0; i < len; i++)
		{
			h += key[i];
		}
		return h;
	}
public:
	friend class Iterator<KeyType, ValueType>;
	HashTable()
	{
	}
	HashTable(int n)
	{
		table(n);
	}
	void Insert(Nod<KeyType, ValueType>* x)
	{
		table[hash(x->information.key)]->prev = x;
		x->next = table[hash(x->information.key)];
		table[hash(x->information.key)] = x;
	}
	Nod<KeyType, ValueType>* Search(KeyType key)
	{
		Nod<KeyType, ValueType>* x = table[hash(key)];
		while (x != NULL)
		{
			if (x->information.key == key)
				return x;
			x = x->next;
		}
		return NULL;
	}
	bool Delete(KeyType key)
	{
		Nod<KeyType, ValueType>* x = Search(key);
		if (x == NULL)
			return false;
		x->prev->next = x->next;
		x->next->prev = x->prev;
		delete x;
		return true;
	}
	ValueType operator[](KeyType key)
	{
		Nod<KeyType, ValueType>* x = Search(key);
		if (x != NULL)
			return x->information.value;
		return 0;
	}
	Iterator Begin(int index)
	{
		return table[index];
	}
	Iterator End(index)
	{
		Nod<KeyType, ValueType>* x = table[index];
		while (x->next != NULL)
			x = x->next;
		return x;
	}
};

template<class KeyType,class ValueType>
class Iterator
{
private:
	Nod<KeyType, ValueType>* it;
	int index;
public:
	Iterator(int i)
	{
		index = i;
	}
	Iterator(Nod<KeyType, ValueType>* x,int i)
	{
		it = x;
		index = i;
	}
	Iterator& operator++()
	{
		if (it->next != NULL)
			it = it->next;
	}
	Iterator& operator--()
	{
		if (it->prev != NULL)
			it = it->prev;
	}
	bool operator==(Iterator i)
	{
		if (it != i.it)
			return true;
		else
			return false;
	}
	bool operator!=(Iterator i)
	{
		if (it != i.it)
			return true;
		else
			return false;
	}
};

int main()
{
	int n;
	cout << "Enter the number of elements(>100) that you want to be inserted in the Hash Table.";
	cin >> n;
	while (n < 100)
	{
		cout << "Enter a number greater than 100!";
		cin >> n;
	}
	srand((int)time(0));
	HashTable<int, int> table(n);
	int m = n;
	while (n > 0)
	{
		int key = (rand() + 100) + 1;
		int value = (rand() + 100) + 1;
		Nod<int, int>* x(key, value);
		table.Insert(x);
		n--;
	}
	for (int index = 0; index < m; index++)
	{
		Nod<int, int>* x = table[index];
		while (table[index] != NULL)
		{
			cout << x.information.key << ":" << x.information.key;
			x = x->next;
		}
	}
	for (int index = 0; index < m; index++)
	{

	}
	system("pause");
	return 0;
}