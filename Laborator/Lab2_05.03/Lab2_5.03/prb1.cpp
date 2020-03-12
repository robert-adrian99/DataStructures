/*1. Sa se implementeze o stiva sau o coada utilizand liste inlantuite. Creati initial
o structura NOD cu doua campuri - un camp de tip int pentru informatie si
un camp de tip pointer la NOD pentru legatura la elementul urmator. Creati
apoi o structura STIVA, care sa aiba un camp de tip pointer la NOD, care
reprezinta varful stivei. De asemenea structura STIVA trebuie sa contina
metodele PUSH, POP si TOP. PUSH adauga un element in varful stivei, POP
extrage elementul din varful stivei, iar TOP returneaza valoarea aflata in varful
stivei. Adaugati de asemenea o metoda ISEMPTY, care verifica daca stiva este
vida. De preferinta utilizati si un constructor, care sa initializeze varful stivei
cu NULL. In functia main a programului se va declara o stiva. Apoi se vor
introduce n elemente, cu n citit de la tastatura. Aceste elemente se extrag
apoi pe rand si se asaza in ordinea de extragere.*/
#include <iostream>
using namespace std;

struct NOD
{
	int info;
	NOD* next;
};

struct STIVA
{
	NOD* varf;

	STIVA()
	{
		varf = NULL;
	}

	bool IsEmpty()
	{
		if (varf == NULL)
			return true;
		return false;
	}

	void PUSH(int element)
	{
		NOD* x = new NOD;
		x->info = element;
		x->next = varf;
		varf = x;
	}

	void POP()
	{
		if (IsEmpty())
			cout << "Stiva este vida!";
		else
		{
			NOD* y = new NOD;
			y = varf;
			varf = varf->next;
			delete y;
		}
	}

	int TOP()
	{
		if (IsEmpty())
			cout << "Stiva este vida!";
		else
			return varf->info;
	}

};

int main()
{
	STIVA MyStack;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		MyStack.PUSH(i + 1);
	while (!MyStack.IsEmpty())
	{
		cout << MyStack.TOP() << endl;
		MyStack.POP();
	}
	cout << endl;
	system("pause");
	return 0;
}