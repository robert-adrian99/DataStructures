/*6. Un anumit etaj al unei cladiri este reprezentat schematic sub forma unei matrice
ce contine valorile -1 si 0, unde -1 reprezinta zid si 0 reprezinta spatiu
liber. Peretii sunt de grosime 1 si usile nu sunt marcate (se considera tot perete).
a. Determinati numarul de incaperi ale etajului respectiv.
b. Determinati incaperea cu suprafata maxima.
c. Care perete poate fi daramat (o pozitie maracta cu -1 se va marca cu 0)
a.i. sa se obtina o incapere de suprafata maxima?*/
#include <iostream>
#include <fstream>
using namespace std;

struct Nod
{
	int row, col;
	Nod *next;
};

struct Coada
{
	Nod *Begin, *End;

	Coada()
	{
		Begin = NULL;
		End = NULL;
	}

	bool IsEmpty()
	{
		if (Begin == NULL)
			return true;
		return false;
	}

	void Push(int row, int col)
	{
		Nod *x = new Nod;
		x->row = row;
		x->col = col;
		x->next = NULL;
		if (Begin == NULL)
			Begin = End = x;
		else
		{
			End->next = x;
			End = x;
		}
	}

	void Pop()
	{
		if (IsEmpty())
			cout << "Coada este vida!";
		else
		{
			Nod *y = new Nod;
			y = Begin;
			Begin = Begin->next;
			delete y;
		}
	}

	int Front(int &row)
	{
		row = Begin->row;
		return Begin->col;
	}
};

void citire(int &m, int &n, int **&mat)
{
	ifstream fin("C:\\Users\\ro_ad\\Desktop\\SD2\\Laborator\\Lab2_5.03\\Lab2_5.03\\matrice.txt");
	fin >> m >> n;
	mat = new int*[m];
	for (int i = 0; i < m; i++)
		mat[i] = new int[n];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			fin >> mat[i][j];
}

int Incaperi_Maxim(int m, int n, int **mat, int &max,int *camere)
{
	int nr = 0, unitati = 0;
	max = 0;
	Coada Camera;
	for (int i = 1; i < m - 1; i++)
	{
		for (int j = 1; j < n - 1; j++)
		{
			if (mat[i][j] == 0)
			{
				unitati = 0;
				Camera.Push(i, j);
				nr++;
				mat[i][j] = nr;
				unitati++;
				while (!Camera.IsEmpty())
				{
					int index1 = 0, index2;
					index2 = Camera.Front(index1);
					Camera.Pop();
					if (mat[index1][index2 - 1] == 0)
					{
						mat[index1][index2 - 1] = nr;
						Camera.Push(index1, index2 - 1);
						unitati++;
					}
					if (mat[index1][index2 + 1] == 0)
					{
						mat[index1][index2 + 1] = nr;
						Camera.Push(index1, index2 + 1);
						unitati++;
					}
					if (mat[index1 - 1][index2] == 0)
					{
						mat[index1 - 1][index2] = nr;
						Camera.Push(index1 - 1, index2);
						unitati++;
					}
					if (mat[index1 + 1][index2] == 0)
					{
						mat[index1 + 1][index2] = nr;
						Camera.Push(index1 + 1, index2);
						unitati++;
					}
				}
				camere[nr-1] = unitati;
				if (unitati > max)
					max = unitati;
			}
		}
	}
	return nr;
}

int Zid(int **mat, int m, int n, int *camere, int &index2)
{
	int max = 0, index1;
	for (int i = 1; i < m - 1; i++)
		for (int j = 2; j < n - 1; j++)
		{
			int s = 0, index;
			if (mat[i][j] == -1)
			{
				if (mat[i + 1][j] != -1)
					s += camere[mat[i + 1][j]];
				if (mat[i - 1][j] != -1 && mat[i - 1][j] != mat[i + 1][j])
					s += camere[mat[i - 1][j] - 1];
				if (mat[i][j + 1] != -1 && mat[i][j + 1] != mat[i + 1][j] && mat[i][j + 1] != mat[i - 1][j])
					s += camere[mat[i][j + 1] - 1];
				if (mat[i][j - 1] != -1 && mat[i][j - 1] != mat[i + 1][j] && mat[i][j - 1] != mat[i - 1][j] && mat[i][j - 1] != mat[i][j + 1])
					s += camere[mat[i][j - 1] - 1];
			}
			if (s >= max)
			{
				max = s;
				index1 = i;
				index2 = j;
			}
		}
	return index1;
}

int main()
{
	int **matrice, m, n, max = 0, *camere;
	citire(m, n, matrice);
	camere = new int[(n*m) / 2];
	cout << "Numarul de incaperi este " << Incaperi_Maxim(m, n, matrice, max, camere) << "." << endl;
	cout << "Cea mai mare camera este de " << max << " unitati." << endl;
	camere[0] = 0;
	int index1, index2;
	index1 = Zid(matrice, m, n, camere, index2);
	cout << "Zidul care trebuie daramat este (" << ++index1 << "," << ++index2 << ")." << endl;
	system("pause");
	return 0;
}