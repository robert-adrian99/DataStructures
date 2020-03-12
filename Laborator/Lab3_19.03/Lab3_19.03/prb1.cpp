/*1. Se considera un graf orientat G = (N,A) memorat prin liste de adiacenta. 
Sa se verifice pentru orice varfuri x,y apartinand lui N daca exista drum de la x la y.
Sa se verifice daca exista lant de la x la y si in caz afirmativ sa se afiseze un astfel de lant.
Se cere utilizarea unei structuri GRAF.*/
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Graf
{
	int nrNoduri;
	vector<vector<int>> ListeAdiac;
	vector<int> lant;

	Graf()
	{
		nrNoduri = 0;
	}

	bool Drum(int x, int y)
	{
		vector<int> coada;
		int *fr = new int[nrNoduri]();
		coada.push_back(x);
		fr[x] = 1;
		while (!coada.empty())
		{
			if (coada.front() == y)
				return true;
			int index = coada.front();
			for (int index1 = 0; index1 < ListeAdiac[index].size(); index1++)
				if (fr[ListeAdiac[index][index1]] == 0)
				{
					coada.push_back(ListeAdiac[index][index1]);
					fr[ListeAdiac[index][index1]] = 1;
				}
			coada.erase(coada.begin());
		}
		return false;
	}

	bool Lant(int x,int y)
	{
		vector<int> coada;
		int *fr = new int[nrNoduri];
		for (int i = 0; i < nrNoduri; i++)
			fr[i] = -100;
		fr[x] = x;
		coada.push_back(x);
		vector<vector<int>> ListeInvers(nrNoduri);
		for (int index = 0; index < nrNoduri; index++)
			for (int index1 = 0; index1 < ListeAdiac[index].size(); index1++)
				ListeInvers[ListeAdiac[index][index1]].push_back(index);
		while (!coada.empty())
		{
			if (coada.front() == y)
			{
				int index = y;
				lant.push_back(y);
				while (index != x)
				{
					lant.push_back(fr[index]);
					index = abs(fr[index]);
				}
				return true;
			}
			int index = coada.front();
			for (int index1 = 0; index1 < ListeAdiac[index].size(); index1++)
				if (fr[ListeAdiac[index][index1]] == -100)
				{
					coada.push_back(ListeAdiac[index][index1]);
					fr[ListeAdiac[index][index1]] = index;
				}
			for (int index1 = 0; index1 < ListeInvers[index].size(); index1++)
				if (fr[ListeInvers[index][index1]] == -100)
				{
					coada.push_back(ListeInvers[index][index1]);
					fr[ListeInvers[index][index1]] = 0 - index;
				}
			coada.erase(coada.begin());
		}
		return false;
	}
};

void citire(Graf &graf)
{
	ifstream fin("C:\\Users\\ro_ad\\Desktop\\SD2\\Laborator\\Lab3_19.03\\Lab3_19.03\\graftxt.txt");
	fin >> graf.nrNoduri;
	for (int index = 0; index < graf.nrNoduri; index++)
	{
		vector<int> lista;
		int nr;
		fin >> nr;
		for (int index1 = 0; index1 < nr; index1++)
		{
			int element;
			fin >> element;
			lista.push_back(element);
		}
		graf.ListeAdiac.push_back(lista);
	}
}

void afisare(Graf graf)
{
	for (int i = 0; i < graf.nrNoduri; i++)
	{
		cout << "Nodul " << i << ": ";
		if (graf.ListeAdiac[i].empty())
			cout << "nu are arce";
		else
		for (int j = 0; j < graf.ListeAdiac[i].size(); j++)
			cout << graf.ListeAdiac[i][j] << " ";
		cout << endl;
	}
}

int main()
{
	Graf graf;
	int x, y, optiune;
	citire(graf);
	//afisare(graf);
	cout << "MENIU" << endl << "1. Verifica daca exista drum de la x la y." << endl << "2. Verifica daca exista lant de la x la y si daca exista il afiseaza." << endl << "9. Iesire." << endl;
	cout << "Alegeti o optiune: ";
	cin >> optiune;
	switch (optiune)
	{
	case 1:
		cout << "Introduceti nodurile intre care doriti sa se verifice daca exista drum: " << endl;
		cout << "x=";
		cin >> x;
		cout << "y=";
		cin >> y;
		if (graf.Drum(x, y) == true)
			cout << "Da, exista drum intre " << x << " si " << y << "!";
		else
			cout << "Nu, nu exista drum intre " << x << " si " << y << "!";
		cout << endl;
		break;
	case 2:
		cout << "Introduceti nodurile intre care doriti sa se verifice daca exista lant: " << endl;
		cout << "x=";
		cin >> x;
		cout << "y=";
		cin >> y;
		cout << endl;
		if (graf.Lant(x, y) == true)
		{
			cout << "Da, exista lant!" << endl;
			cout << "{ ";
			for (int i = graf.lant.size() - 1; i >= 1; i--)
				if (graf.lant[i] < 0)
					cout << "(" << abs(graf.lant[i - 1]) << "," << abs(graf.lant[i]) << ") ";
				else
					cout << "(" << abs(graf.lant[i]) << "," << abs(graf.lant[i - 1]) << ") ";
			cout << "}";
		}
		else
			cout << "Nu, nu exista lant intre " << x << " si " << y << "!";
		cout << endl;
		break;
	case 9:
		break;
	default:
		cout << "Introduceti o optiune valida!" << endl;
		break;
	}
	system("pause");
	return 0;
}