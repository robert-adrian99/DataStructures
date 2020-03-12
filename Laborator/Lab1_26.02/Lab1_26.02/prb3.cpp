/*3. Sa se verice daca un vector este sortat si daca da, sa se specice cum este
sortat, crescator sau descrescator.*/
#include <iostream>
using namespace std;

void citire(int &n, int *&vector)
{
	cin >> n;
	vector = new int[n];
	for (int i = 0; i < n; i++)
		cin >> vector[i];
}

bool verificare(int n, int *vector, bool &cresc, bool &desc)
{
	cresc = true, desc = true;
	for (int i = 0; i < n - 1; i++)
	{
		if (vector[i] <= vector[i + 1])
		{
			desc = false;
			if (cresc == false)
				return false;
			continue;
		}
		if (vector[i] > vector[i + 1])
		{
			cresc = false;
			if (desc == false)
				return false;
		}
	}
	return true;
}

int main()
{
	int n, *vector;
	bool cresc, desc;
	citire(n, vector);
	if (verificare(n, vector, cresc, desc) == true)
		if (cresc == true)
			cout << "Sirul este ordonat crescator.";
		else
			cout << "Sirul este ordonat descrescator.";
	else
		cout << "Sirul nu este ordonat.";
	cout << endl;
	delete vector;
	system("pause");
	return 0;
}