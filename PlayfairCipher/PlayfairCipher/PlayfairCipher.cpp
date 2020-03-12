#include <iostream>
#include <string.h>

struct Digraph
{
	char first;
	char second;
};

void read(char phrase[], char message[])
{
	std::cout << "The key-phrase and the message to encrypt must have just uppercase or lowercase letter(without Q and q) and spaces!" << std::endl;
	std::cout << "Enter the key-phrase: ";
	std::cin.getline(phrase, 30);
	std::cout << "Enter the message to encrypt: ";
	std::cin.getline(message, 30);
}

bool validation(char expression[30])
{
	for (int index = 0; index < strlen(expression); index++)
		if (!strchr("ABCDEFGHIJKLMNOPRSTUVWXYZabcdefghijklmnoprstuvwxyz ", expression[index]))
			return false;
	return true;
}

void convert_toupper(char expression[30])
{
	for (int index = 0; index < strlen(expression); index++)
		expression[index] = toupper(expression[index]);
}

void form_matrix(char phrase[], char matrix[5][5])
{
	int row = 0, column = 0, index_ph = 0, index_fr = 0, frequency[26] = { 0 };
	frequency[16]++;
	convert_toupper(phrase);
	while (row < 5)
	{
		column = 0;
		while (column < 5)
		{
			if (index_ph < strlen(phrase))
			{
				if (phrase[index_ph] == ' ')
					index_ph++;
				else
				{
					if (!frequency[phrase[index_ph] - 'A'])
					{
						matrix[row][column] = phrase[index_ph];
						frequency[phrase[index_ph] - 'A']++;
						column++;
					}
					index_ph++;
				}
			}
			else
			{
				if (!frequency[index_fr])
				{
					matrix[row][column] = index_fr + 'A';
					frequency[index_fr]++;
					column++;
				}
				index_fr++;
			}
		}
		row++;
	}
}

void form_digraphs(char message[], Digraph crypt[15], int &nr_digraph)
{
	nr_digraph = 0;
	convert_toupper(message);
	int dim = 0;
	char mess[15][30];
	char *p = strtok(message, " ");
	while (p)
	{
		strcpy(mess[dim++], p);
		p = strtok(0, " ");
	}
	int transport = 0;
	for (int index1 = 0; index1 < dim; index1++)
	{
		int index2;
		for (index2 = transport; index2 < strlen(mess[index1]) - 1; index2 += 2)
		{
			crypt[nr_digraph].first = mess[index1][index2];
			crypt[nr_digraph++].second = mess[index1][index2 + 1];
		}
		if ((strlen(mess[index1]) % 2 == 0 && transport == 1) || (strlen(mess[index1]) % 2 == 1 && transport == 0))
		{
			crypt[nr_digraph].first = mess[index1][index2];
			crypt[nr_digraph++].second = (index1 < dim - 1) ? mess[index1 + 1][0] : 'Z';
		}
		if ((strlen(mess[index1]) % 2 == 1 && transport == 1) || (strlen(mess[index1]) % 2 == 1 && transport == 0))
			transport = !transport;
	}
}

void form_encryption(Digraph encryption[], Digraph crypt[],int nr_digraph, char matrix[5][5])
{
	int row_first, row_second, column_first, column_second;
	for (int index = 0; index < nr_digraph; index++)
	{
		for (int row = 0; row < 5; row++)
			for (int column = 0; column < 5; column++)
				if (matrix[row][column] == crypt[index].first)
				{
					row_first = row;
					column_first = column;
				}
				else
					if (matrix[row][column] == crypt[index].second)
					{
						row_second = row;
						column_second = column;
					}
		if (row_first == row_second)
		{
			encryption[index].first = (column_first == 4) ? matrix[row_first][0] : matrix[row_first][column_first + 1];
			encryption[index].second = (column_second == 4) ? matrix[row_second][0] : matrix[row_second][column_second + 1];
		}
		else
			if (column_first == column_second)
			{
				encryption[index].first = (row_first == 4) ? matrix[0][column_first] : matrix[row_first + 1][column_first];
				encryption[index].second = (row_second == 4) ? matrix[0][column_second] : matrix[row_second + 1][column_second];
			}
			else
			{
				encryption[index].first = matrix[row_first][column_second];
				encryption[index].second = matrix[row_second][column_first];
			}
	}
}

void write(Digraph encryption[], Digraph crypt[], int nr_digraph, char matrix[5][5])
{
	std::cout << std::endl;
	for (int index = 0; index < 5; index++)
	{
		for (int index1 = 0; index1 < 5; index1++)
			std::cout << matrix[index][index1] << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl;
	for (int index = 0; index < nr_digraph; index++)
		std::cout << crypt[index].first << crypt[index].second << " ";
	std::cout << std::endl;
	for (int index = 0; index < nr_digraph; index++)
		std::cout << encryption[index].first << encryption[index].second << " ";
	std::cout << std::endl;
}

int main()
{
	char phrase[30], message[30], matrix[5][5];
	Digraph encryption[15], crypt[15];
	int nr_digraph;
	read(phrase, message);
	if (validation(phrase) && validation(message))
	{
		form_matrix(phrase, matrix);
		form_digraphs(message, crypt, nr_digraph);
		form_encryption(encryption, crypt, nr_digraph, matrix);
		write(encryption, crypt, nr_digraph, matrix);
	}
	else
		std::cout << "Key-phrase or message invalid!" << std::endl;
	system("pause");
	return 0;
}