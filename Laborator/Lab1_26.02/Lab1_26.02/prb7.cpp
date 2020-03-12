/*7. Tipariti sumele elementelor aflate pe patratele concentrice ale unei matrice patratice.*/
#include <iostream>
using namespace std;

void citire(int &n, int **&matrice)
{
	cin >> n;
	matrice = new int*[n];
	for (int i = 0; i < n; i++)
		matrice[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> matrice[i][j];
}

void sume_patrate_conc(int n, int **matrice)
{
	for (int i = 0; i < (n % 2 == 1 ? (n / 2) + 1 : n / 2); i++)
	{
		int s = 0;
		for (int j = i; j < n - i; j++)
			s += matrice[i][j];
		for (int j = i + 1; j < n - i; j++)
			s += matrice[j][n - i - 1];
		for (int j = n - i - 2; j > i; j--)
			s += matrice[n - i - 1][j];
		for (int j = n - i - 1; j > i; j--)
			s += matrice[j][i];
		cout << endl << "Suma patratului " << i + 1 << " este " << s;
	}
	cout << endl;
}

int main()
{
	int n, **matrice;
	citire(n, matrice);
	sume_patrate_conc(n, matrice);
	for (int i = 0; i < n; i++)
		delete matrice[i];
	delete	matrice;
	system("pause");
	return 0;
}