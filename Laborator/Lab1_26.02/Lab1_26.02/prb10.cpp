/*10. Se considera un cub de dimensiune n*n*n care contine numerele de la 1 la n*n*n dispuse în modul urmator:
- pe fiecare strat impar ordonate in spirala, incepand din coltul stanga sus, in sensul acelor de ceasornic
- pe fiecare strat par ordonate in spirala, pornind de la elementul aflat deasupra ultimului element parcurs 
pe stratul anterior si in sens invers acelor de ceasornic.
a. Daca se citeste un numar p, sa se determine pozitia in cub - adica coordonatele 
x - linia, y - coloana, z - strat, fara a construi efectiv cubul.
b. Sa se determine numarul de numere prime de pe fiecare fata laterala a cubului.*/
#include <iostream>
using namespace std;

bool verificare(int p, int n)
{
	if (p<1 || p>n*n*n)
		return false;
	return true;
}

int cautare_strat(int n,int p)
{
	for (int i = 0; i < n; i++)
		if (p <= (i + 1)*(n*n))
			return i + 1;
}



int main()
{
	int n, p;
	cin >> n >> p;
	cout << cautare_strat(n, p);
	system("pause");
	return 0;
}