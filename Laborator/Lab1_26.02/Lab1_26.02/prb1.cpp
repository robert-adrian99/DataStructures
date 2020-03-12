/*Se considera  un vector de numere v cu n elemente. Sa  se determine care este
elementul minim si de câte ori apare în sir, printr-o singur  parcurgere a sirului
(în afara  de citire).*/
#include <iostream>

void citire(int *&vector, int &n)
{
	std::cin >> n;
	vector = new int[n];
	for (int index = 0; index < n; index++)
		std::cin >> vector[index];
}

int gasire_minim(int *vector, int n, int &nr_ori)
{
	int minim = vector[0];
	nr_ori = 1;
	for (int index = 1; index < n; index++)
		if (vector[index] == minim)
			nr_ori++;
		else
			if (vector[index] < minim)
			{
				minim = vector[index];
				nr_ori = 1;
			}
	return minim;
}

int main()
{
	int *vector, n, nr = 0;
	citire(vector, n);
	std::cout << "Elementul minim este " << gasire_minim(vector, n, nr);
	std::cout << " si apare de " << nr << " ori";
	delete vector;
	system("pause");
	return 0;
}