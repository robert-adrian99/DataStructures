/*1. Implementati o coada de prioritati folosind o structura PRIOROTY_QUEUE,
care sa aiba un camp DATA de tip vector de intregi, care sa stocheze elementele
cozii sub forma unui heap max si un camp SIZE - nr. de elemente stocate in
coada. In plus structura trebuie sa aiba metodele:
 INSERT - insereaza un nou nod in coada
 EXTRACT_MAX - extrage elementul de prioritate maxima din coada
 MAX_ELEMENT - returneaza elementul de prioritate maxima
 INCREASE_KEY - creste prioritatea unui nod.
 MAX_HEAP (sau SIFT_DOWN) - functia care coboara o cheie pe pozitia corespunzatoare din heap.
Structura trebuie sa dispuna de constructor. In functia main se
declara o variabila de tip PRIORITY_QUEUE si se foloseste un meniu implementat
cu ajutorul unei instructiuni switch, prin care utilizatorul sa poata selecta oricare dintre 
operatiile de insertie, extragerea maximului, obtinerea maximului si afisarea elementelor din heap.*/
#include <iostream>
#include <vector>
using namespace std;
class Priority_Queue
{
private:
	vector<int> Data;
	int Size;
public:
	Priority_Queue()
	{
		Size = 0;
	}
	int GetSize()
	{
		return Size;
	}
	int Max_Element()
	{
		return Data[0];
	}
	void Max_Heap(int index)
	{
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int index_max = index;
		if (left<Size && Data[left]>Data[index_max])
			index_max = left;
		if (right<Size && Data[right]>Data[index_max])
			index_max = right;
		if (index_max != index)
		{
			swap(Data[index_max], Data[index]);
			Max_Heap(index_max);
		}
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
		int parent = (index - 1) / 2;
		while (index > 0 && Data[parent] < value)
		{
			Data[index] = Data[parent];
			index = parent;
			parent = (index - 1) / 2;
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
	Priority_Queue Heap;
	cout << "MENU" << endl << "The oprions are:" << endl;
	cout << "1. Insert a value in Heap." << endl;
	cout << "2. Extract the maximum value from Heap(this operation will get the maximum value and then it will be deleted)." << endl;
	cout << "3. Get the maximum value from Heap(but without delete it)." << endl;
	cout << "4. Print all the values from Heap(this operation will delete the values from heap because it will use the Extract method)." << endl;
	cout << "9. Exit." << endl << "WARNING! The program will stop only when you enter the Exit option!" << endl;
	int option;
	do
	{
		cout << "Enter your choise: ";
		cin >> option;
		int size = Heap.GetSize();
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
		case 9:
			break;
		default:
			cout << "Enter a valid option!" << endl;
			break;
		}
	} while (option != 9);
	system("pause");
	return 0;
}