/*8. Sa se completeze elementele unei matrice astfel: pe prima linie elementele dintr-un
vector v. Pe fiecare dintre urmatoarele linii permutarea circulara a liniei precedente.*/
#include <iostream>
using namespace std;

void citire(int &n, int *&vector)
{
	cin >> n;
	vector = new int[n];
	for (int i = 0; i < n; i++)
		cin >> vector[i];
}

void creare_matrice(int n, int *vector, int **&matrice)
{
	matrice = new int*[n];
	for (int i = 0; i < n; i++)
		matrice[i] = new int[n];
	for (int j = 0; j < n; j++)
		matrice[0][j] = vector[j];
	for (int i = 1; i < n; i++)
	{
		int aux = matrice[i - 1][0];
		for (int j = 0; j < n - 1; j++)
			matrice[i][j] = matrice[i - 1][j + 1];
		matrice[i][n - 1] = aux;
	}
}

void afisare(int n, int **matrice)
{
	cout << endl;
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
	int n, *vector, **matrice;
	citire(n, vector);
	creare_matrice(n, vector, matrice);
	afisare(n, matrice);
	for (int i = 0; i < n; i++)
		delete matrice[i];
	delete	matrice;
	delete vector;
	system("pause");
	return 0;
}