/*2. Se considera vectorul de numere v cu n elemente numere naturale mai mici decat 100. Sa se
determine ce numar apare cel mai des si de câte ori.*/
#include <iostream>

void citire(int &n, int *&vector)
{
	std::cin >> n;
	vector = new int[n];
	for (int index = 0; index < n; index++)
		std::cin >> vector[index];
}

int gasire_nr(int n, int *vector, int &nr_ori)
{
	int frecventa[100] = { 0 };
	for (int index = 0; index < n; index++)
		frecventa[vector[index]]++;
	nr_ori = frecventa[0];
	int nr = 0;
	for (int index = 1; index < n; index++)
		if (nr_ori < frecventa[index])
		{
			nr = index;
			nr_ori = frecventa[index];
		}
	return nr;
}

int main()
{
	int *vector, n, nr = 0;
	citire(n, vector);
	std::cout << "Elementul care apare cel mai des este " << gasire_nr(n, vector, nr);
	std::cout << " si apare de " << nr << " ori.";
	delete vector;
	system("pause");
	return 0;
}