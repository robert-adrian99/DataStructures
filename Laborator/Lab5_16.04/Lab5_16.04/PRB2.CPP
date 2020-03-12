//PROBLEMA 2 || TEMA 5
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

template<class T>
struct Nod
{
	T info;
	int FactorBalansare;
	int height;
	Nod *left, *right, *parent;
	Nod()
	{
		left = right = parent = NULL;
	}
	Nod(T x)
	{
		info = x;
		FactorBalansare = 0;
		height = 0;
		left = right = parent = NULL;
	}
};

template<class T>
class AVL
{
private:
	Nod<T> *Root;
	void Insert_Repair(Nod<T>* x)
	{
		if (x == NULL)
			return;
		Nod<T> *y = x->parent;
		if (x == y->left)
			y->FactorBalansare++;
		else
			y->FactorBalansare--;
		if (y->FactorBalansare == 0)
			return;
		if (y->FactorBalansare == 1 || y->FactorBalansare == -1)
			return Insert_Repair(y);
		if (y->FactorBalansare == -2)
		{
			Nod<T> *z = y->left;
			if (z->FactorBalansare == -1)
			{
				Rot_Right(y);
				y->FactorBalansare = y->right->height - y->left->height;
				y->parent->FactorBalansare = y->parent->right->height - y->parent->left->height;
				return;
			}
			if (z->FactorBalansare == 1)
			{
				Rot_Left(z);
				Rot_Right(y);
				z->FactorBalansare = z->right->height - z->left->height;
				y->FactorBalansare = y->right->height - y->left->height;
			}
			return;
		}
		if (y->FactorBalansare == 2)
		{
			Nod<T> *z = y->right;
			if (z->FactorBalansare == 1)
			{
				Rot_Left(y);
				y->FactorBalansare = y->right->height - y->left->height;
				y->parent->FactorBalansare = y->parent->right->height - y->parent->left->height;
				return;
			}
			if (z->FactorBalansare == -1)
			{
				Rot_Right(z);
				Rot_Left(y);
				z->FactorBalansare = z->right->height - z->left->height;
				y->FactorBalansare = y->right->height - y->left->height;
			}
			return;
		}
	}
	void Delete_Repair(Nod<T>* x)
	{
		if (x == NULL)
			return;
		Nod<T> *y = x->parent;
		if (x == y->left)
			y->FactorBalansare++;
		else
			y->FactorBalansare--;
		if (y->FactorBalansare == -1 || y->FactorBalansare == 1)
			return;
		if (y->FactorBalansare == 0)
			return Delete_Repair(y);
		if (y->FactorBalansare == -2)
		{
			Nod<T> *z = y->left;
			if (z->FactorBalansare == 0)
			{
				Rot_Right(y);
				z->FactorBalansare = 1;
				y->FactorBalansare = -1;
				return;

			}
			if (z->FactorBalansare == -1)
			{
				Rot_Right(y);
				z->FactorBalansare = 0;
				y->FactorBalansare = 0;
				return Delete_Repair(y);
			}
			if (z->FactorBalansare == 1)
			{
				Rot_Left(z);
				Rot_Right(y);
				return Delete_Repair(y);
			}
		}
		if (y->FactorBalansare == 2)
		{
			Nod<T> *z = y->right;
			if (z->FactorBalansare == 0)
			{
				Rot_Left(y);
				z->FactorBalansare = -1;
				y->FactorBalansare = 1;
				return;
			}
			if (z->FactorBalansare == 1)
			{
				Rot_Left(y);
				z->FactorBalansare = 0;
				y->FactorBalansare = 0;
				return Delete_Repair(y);
			}
			if (z->FactorBalansare == -1)
			{
				Rot_Right(z);
				Rot_Left(y);
				return Delete_Repair(y);
			}
		}
	}
	void Rot_Left(Nod<T> *x)
	{
		Nod<T> *y = x->right;
		x->right = y->left;
		if (x->right != NULL)
			x->right->parent = x;
		y->parent = x->parent;
		if (x->parent == NULL)
			Root = y;
		else if (x == x->parent->left)
			y = x->parent->left;
		else
			y = x->parent->right;
		x->parent = y;
		y->left = x;
		y->height = max(y->left->height, y->right->height) + 1;
		x->height = max(x->left->height, x->right->height) + 1;
	}
	void Rot_Right(Nod<T> *x)
	{
		Nod<T> *y = x->left;
		x->left = y->right;
		if (x->left != NULL)
			x->left->parent = x;
		y->parent = x->parent;
		if (x->parent == NULL)
			Root = y;
		else if (x == x->parent->right)
			y = x->parent->right;
		else
			y = x->parent->left;
		x->parent = y;
		y->right = x;
		x->height = max(x->left->height, x->right->height) + 1;
		y->height = max(y->left->height, y->right->height) + 1;
	}
	void Transplant(Nod<T> *u, Nod<T> *v)
	{
		if (u->parent == NULL)
			Root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v != NULL)
			v->parent = u->parent;
	}
	void Preorder(Nod<T> *x)
	{
		if (x == NULL)
			return;
		cout << x->info << " ";
		Preorder(x->left);
		cout << " ";
		Preorder(x->right);
	}
	void Inorder(Nod<T> *x)
	{
		if (x == NULL)
			return;
		Inorder(x->left);
		cout << " " << x->info << " ";
		Inorder(x->right);
	}
	void Postorder(Nod<T> *x)
	{
		if (x == NULL)
			return;
		Postorder(x->left);
		cout << " ";
		Postorder(x->right);
		cout << " " << x->info;
	}
	void BreadthFirst()
	{
		int level = 0, nr1 = 0, nr2 = 0;
		queue<Nod<T>*> q;
		q.push(Root);
		cout << "Level 0:";
		nr1++;
		while (!q.empty())
		{
			Nod<T> *x = q.front();
			if (x->left != NULL)
			{
				q.push(x->left);
				nr2++;
			}
			if (x->right != NULL)
			{
				q.push(x->right);
				nr2++;
			}
			cout << q.front()->info << " ";
			q.pop();
			nr1--;
			if (nr1 == 0)
			{
				level++;
				cout << "Level " << level << ":";
				nr1 = nr2;
				nr2 = 0;
			}
		}
	}
public:
	AVL()
	{
		Root = NULL;
	}
	AVL(T information)
	{
		Root = new Nod<T>(information);
	}
	Nod<int>* GetRoot()
	{
		return Root;
	}
	void Insert(Nod<T> *x)
	{
		Nod<T> *z = Root;
		Nod<T> *y = NULL;
		while (z != NULL)
		{
			y = z;
			if (x->info < z->info)
				z = z->left;
			else
				z = z->right;
		}
		x->parent = y;
		if (y == NULL)
			Root = x;
		else if (x->info < y->info)
			y->left = x;
		else
			y->right = x;
		Insert_Repair(x);
	}
	Nod<T>* Maxim(Nod<T>* x)
	{
		Nod<T> *y = x;
		while (y->right != NULL)
			y = y->right;
		return y;
	}
	Nod<T>* Minim(Nod<T>* x)
	{
		Nod<T> *y = x;
		while (y->left != NULL)
			y = y->left;
		return y;
	}
	Nod<T>* Successor(Nod<T>* x)
	{
		if (x->right != NULL)
			return Minim(x->right);
		Nod<T> *parent = x->parent;
		while (parent != NULL && x == parent->right)
		{
			x = parent;
			parent = parent->parent;
		}
		return parent;
	}
	Nod<T>* Predecessor(Nod<T>* x)
	{
		if (x->left != NULL)
			return Maxim(x->left);
		Nod<T> *parent = x->parent;
		while (parent != NULL && x == parent->left)
		{
			x = parent;
			parent = parent->parent;
		}
		return parent;
	}
	Nod<T>* Search(T value)
	{
		Nod<T> *x = Root;
		while (x != NULL && x->info != value)
			if (value < x->info)
				x = x->left;
			else
				x = x->right;
		return x;
	}
	void Delete(Nod<T>* x)
	{
		if (x->left == NULL)
		{
			Transplant(x, x->right);
			Delete_Repair(x);
		}
		else if (x->right == NULL)
		{
			Transplant(x, x->left);
			Delete_Repair(x);
		}
		else
		{
			Nod<T> *y = Successor(x);
			if (y != x->right)
			{
				Transplant(y, y->right);
				y->right = x->right;
				x->right->parent = y;
			}
			Nod<T> *parent = y->parent;
			Transplant(x, y);
			y->left = x->left;
			x->left->parent = y;
			Delete_Repair(parent);
		}
	}
	void Print_Tree(int option)
	{
		switch (option)
		{
		case 1:
			Preorder(Root);
			break;
		case 2:
			Inorder(Root);
			break;
		case 3:
			Postorder(Root);
			break;
		case 4:
			BreadthFirst();
			break;
		default:
			cout << "Enter a valid option!";
			break;
		}
	}
	void Empty()
	{
		while (Root != NULL)
			Delete(Root);
	}
	void Construct(vector<T> vect)
	{
		for (int index = 0; index < vect.size(); index++)
			Insert(vect[index]);
	}
	void Merge(AVL<T> Tree1)
	{
		AVL<T> Tree2;

	}
};

int main()
{
	AVL<int> Tree;
	int option;
	cout << "MENU of AVL Tree operations:" << endl;
	cout << "1. Insert a value." << endl << "2. Search a value." << endl << "3. Delete a value." << endl << "4. Get the minimum value." << endl;
	cout << "5. Get the maximum value." << endl << "6. Get the successor value of a given one." << endl << "7. Get the predecessor value of a given value";
	cout << endl << "8. Print the tree values in 4 ways." << endl << "9. Join." << endl << "10. Exit." << endl;
	cout << "Enter your choice: ";
	cin >> option;
	while (option != 10)
	{
		switch (option)
		{
		case 1:
		{
			int x;
			cout << "Enter the value that you want to insert in the AVL Tree: ";
			cin >> x;
			Nod<int> *y = new Nod<int>(x);
			Tree.Insert(y);
			break;
		}
		case 2:
		{
			int x;
			cout << "Enter the value that you want to search in the AVL Tree: ";
			cin >> x;
			Nod<int> *y = Tree.Search(x);
			if (y == NULL)
				cout << "There is no such a value in the AVL Tree!";
			else
				cout << "The value was found!";
			break;
		}
		case 3:
		{
			int x;
			cout << "Enter the value that you want to delete from the AVL Tree: ";
			cin >> x;
			Nod<int> *y = Tree.Search(x);
			if (y == NULL)
				cout << "There is no such a value in the AVL Tree!";
			else
			{
				Tree.Delete(y);
				cout << "The value was deleted!";
			}
			break;
		}
		case 4:
		{
			Nod<int> *y = Tree.Minim(Tree.GetRoot());
			cout << "The minimum value is " << y->info;
			break;
		}
		case 5:
		{
			Nod<int> *y = Tree.Maxim(Tree.GetRoot());
			cout << "The maximum value is " << y->info;
			break;
		}
		case 6:
		{
			int x;
			cout << "Enter the value for which you want to get the successor from the AVL Tree: ";
			cin >> x;
			Nod<int> *y = Tree.Search(x);
			if (y == NULL)
				cout << "There is no such value in the AVL Tree!";
			else
			{
				y = Tree.Successor(y);
				cout << "The successor of " << x << " from the AVL Tree is " << y->info;
			}
			break;
		}
		case 7:
		{
			int x;
			cout << "Enter the value for which you want to get the predecessor from the AVL Tree: ";
			cin >> x;
			Nod<int> *y = Tree.Search(x);
			if (y == NULL)
				cout << "There is no such value in the AVL Tree!";
			else
			{
				y = Tree.Predecessor(y);
				cout << "The predecessor of " << x << " from the AVL Tree is " << y->info;
			}
			break;
		}
		case 8:
		{
			cout << "These are the ways of printing the AVL Tree:" << endl;
			cout << "1. Preorder" << endl << "2. Inorder" << endl << "3. Postorder" << endl << "4. Breadth First" << endl;
			cout << "Enter your choice for the way to print the AVL Tree: ";
			int x;
			cin >> x;
			Tree.Print_Tree(x);
			break;
		}
		case 9:
		case 10:
			break;
		default:
			break;
		}
		if (option == 10)
			break;
	}
	system("pause");
	return 0;
}