/*5. Un profesor a studiat structura relatiilor dintre elevii sai. Pentru a reprezenta
aceasta structura, profesorul a numerotat elevii de la 1 la n si a construit o
matrice patratica cu n linii astfel: a(i,j) = 1 daca elevul i il agreeaza pe elevul
j si 0 altfel. Se considera ca fiecare elev se agreeaza pe sine insusi.
a. Afisati pe ecran toate perechile distincte de elevi care se agreeaza reciproc.
b. Afisati elevii care nu agreeaza pe nimeni.
c. Afisati elevii care nu sunt agreati de nimeni.*/
#include <iostream>
using namespace std;

void citire( int &n, int **&matrice)
{
	cin >> n;
	matrice = new int*[n];
	for (int i = 0; i < n; i++)
		matrice[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			cin >> matrice[i][j];
}

void a_AgreareReciproca(int n, int **matrice)
{
	bool ok = false;
	cout << endl << "Elevii care se agreeaza reciproc sunt: " << endl;
	for (int i = 0; i < n; i++)
		for (int j = i+1; j < n; j++)
			if (matrice[i][j] == 1 && matrice[j][i] == 1)
			{
				ok = true;
				cout << "(" << i + 1 << "," << j + 1 << ")" << endl;
			}
	if (ok == false)
		cout << "Nu exista elevi care sa se agreeze reciproc.";
	cout << endl;
}

void b_NuAgreeaza(int n, int **matrice)
{
	for (int i = 0; i < n; i++)
	{
		bool ok = true;
		for (int j = 0; j < n; j++)
			if (i != j && matrice[i][j] == 1)
				ok = false;
		if (ok == true)
			cout << "Elevul " << i + 1 << " nu agreeaza pe nimeni." << endl;
	}
	cout << endl;
}

void c_NuEsteAgreat(int n, int **matrice)
{
	for (int j = 0; j < n; j++)
	{
		bool ok = true;
		for (int i = 0; i < n; i++)
			if (j != i && matrice[i][j] == 1)
				ok = false;
		if (ok == true)
			cout << "Elevul " << j + 1 << " nu este agreat de nimeni." << endl;
	}
	cout << endl;
}

int main()
{
	int m, n, **matrice;
	citire(n, matrice);
	a_AgreareReciproca(n, matrice);
	b_NuAgreeaza(n, matrice);
	c_NuEsteAgreat(n, matrice);
	for (int i = 0; i < n; i++)
		delete matrice[i];
	delete	matrice;
	system("pause");
	return 0;
}