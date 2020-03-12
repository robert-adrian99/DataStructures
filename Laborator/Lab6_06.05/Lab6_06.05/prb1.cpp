// TEMA 6 || PROBLEMA 1
#include <iostream>
#include <vector>
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
	Nod(pair<KeyType, ValueType> info)
	{
		information = info;
	}
};

template<class KeyType,class ValueType>
class HashTable
{
private:
	vector<Nod<KeyType, ValueType>*> table;
	KeyType hash(KeyType)
	{

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
	}
};

template<class KeyType,class ValueType>
class Iterator
{
private:
	Nod<KeyType, ValueType>* it;
public:
	Iterator()
	{
	}
	Iterator(Nod<KeyType, ValueType>* x)
	{
		it = x;
	}
	Iterator& operator++()
	{
		if (it->next != NULL)
			it = it->next;
		//else
			//it
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

	system("pause");
	return 0;
}