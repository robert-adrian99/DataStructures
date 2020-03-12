/*6. Sa se refaca un arbore binar cunoscandu-se parcurgerile sale in preordine si inordine.
Se cere utilizarea unei structuri NOD pentru nodurile arborelui, care sa aiba 3 campuri:
INFO - informatie, STANGA - pointer la NOD, DREAPTA - pointer la NOD.*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Nod
{
	int info;
	Nod *stanga, *dreapta;
};

struct Arbore
{
	Nod *rad;

	void RefacereArbore(vector<int> Preordine,vector<int> Inordine)
	{

	}
};

vector<int> citire(vector<int> &inordine)
{
	ifstream fin("C:\\Users\\ro_ad\\Desktop\\SD2\\Laborator\\Lab3_19.03\\Lab3_19.03\\ArborePreIn.txt");
	vector<int> preordine;
	int x;
	fin >> x;
	while (x != -1)
	{
		preordine.push_back(x);
		fin >> x;
	}
	while (fin >> x)
		inordine.push_back(x);
	return preordine;
}

int main()
{
	vector<int> Preordine;
	vector<int> Inordine;
	Preordine = citire(Inordine);
	system("pause");
	return 0;
}