/*4. Scrieti o functie care interschimba coloanele unei matrici cu m linii si n coloane,
astfel incat elementele din linia k sa fie în ordine crescatoare.*/
#include <iostream>
using namespace std;

void citire(int &m, int &n, int **&matrice)
{
	cin >> m >> n;
	matrice = new int*[m];
	for (int i = 0; i < m; i++)
		matrice[i] = new int[n];
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> matrice[i][j];
}

void interschimbare(int m, int **matrice, int index1, int index2)
{
	for (int i = 0; i < m; i++)
	{
		int aux = matrice[i][index1];
		matrice[i][index1] = matrice[i][index2];
		matrice[i][index2] = aux;
	}
}

void sortare_mat(int m, int **matrice, int k, int stanga, int dreapta)
{
	int index1 = stanga, index2 = dreapta, x = matrice[k][(stanga + dreapta) / 2];
	do {
		while (matrice[k][index1] < x)
			index1++;
		while (matrice[k][index2] > x)
			index2--;
		if (index1 <= index2)
		{
			interschimbare(m, matrice, index1, index2);
			index1++;
			index2--;
		}
	} while (index1 <= index2);
	if (stanga < index2)
		sortare_mat(m, matrice, k, stanga, index2);
	if (dreapta > index1)
		sortare_mat(m, matrice, k, index1, dreapta);
}

void afisare(int m, int n, int **matrice)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << matrice[i][j]<<" ";
		cout << endl;
	}
	cout << endl;
}

int main()
{
	int m, n, **matrice,k;
	citire(m, n, matrice);
	cin >> k;
	sortare_mat(m, matrice, k, 0, n - 1);
	afisare(m, n, matrice);
	for (int i = 0; i < n; i++)
		delete matrice[i];
	delete	matrice;
	system("pause");
	return 0;
}