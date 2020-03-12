/*4. Se da un arbore n-ar memorat in reprezentarea fiu-frate. Sa se parcurga in adancime si in latime. 
Se cere utilizarea unuei structuri NOD, precum si a unei structuri ARBORE.*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct Nod
{
	int info;
	Nod *fiu, *frate;
	Nod()
	{
		fiu = NULL;
		frate = NULL;
	}
};

struct Arbore
{
	Nod *rad;
	int N;

	Arbore()
	{
		rad = NULL;
	}

	vector<int> ParcurgLatime()
	{
		vector<int> v;
		queue<Nod*> q;
		q.push(rad);
		while (!q.empty())
		{
			v.push_back(q.front()->info);
			Nod *x = q.front()->fiu;
			if (x != NULL)
			{
				q.push(x);
				while (x->frate != NULL)
				{
					q.push(x->frate);
					x = x->frate;
				}
			}
			q.pop();
		}
		return v;
	}

	vector<int> ParcurgAdancime()
	{
		vector<int> v;
		stack<Nod*> sAd, sAjut;
		sAd.push(rad);
		while (!sAd.empty())
		{
			v.push_back(sAd.top()->info);
			Nod *x = sAd.top()->fiu;
			if (x != NULL)
			{
				sAjut.push(x);
				while (x->frate != NULL)
				{
					sAjut.push(x->frate);
					x = x->frate;
				}
			}
			sAd.pop();
			while (!sAjut.empty())
			{
				sAd.push(sAjut.top());
				sAjut.pop();
			}
		}
		return v;
	}
};

void citire(Arbore &ARB)
{
	ifstream fin("C:\\Users\\ro_ad\\Desktop\\SD2\\Laborator\\Lab3_19.03\\Lab3_19.03\\arboreNar.txt");
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
			if (elem != -1 && s.top()->info != -1 && s.top()->fiu == NULL)
			{
				Nod *x = new Nod;
				x->info = elem;
				s.top()->fiu = x;
				s.push(x);
			}
			else
				if (elem != -1 && s.top()->info != -1 && s.top()->fiu != NULL)
				{
					Nod *x = new Nod;
					x->info = elem;
					s.top()->frate = x;
					s.push(x);
				}
				else
					if (elem == -1 && s.top()->info != -1 && s.top()->fiu == NULL)
					{
						Nod *x = new Nod;
						x->info = elem;
						s.push(x);
					}
					else
						if (elem == -1 && s.top()->info != -1 && s.top()->fiu != NULL)
							s.pop();
						else
							if (elem != -1 && s.top()->info == -1)
							{
								s.pop();
								Nod *x = new Nod;
								x->info = elem;
								s.top()->frate = x;
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
	vector<int> v;
	v = ARB.ParcurgLatime();
	cout << "Parcurgere in Latime:" << endl;
	for (int index = 0; index < v.size(); index++)
		cout << v[index] << " ";
	cout << endl;
	cout << "Parcurgere in Adancime:" << endl;
	v = ARB.ParcurgAdancime();
	for (int index = 0; index < v.size(); index++)
		cout << v[index] << " ";
	cout << endl;
	system("pause");
	return 0;
}