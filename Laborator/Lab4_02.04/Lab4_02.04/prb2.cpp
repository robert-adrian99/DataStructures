/*2. Implementarea unui heap d-ar cu aceleasi operatii ca pentru heap-ul binar.
Un heap d-ar este un arbore d-ar cu proprietatile de heap cunoscute.*/
#include <iostream>
#include <vector>
using namespace std;

class D_aryHeap
{
private:
	int Size, D;
	vector<int> Data;
public:
	D_aryHeap(int d=2)
	{
		Size = 0;
		D = d;
	}
	void GiveVector(vector<int> heap)
	{
		Data = heap;
	}
	int GetSize()
	{
		return Size;
	}
	void Max_Heap(int index)
	{
		int index_max = index;
		for (int son = 2 * index + 1; son <= 2 * index + D; son++)
		{
			if (son<Size&&Data[son]>Data[index_max])
				index_max = son;
		}
		if (index_max != index)
		{
			swap(Data[index_max], Data[index]);
			Max_Heap(index_max);
		}
	}
	void Construct_Heap()
	{
		for (int index = Size / D - 1; index > 0; index--)
			Max_Heap(index);
	}
	int Max_Element()
	{
		return Data[0];
	}
	int Extract_Max()
	{
		int max;
		if (Size < 1)
			return -1;
		else
		{
			max = Data[0];
			Data[0] = Data[Size - 1];
			Data.pop_back();
			Size = Size - 1;
			Max_Heap(0);
		}
		return max;
	}
	bool Increase_Key(int index, int value)
	{
		if (value < Data[index])
			return false;
		Data[index] = value;
		int parent = (index - 1) / D;
		while (index > 0 && Data[parent] < value)
		{
			Data[index] = Data[parent];
			index = parent;
			parent = (index - 1) / D;
		}
		Data[index] = value;
		return true;
	}
	bool Insert(int value)
	{
		Data.push_back(0);
		Size++;
		if (Increase_Key(Size - 1, value) == false)
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
	D_aryHeap Heap;
	cout << "MENU" << endl << "The oprions are:" << endl;
	cout << "1. Insert a value in Heap." << endl;
	cout << "2. Extract the maximum value from Heap(this operation will get the maximum value and then it will be deleted)." << endl;
	cout << "3. Get the maximum value from Heap(but without delete it)." << endl;
	cout << "4. Print all the values from Heap(this operation will delete the values from heap because it will use the Extract method)." << endl;
	cout << "5. Construct a D-ary Heap based on a vector read from keyboard." << endl;
	cout << "9. Exit." << endl << "WARNING! The program will stop only when you enter the Exit option!" << endl;
	int option;
	int size = Heap.GetSize();
	bool ok = true;
	if (size == 0)
	{
		cout << "The Heap is empty! Please insert some values using option 1 or 5!";
		ok = false;
	}
	cout << "Enter your choise: ";
	cin >> option;
	while(ok == false)
	{
		cout << "Please enter an option for insert values such as 1 or 5!";
		cin >> option;
		if (option == 1 || option == 5)
		{
			ok = true;
			break;
		}
	}
	while(option != 9)
	{
		size = Heap.GetSize();
		if (size == 0)
			cout << "The Heap is empty! Please insert some values!";
		switch (option)
		{
		case 1:
		{
			cout << "Enter the value you want to insert in Heap: ";
			int value;
			cin >> value;
			if (Heap.Insert(value) == true)
				cout << "The value was inserted." << endl;
			else
				cout << "The value is too little" << endl;
			break;
		}
		case 2:
		{
			if (size == 0)
				cout << "The Heap is empty!" << endl;
			else
				cout << "The maximum value from Heap is " << Heap.Extract_Max() << " and it was deleted!" << endl;
			break;
		}
		case 3:
		{
			if (size == 0)
				cout << "The Heap is empty!" << endl;
			else
				cout << "The maximum value from Heap is " << Heap.Max_Element() << " and it wasn't deleted" << endl;
			break;
		}
		case 4:
		{
			if (size == 0)
				cout << "The Heap is empty!" << endl;
			else
			{
				for (int index = 0; index < size; index++)
					cout << Heap.Extract_Max() << " ";
				cout << endl;
			}
			break;
		}
		case 5:
		{
			cout << "Set the D for the D-ary Heap: ";
			int D;
			cin >> D;
			cout << "Set the size of the vector: ";
			cin >> size;
			cout << "Give the vector to be transformed in D-ary Heap: ";
			vector<int> vector_heap;
			for (int index = 0; index < size; index++)
			{
				int x;
				cin >> x;
				vector_heap.push_back(x);
			}
			Heap.GiveVector(vector_heap);
			break;
		}
		case 9:
			break;
		default:
			cout << "Enter a valid option!" << endl;
			break;
		}
		cout << "Enter your choise: ";
		cin >> option;
	}
	system("pause");
	return 0;
}