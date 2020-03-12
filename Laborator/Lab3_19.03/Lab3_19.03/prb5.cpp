/*5. Se citeste dintr-un fisier un arbore binar. Sa se determine inaltimea acestuia
(=lungimea celui mai lung drum de la radacina la o frunza). Se cere utilizarea
unei structuri NOD pentru nodurile arborelui, care sa aiba 3 campuri: INFO
- informatie, STANGA - pointer la NOD, DREAPTA - pointer la NOD.*/
#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
using namespace std;

struct Nod
{
	int info;
	Nod *stanga, *dreapta;
	
	Nod()
	{
		stanga = NULL;
		dreapta = NULL;
	}
};

struct Arbore
{
	Nod *rad;

	Arbore()
	{
		rad = NULL;
	}

	int Inaltime()
	{
		int hmax = -1;
		int nr1 = 0, nr2 = 0;
		queue<Nod*> q;
		q.push(rad);
		nr1++;
		while (!q.empty())
		{
			Nod *x = new Nod;
			x = q.front();
			if (x->stanga != NULL)
			{
				q.push(x->stanga);
				nr2++;
			}
			if (x->dreapta != NULL)
			{
				q.push(x->dreapta);
				nr2++;
			}
			q.pop();
			nr1--;
			if (nr1 == 0)
			{
				hmax++;
				nr1 = nr2;
				nr2 = 0;
			}
		}
		return hmax;
	}
};

void citire(Arbore &ARB)
{
	ifstream fin("C:\\Users\\ro_ad\\Desktop\\SD2\\Laborator\\Lab3_19.03\\Lab3_19.03\\ArboreBinar.txt");
	stack<Nod*> s;
	int elem;
	while (fin >> elem)
	{
		if (s.empty())
		{
			Nod* x = new Nod;
			x->info = elem;
			ARB.rad = x;
			s.push(x);
		}
		else
			if (elem != -1 && s.top()->info != -1 && s.top()->stanga == NULL)
			{
				Nod *x = new Nod;
				x->info = elem;
				s.top()->stanga = x;
				s.push(x);
			}
			else
				if (elem != -1 && s.top()->info != -1 && s.top()->stanga != NULL)
				{
					Nod *x = new Nod;
					x->info = elem;
					s.top()->dreapta = x;
					s.push(x);
				}
				else
					if (elem == -1 && s.top()->info != -1 && s.top()->stanga == NULL)
					{
						Nod *x = new Nod;
						x->info = elem;
						s.push(x);
					}
					else
						if (elem == -1 && s.top()->info != -1 && s.top()->stanga != NULL)
							s.pop();
						else
							if (elem != -1 && s.top()->info == -1)
							{
								s.pop();
								Nod *x = new Nod;
								x->info = elem;
								s.top()->dreapta = x;
								s.pop();
								s.push(x);
							}
							else
								if (elem == -1 && s.top()->info == -1)
								{
									s.pop();
									s.pop();
								}
	}
}

int main()
{
	Arbore ARB;
	citire(ARB);
	cout << ARB.Inaltime() << endl;
	system("pause");
	return 0;
}