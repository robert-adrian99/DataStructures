/*3. Sa se implementeze o coada circulara. Pentru aceasta se cere crearea unei
structuri COADA care sa contina un camp de tip vector de int numit DATA,
care stocheaza elementele din coada, un camp SIZE_MAX de tip int, care
reprezinta capacitatea maxima a cozii,doua campuri de tip int BEGIN si END,
care reprezinta pozitia in vectorul DATA a primului si respectiv pozitia de dupa
ultimul element din coada. De asemenea se cer in structura COADA, metodele
PUSH, POP, FRONT, ISEMPTY, unde PUSH adauga un element dupa ultimul
element din coada, POP extrage primul element din coada, FRONT
returneaza valoarea aflata la inceputul cozii si ISEMPTY verifica daca este
vida sau nu coada. In functia main se declara o variabila de tip COADA, se
insereaza pe rand n elemente, cu n citit de la tastatura, apoi se extrag aceste
elemente pe rand si se afisaza in ordinea extragerii.*/
#include <iostream>
using namespace std;

struct COADA
{
	int *Data;
	int Begin, End, SizeMax;

	COADA(int dim = 50)
	{
		Begin = NULL;
		End = NULL;
		SizeMax = dim;
		Data = new int[SizeMax];
	}

	bool IsEmpty()
	{
		if (Begin == End)
			return true;
		return false;
	}

	bool IsFull()
	{
		if ((End + 1) % SizeMax == Begin)
			return true;
		return false;
	}

	void Push(int element)
	{
		if (IsFull())
			cout << "Coada este plina!";
		else
		{
			Data[End] = element;
			End = (End + 1) % SizeMax;
		}
	}

	void Pop()
	{
		if (IsEmpty())
			cout << "Coada este vida!";
		else
			Begin = (Begin + 1) % SizeMax;
	}

	void Front()
	{
		if (IsEmpty())
			cout << "Coada este vida!";
		else
			cout << Data[Begin];
	}
};

int main()
{
	COADA MyQueue;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int x;
		cin >> x;
		MyQueue.Push(x);
	}
	for (int i = 0; i < n; i++)
	{
		MyQueue.Front();
		cout << " ";
		MyQueue.Pop();
	}
	delete[] MyQueue.Data;
	system("pause");
	return 0;
}