/*6. Sa se scrie intr-o matrice patratica numerele de la 1 la n*n in spirala: 
- pentru n impar incepand din centru;
- pentru n par incepand din coltul stanga - sus.*/
#include <iostream>
using namespace std;

void creare(int n, int **&matrice)
{
	matrice = new int*[n];
	for (int i = 0; i < n; i++)
		matrice[i] = new int[n];
	int x, add;
	if (n % 2 == 1)
	{
		x = n * n;
		add = -1;
	}
	else
	{
		x = 1;
		add = 1;
	}
	for (int i = 0; i < (n % 2 == 1 ? (n / 2) + 1 : n / 2); i++)
	{
		for (int j = i; j < n - i; j++)
		{
			matrice[i][j] = x;
			x += add;
		}
		for (int j = i + 1; j < n - i; j++)
		{
			matrice[j][n - i - 1] = x;
			x += add;
		}
		for (int j = n - i - 2; j > i; j--)
		{
			matrice[n - i - 1][j] = x;
			x += add;
		}
		for (int j = n - i - 1; j > i; j--)
		{
			matrice[j][i] = x;
			x += add;
		}
	}
}

void afisare(int n, int **matrice)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << matrice[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

int main()
{
	int n, **matrice;
	cin >> n;
	creare(n, matrice);
	afisare(n, matrice);
	for (int i = 0; i < n; i++)
		delete matrice[i];
	delete	matrice;
	system("pause");
	return 0;
}