/*3. Se citeste un text dintr-un fisier. Sa se construiasca arborele de codificare
Huffmann corespunzator. Sa se afiseze codul corespunzator fiecarui caracter
si sa se codifice textul. Utilizati o coada de prioritate (min).*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
struct Nod
{
	char character;
	int frequency;
	bool right;
	Nod *parent, *left_son, *right_son;
};
class PriorityQueue
{
private:
	vector<Nod*> Data;
	int Size;
public:
	PriorityQueue()
	{
		Size = 0;
	}
	int GetSize()
	{
		return Size;
	}
	void Min_Heap(int index)
	{
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int index_min = index;
		if (left < Size && Data[left]->frequency < Data[index_min]->frequency)
			index_min = left;
		if (right < Size && Data[right]->frequency < Data[index_min]->frequency)
			index_min = right;
		if (index_min != index)
		{
			swap(Data[index_min], Data[index]);
			Min_Heap(index_min);
		}
	}
	Nod *Extract_Min()
	{
		Nod *min;
		if (Size < 1)
			return NULL;
		else
		{
			min = Data[0];
			Data[0] = Data[Size - 1];
			Data.pop_back();
			Size = Size - 1;
			Min_Heap(0);
		}
		return min;
	}
	bool Decrease_Key(int index, int value)
	{
		if (value < Data[index]->frequency)
			return false;
		Data[index]->frequency = value;
		int parent = (index - 1) / 2;
		while (index > 0 && Data[parent]->frequency > value)
		{
			Data[index] = Data[parent];
			index = parent;
			parent = (index - 1) / 2;
		}
		Data[index]->frequency = value;
		return true;
	}
	bool Insert(int value,Nod *left,Nod *right)
	{
		Nod *x = new Nod;
		x->frequency = 0;
		x->left_son = left;
		x->right_son = right;
		Data.push_back(x);
		Size++;
		if (Decrease_Key(Size - 1, value) == false)
		{
			Data.pop_back();
			Size--;
			return false;
		}
		return true;
	}

};

int main()
{

	system("pause");
	return 0;
}