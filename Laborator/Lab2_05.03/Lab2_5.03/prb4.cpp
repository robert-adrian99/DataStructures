/*4. Sa se implementeze algoritmul de sortare Bucket-sort utilizand liste dublu
inlantuite. Utilizati o structura LISTA_DUBLU, care sa aiba ca membrii un
pointer la NOD, reprezentand capul listei si metodele:
 INSERT_SORT - insereaza o cheie intr-o lista ordonata pe pozitia potrivita
 MERGE - uneste lista cu alta lista transmisa ca parametru
 INSERT - insereaza in capul listei
 PRINT - afisaza elementele stocate in lista
Utilizati un constructor pentru initializarea capului listei cu NULL.
Structura NOD utilizata in lista dublu inlantuita trebuie sa aiba campurile INFO, NEXT si PREV.*/
#include <iostream>
using namespace std;

struct Nod
{
	int info;
	Nod *prev, *next;
};

struct Lista_Dublu
{
	Nod* head;

	Lista_Dublu()
	{
		head = NULL;
	}

	bool IsEmpty()
	{
		if (head == NULL)
			return true;
		return false;
	}

	void Insert_Sort(int element)
	{
		Nod* x = new Nod;
		x = head;
		while (x != NULL)
		{
			if (x->info >= element)
			{
				Nod* y = new Nod;
				y->info = element;
				y->next = x->next;
				y->prev = x;
				x->next->prev = y;
				x->next = y;
				return;
			}
			x = x->next;
		}
	}

	void Insert(int element)
	{
		Nod* x = new Nod;
		x->info = element;
		head->prev = x;
		x->next = head;
		head = x;
	}

	void Delete_Head()
	{
		Nod *x = new Nod;
		x = head;
		head = head->next;
		head->prev = NULL;
		delete x;
	}

	void Merge(Lista_Dublu L,Lista_Dublu Rezultat)
	{
		while (!IsEmpty() && !L.IsEmpty())
		{
			Nod *x = new Nod;
			if (head->info < L.head->info)
			{
				Rezultat.Insert(head->info);
				Delete_Head();
			}
			else
			{
				Rezultat.Insert(L.head->info);
				L.Delete_Head();
			}
		}
		while (!IsEmpty)
		{
			Rezultat.Insert(head->info);
			Delete_Head();
		}
		while (!L.IsEmpty())
		{
			Rezultat.Insert(L.head->info);
			L.Delete_Head();
		}
	}

	void Print()
	{
		Nod* x = new Nod;
		x = head;
		while (x != NULL)
		{
			cout << x->info << " ";
			x = x->next;
		}
		delete x;
	}
};

int main()
{

	system("pause");
	return 0;
}