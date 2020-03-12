/*2. Se considera un graf orientat G = (N,A). Sa se verifice daca este conex si fara cicluri*/
#include <iostream>
#include <fstream>
using namespace std;

struct Graf
{
	int nrNoduri;
	int **MatrAdiac;

	Graf()
	{
		nrNoduri = 0;
	}

	bool Conex_FaraCicluri()
	{
		int nrMuchii = 0;
		for (int index1 = 1; index1 < nrNoduri; index1++)
		{
			for (int index2 = 0; index2 < index1; index2++)
				if (MatrAdiac[index1][index2] == 1 || MatrAdiac[index2][index1] == 1)
					nrMuchii++;
		}
		if (nrMuchii == nrNoduri - 1)
			return true;
		else
			return false;
	}
};

void citire(Graf &graf)
{
	ifstream fin("C:\\Users\\ro_ad\\Desktop\\SD2\\Laborator\\Lab3_19.03\\Lab3_19.03\\MatriceGraf.txt");
	fin >> graf.nrNoduri;
	graf.MatrAdiac = new int*[graf.nrNoduri];
	for (int i = 0; i < graf.nrNoduri; i++)
		graf.MatrAdiac[i] = new int[graf.nrNoduri]();
	for (int index1 = 0; index1 < graf.nrNoduri; index1++)
	{
		for (int index2 = 0; index2 < graf.nrNoduri; index2++)
			fin >> graf.MatrAdiac[index1][index2];
	}
}

int main()
{
	Graf graf;
	citire(graf);
	if (graf.Conex_FaraCicluri() == true)
		cout << "Da";
	else
		cout << "Nu";
	cout << endl;
	system("pause");
	return 0;
}