/*5. Sa se implementeze o lista simplu inlantuita cu functionalitatile descrise in
continuare. Se cere utilizarea unei structuri NOD care are doua campuri: un
camp int pentru informatie si un camp de tip pointer la NOD pentru legatura
catre urmatorul element. Se cere utilizarea unei structuri LISTA care are ca
membru un pointer la NOD reprezentand capul listei si metodele:
 INSERT - insereaza un element in capul listei
 SEARCH - cauta o cheie k in lista
 DELETE - sterge un element din lista
 ISEMPTY - verifica daca lista e vida
 INVERSE - inverseaza lista in compelxitate O(n), fara a folosi mai mult
	decat o zona de memorie constanta, cu exceptia celei ocupate de lista (adica fara a construi o a doua lista)
 INSERT_AFTER - insereaza o cheie k dupa un nod cu o anumita cheie m data, sau la capatul listei, daca m nu exista in lista
 INSERT_N_POZ - insereaza de n ori cheia k pe pozitia p, daca lista are cel putin p elemente, sau la sfarsitul listei altfel
 PRINT_LIST - afiseaza elementele din lista.
Utilizati un constructor pentru a initializa capul listei cu NULL.
In functia main realizati un meniu cu ajutorul unei instructiuni switch, prin
care se ofera 8 optiuni, fiecare corespunzatoare uneia dintre functiile de mai
sus, precum si o optiune de EXIT. Intr-o instructiune while, se citesc si se
executa optiuni pana la alegerea optiunii de EXIT.*/
#include <iostream>
#include <fstream>
using namespace std;

struct Nod
{
	int info;
	Nod* next;
	Nod()
	{
		next = NULL;
	}
};

struct Lista
{
	Nod* head;

	Lista()
	{
		head = NULL;
	}

	bool IsEmpty()
	{
		if (head == NULL)
			return true;
		return false;
	}

	void Insert(int element)
	{
		Nod* x = new Nod;
		x->info = element;
		x->next = head;
		head = x;
	}

	Nod* Search(int k)
	{
		if (IsEmpty())
		{
			cout << "Lista este vida!" << endl;
			return NULL;
		}
		Nod* x = new Nod;
		x = head;
		while (x != NULL && x->info != k)
			x = x->next;
		if (x == NULL)
			return NULL;
		else
			return x;
	}

	void Delete(int k)
	{
		if (IsEmpty())
		{
			cout << "Lista este vida!" << endl;
			return;
		}
		Nod* x = new Nod;
		x = Search(k);
		if (x == NULL)
		{
			cout << "Elementul nu exista in lista!" << endl;
			return;
		}
		if (x == head)
			head = head->next;
		else
		{
			Nod* y = new Nod;
			y = head;
			while (y->next != x)
				y = y->next;
			y->next = x->next;
			y = NULL;
			delete y;
		}
		delete x;
	}

	void Inverse()
	{
		if (IsEmpty())
		{
			cout << "Lista este vida!" << endl;
			return;
		}
		Nod* x = new Nod;
		Nod* y = new Nod;
		x = head->next;
		head->next = NULL;
		while (x != NULL)
		{
			y = x->next;
			x->next = head;
			head = x;
			x = y;
		}
		delete x;
		delete y;
	}

	void Insert_After(int k, int m)
	{
		Nod* x = new Nod;
		x = Search(m);
		/*if (x == NULL)
		{
			x = head;
			while (x->next != NULL)
				x = x->next;
			Nod* y = new Nod;
			y->info = k;
			y->next = NULL;
			x->next = y;
		}*/
		/* SAU*/
		if (x == NULL)
			Insert(k);
		else
		{
			Nod* y = new Nod;
			y->info = k;
			y->next = x->next;
			x->next = y;
		}
		delete x;
	}

	void Insert_N_Poz(int k, int p,int n)
	{
		Nod* x;
		x = head;
		for (; x != NULL && p > 0; p--)
			x = x->next;
		if (p > 0)
		{
			x = head;
			if (x != NULL)
			{
				while (x->next != NULL)
					x = x->next;
			}
		}
		for (int i = 0; i < n; i++)
		{
			Nod* y = new Nod;
			y->info = k;
			if (x == NULL)
			{
				head = y;
				x = head;
			}
			else
			{
				y->next = x->next;
				x->next = y;
			}
		}
	}

	void Print_List()
	{
		if (IsEmpty())
		{
			cout << "Lista este vida!" << endl;
			return;
		}
		Nod* x;
		x = head;
		while (x != NULL)
		{
			cout << x->info << " ";
			x = x->next;
		}
	}
};

void citire(Lista &L)
{
	ifstream fin("C:\\Users\\ro_ad\\Desktop\\SD2\\Laborator\\Lab2_5.03\\Lab2_5.03\\lista.txt");
	int x;
	while (fin >> x)
		L.Insert(x);
}

int main()
{
	Lista L;
	citire(L);
	cout << "Meniul de optiuni este:" << endl;
	cout << "1. Inserarea unui element in capul listei" << endl;
	cout << "2. Cautarea unui element in lista" << endl;
	cout << "3. Stergerea unui element din lista" << endl;
	cout << "4. Verificarea listei daca este vida" << endl;
	cout << "5. Inversarea listei" << endl;
	cout << "6. Inserarea unui element dupa un al doilea, sau la capatul listei daca al doilea element nu exista in lista" << endl;
	cout << "7. Inserarea unui element pe o pozitie in lista, de un numar de ori, sau la sfarsitul listei daca aceasta nu are suficiente pozitii" << endl;
	cout << "8. Afisarea elementelor listei" << endl;
	cout << "9. Iesire" << endl;
	int optiune;
	cout << "Introduceti o optiune:" << endl;
	cin >> optiune;
	while (optiune != 9)
	{
		bool ok = true;
		switch (optiune)
		{
		case 1: 
			int x;
			cout << "Introduceti elementul care doriti sa fie inserat in lista:" << endl;
			cin >> x;
			L.Insert(x);
			cout << "Elementul a fost adaugat in lista!" << endl;
			break;
		case 2: 
			cout << "Introduceti elementul pe care doriti sa il cautati in lista:" << endl;
			cin >> x; 
			if (L.Search(x))
				cout << "Elementul exista in lista!" << endl;
			else
				cout << "Elementul nu exista in lista!" << endl;
			break;
		case 3:
			cout << "Introduceti elementul care doriti sa fie sters din lista:" << endl;
			cin >> x;
			L.Delete(x);
			cout << "Elementul a fost sters!" << endl;
			break;
		case 4:
			if (L.IsEmpty())
				cout << "Lista este vida!" << endl;
			else
				cout << "Lista nu este vida!" << endl;
			break;
		case 5:
			L.Inverse();
			cout << "Lista a fost inversata!" << endl;
			break;
		case 6:
			int y;
			cout << "Introduceti elementul care doriti sa fie inserat in lista:" << endl;
			cin >> x;
			cout << "Introduceti elementul dupa care doriti sa fie introdus in lista elementul: " << x << endl;
			cin >> y;
			L.Insert_After(x, y);
			cout << "Elementul a fost inserat!" << endl;
			break;
		case 7:
			int p, n;
			cout << "Introduceti elementul care doriti sa fie inserat in lista:" << endl;
			cin >> x;
			cout << "Introduceti pozitia pe care doriti sa fie introdus in lista elementul: " << x << endl;
			cin >> p;
			cout << "Introduceti de cate ori doriti sa fie introdus in lista elementul: " << x << endl;
			cin >> n;
			L.Insert_N_Poz(x, p, n);
			cout << "Elementul a fost inserat!" << endl;
			break;
		case 8:
			cout << "Elementele listei sunt:" << endl;
			L.Print_List();
			cout << endl;
			break;
		case 9:
			break;
		default:
			ok = false;
			break;
		}
		if (ok == false)
			cout << "Introduceti doar optiuni valide!" << endl;
		if (optiune == 9)
			break;
		cout << "Introduceti o optiune:" << endl;
		cin >> optiune;
	}
	system("pause");
	return 0;
}