/*2. Se citeste dintr-un fisier o expresie aritmetica alcatuita din numere intregi fara
semn, operatorii aritmetici +, -, *, / si paranteze rotunde. Atentie, caracterele
din sir NU sunt despartite prin spatii! Sa se construiasca forma poloneza
postfixata pentru expresia aritmetica data si sa se evalueze expresia. Utilizati
stive. (Este de preferat utilizarea unui vector pentru stocarea elementelor
stivei. Se cere utilizarea unei structuri STIVA!).*/
/*Se da expresia matematica.Sa se transforme in forma poloneza postfixata si sa se evalueze expresia (folosind stive).*/
#include <iostream>
#include <string>
#define SizeMax 100

struct MyQueue
{
	char elements[10];
	int first = 0;
	int last = 0;

	bool isEmpty()
	{
		if (first >= last)
			return true;
		return false;
	}

	bool isFull()
	{
		if (last >= SizeMax)
			return true;
		return false;
	}

	void push(char element)
	{
		if (!isFull())
		{
			elements[last++] = element;
		}
	}

	void pop()
	{
		if (!isEmpty())
		{
			first++;
		}
	}

	void print()
	{
		for (int index = first; index < last; index++)
			std::cout << elements[index] << std::endl;
	}
};

struct MyStack
{
	int dim = 0;
	int vf = -1;
	char elements[100];

	bool isEmpty()
	{
		if (vf == -1)
			return true;
		return false;
	}

	bool isFull()
	{
		if (vf >= 100 || vf >= dim)
			return true;
		return false;
	}

	void push(char element)
	{
		if (!isFull())
		{
			elements[++vf] = element;
			dim++;
		}
	}

	void pop()
	{
		if (!isEmpty())
		{
			vf--;
			dim--;
		}
	}

	void print()
	{
		for (int index = 0; index < dim; index++)
			std::cout << elements[index] << " ";
		std::cout << std::endl;
	}
};

struct Operator
{
	char operatie;
	int prioritate;
};

struct OperatorStack
{
	int dim = 0;
	int vf = -1;
	Operator elements[100];

	bool isEmpty()
	{
		if (vf == -1)
			return true;
		return false;
	}

	bool isFull()
	{
		if (vf >= 100 || vf >= dim)
			return true;
		return false;
	}

	void push(char element)
	{
		if (!isFull())
		{
			elements[++vf].operatie = element;
			dim++;
			if (element == '(')
				elements[vf].prioritate = 0;
			else
				if (strchr("+-", element))
					elements[vf].prioritate = 1;
				else
					elements[vf].prioritate = 2;
		}
	}

	void pop()
	{
		if (!isEmpty())
		{
			vf--;
			dim--;
		}
	}
};

void read(char string[])
{
	std::cin.getline(string, 30);
}

bool validare(char *string)
{
	for (int index = 0; index < strlen(string); index++)
		if (!strchr("0123456789+-*/()", string[index]))
			return false;
	return true;
}

int evaluare_expresie(MyQueue forma_post)
{
	MyStack obj;
	while (!forma_post.isEmpty())
	{
		if (strchr("0123456789", forma_post.elements[forma_post.first]))
			obj.push(forma_post.elements[forma_post.first] - '0');
		else
		{
			int y = obj.elements[obj.vf];
			obj.pop();
			int x = obj.elements[obj.vf];
			obj.pop();
			if (forma_post.elements[forma_post.first] == '+')
				obj.push(x + y);
			else
				if (forma_post.elements[forma_post.first] == '-')
				{
					if (x < y)
					{
						int aux = x;
						x = y;
						y = aux;
					}
					obj.push(x - y);
				}
				else
					if (forma_post.elements[forma_post.first] == '*')
						obj.push(x * y);
					else
					{
						if (y != 0)
							obj.push(x / y);
						else
							std::cout << "Nu se poate imparti la 0";
					}
		}
		forma_post.pop();
	}
	return obj.elements[obj.vf];
}

MyQueue transformare_postfixat(char string[])
{
	MyQueue coada;
	OperatorStack obj;
	for (int index = 0; index < strlen(string); index++)
		if (strchr("0123456789", string[index]))
			coada.push(string[index]);
		else
			if (string[index] != '(')
				obj.push(string[index]);
			else
				if (string[index] == ')')
				{
					while (obj.elements[obj.vf].operatie != '(')
					{
						coada.push(obj.elements[obj.vf].operatie);
						obj.pop();
					}
					obj.pop();
				}
	while (!obj.isEmpty())
	{
		coada.push(obj.elements[obj.vf].operatie);
		obj.pop();
	}
	return coada;
}

int main()
{
	int rezultat;
	char expresie[31];
	MyQueue forma_postfixata;
	read(expresie);
	if (validare(expresie))
	{
		forma_postfixata = transformare_postfixat(expresie);
		rezultat = evaluare_expresie(forma_postfixata);
		std::cout << rezultat << std::endl;
	}
	else
		std::cout << "Expresia este invalida!" << std::endl;
	system("pause");
	return 0;
}