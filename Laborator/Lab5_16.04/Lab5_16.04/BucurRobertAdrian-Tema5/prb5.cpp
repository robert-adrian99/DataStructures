// PROBLEMA 5 || TEMA 5
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#define BLACK false
#define RED true
using namespace std;

template<class KeyType, class ValueType>
struct Pair
{
	KeyType key;
	ValueType value;
	Pair()
	{
		key = NULL;
		value = NULL;
	}
	Pair(KeyType k, ValueType v)
	{
		key = k;
		value = v;
	}
};

template<class KeyType, class ValueType>
struct Nod
{
	Pair<KeyType, ValueType> info;
	bool color;  //true - red  ||  false - black
	Nod<KeyType,ValueType> *left, *right, *parent;
	Nod()
	{
		color = BLACK;
	}
	Nod(KeyType x,ValueType y)
	{
		Pair<KeyType, ValueType> i(x, y);
		info = i;
		color = RED;
		left = right = parent = NULL;
	}
};

template<class KeyType, class ValueType>
class MAP
{
private:
	Nod<KeyType,ValueType> *Root;
	Nod<KeyType,ValueType> *NIL;
	void InsertRepair(Nod<KeyType,ValueType>* x)
	{
		while (x->parent->color == RED)
		{
			if (x->parent == x->parent->parent->left)
			{
				Nod<KeyType,ValueType>* uncle = x->parent->parent->right;
				if (uncle->color == RED)
				{
					x->parent->color = BLACK;
					uncle->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else 
				{
					if (x == x->parent->right)
					{
						x = x->parent;
						LeftRotation(x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					RightRotation(x->parent->parent);
				}
			}
			else
			{
				Nod<KeyType,ValueType>* uncle = x->parent->parent->left;
				if (uncle->color == RED)
				{
					x->parent->color = BLACK;
					uncle->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->left)
					{
						x = x->parent;
						RightRotation(x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					LeftRotation(x->parent->parent);
				}
			}
		}
		Root->color = BLACK;
	}
	void DeleteRepair(Nod<KeyType,ValueType>* x)
	{
		if (x->color == RED)
		{
			x->color = BLACK;
			return;
		}
		if (x->parent->left == x)
		{
			Nod<KeyType,ValueType> *brother = x->parent->right;
			if (brother->color == RED)
			{
				brother->color = BLACK;
				x->parent->color = RED;
				LeftRotation(x->parent);
			}
			brother = x->parent->right;
			if (brother->color == BLACK && brother->right->color == BLACK && brother->left->color == BLACK)
			{
				brother->color = RED;
				return DeleteRepair(x->parent);
			}
			if (brother->color == BLACK && brother->right->color == BLACK && brother->left->color == RED)
			{
				brother->left->color = BLACK;
				brother->color = RED;
				RightRotation(brother);
			}
			brother = x->parent->right;
			brother->color = x->parent->color;
			x->parent->color = BLACK;
			brother->right->color = BLACK;
			LeftRotation(x->parent);
		}
		else
		{
			Nod<KeyType,ValueType> *brother = x->parent->left;
			if (brother->color == RED)
			{
				brother->color = BLACK;
				x->parent->color = RED;
				RightRotation(x->parent);
			}
			brother = x->parent->left;
			if (brother->color == BLACK && brother->right->color == BLACK && brother->left->color == BLACK)
			{
				brother->color = RED;
				return DeleteRepair(x->parent);
			}
			if (brother->color == BLACK && brother->right->color == RED && brother->left->color == BLACK)
			{
				brother->right->color = BLACK;
				brother->color = RED;
				LeftRotation(brother);
			}
			brother = x->parent->left;
			brother->color = x->parent->color;
			x->parent->color = BLACK;
			brother->left->color = BLACK;
			RightRotation(x->parent);
		}
	}
	void LeftRotation(Nod<KeyType,ValueType>* x)
	{
		Nod<KeyType,ValueType> *y = x->right;
		x->right = y->left;
		if (x->right != NIL)
			x->right->parent = x;
		y->parent = x->parent;
		if (x->parent == NIL)
			Root = y;
		else if (x == x->parent->left)
			y = x->parent->left;
		else
			y = x->parent->right;
		x->parent = y;
		y->left = x;
	}
	void RightRotation(Nod<KeyType,ValueType>* x)
	{
		Nod<KeyType,ValueType> *y = x->left;
		x->left = y->right;
		if (x->left != NIL)
			x->left->parent = x;
		y->parent = x->parent;
		if (x->parent == NIL)
			Root = y;
		else if (x == x->parent->right)
			y = x->parent->right;
		else
			y = x->parent->left;
		x->parent = y;
		y->right = x;
	}
	void Transplant(Nod<KeyType,ValueType>* u, Nod<KeyType,ValueType>* v)
	{
		if (u->parent == NIL)
			Root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		if (v != NIL)
			v->parent = u->parent;
	}
	void Preorder(Nod<KeyType,ValueType>* x)
	{
		if (x == NIL)
			return;
		cout << "MAP[" << x->info.key << "]:" << x->info.value << " ";
		Preorder(x->left);
		cout << " ";
		Preorder(x->right);
	}
	void Inorder(Nod<KeyType,ValueType>* x)
	{
		if (x == NIL)
			return;
		Inorder(x->left);
		cout << " " << "MAP[" << x->info.key << "]:" << x->info.value << " ";
		Inorder(x->right);
	}
	void Postorder(Nod<KeyType,ValueType>* x)
	{
		if (x == NIL)
			return;
		Postorder(x->left);
		cout << " ";
		Postorder(x->right);
		cout << " " << "MAP[" << x->info.key << "]:" << x->info.value;
	}
	void BreadthFirst()
	{
		int level = 0, nr1 = 0, nr2 = 0;
		queue<Nod<KeyType,ValueType>*> q;
		q.push(Root);
		cout << "Level 0:";
		nr1++;
		while (!q.empty())
		{
			Nod<KeyType,ValueType> *x = q.front();
			if (x->left != NIL)
			{
				q.push(x->left);
				nr2++;
			}
			if (x->right != NIL)
			{
				q.push(x->right);
				nr2++;
			}
			cout << "MAP[" << q.front()->info.key << "]:" << q.front()->info.value << " ";
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
	MAP()
	{
		NIL = new Nod<KeyType,ValueType>;
		NIL->left = NIL->right = NIL->parent = NIL;
		Root = NIL;
	}
	MAP(KeyType k, ValueType v)
	{
		Root = new Nod<KeyType,ValueType>(k, v);
		Root->color = BLACK;
	}
	Nod<KeyType,ValueType>* GetRoot()
	{
		return Root;

	}
	void Insert(Nod<KeyType,ValueType>* x)
	{
		x->color = RED;
		x->left = x->right = NIL;
		Nod<KeyType,ValueType>* z = Root;
		Nod<KeyType,ValueType>* y = NIL;
		while (z != NIL)
		{
			y = z;
			if (x->info.key < z->info.key)
				z = z->left;
			else
				z = z->right;
		}
		x->parent = y;
		if (y == NIL)
			Root = x;
		else if (x->info.key < y->info.key)
			y->left = x;
		else
			y->right = x;
		InsertRepair(x);
	}
	Nod<KeyType,ValueType>* Maxim(Nod<KeyType,ValueType>* x)
	{
		Nod<KeyType,ValueType> *y = x;
		while (y->right != NIL)
			y = y->right;
		return y;
	}
	Nod<KeyType,ValueType>* Minim(Nod<KeyType,ValueType>* x)
	{
		Nod<KeyType,ValueType> *y = x;
		while (y->left != NIL)
			y = y->left;
		return y;
	}
	Nod<KeyType,ValueType>* Successor(Nod<KeyType,ValueType>* x)
	{
		if (x->right != NIL)
			return Minim(x->right);
		Nod<KeyType,ValueType> *parent = x->parent;
		while (parent != NIL && x == parent->right)
		{
			x = parent;
			parent = parent->parent;
		}
		return parent;
	}
	Nod<KeyType,ValueType>* Predecessor(Nod<KeyType,ValueType>* x)
	{
		if (x->left != NIL)
			return Maxim(x->left);
		Nod<KeyType,ValueType> *parent = x->parent;
		while (parent != NIL && x == parent->left)
		{
			x == parent;
			parent = parent->parent;
		}
		return parent;
	}
	Nod<KeyType,ValueType>* Search(ValueType k)
	{
		Nod<KeyType,ValueType> *x = Root;
		while (x != NIL && x->key != k)
			if (k < x->key)
				x = x->left;
			else
				x = x->right;
		return x;
	}
	void Delete(Nod<KeyType,ValueType>* x)
	{
		if (x->left == NIL)
		{
			Transplant(x, x->right);
			Delete_Repair(x);
		}
		else if (x->right == NIL)
		{
			Transplant(x, x->left);
			Delete_Repair(x);
		}
		else
		{
			Nod<KeyType,ValueType> *y = Successor(x);
			if (y != x->right)
			{
				Transplant(y, y->right);
				y->right = x->right;
				x->right->parent = y;
			}
			Nod<KeyType,ValueType> *parent = y->parent;
			Transplant(x, y);
			y->left = x->left;
			x->left->parent = y;
			Delete_Repair(parent);
		}
	}
	void PrintTree(int option)
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
	void Clear()
	{
		while (Root != NIL)
			Delete(Root);
	}
	bool isEmpty()
	{
		if (Root == NIL)
			return true;
		return false;

	}
	int Size()
	{
		int nr = 0;
		queue<Nod<KeyType,ValueType>*> q;
		q.push(Root);
		nr++;
		while (!q.empty())
		{
			Nod<KeyType,ValueType> *x = q.front();
			if (x->left != NIL)
			{
				q.push(x->left);
				nr++;
			}
			if (x->right != NIL)
			{
				q.push(x->right);
				nr++;
			}
			q.pop();
		}
		return nr;
	}
	ValueType operator[](KeyType k)
	{
		Nod<KeyType,ValueType>* x = Search(k);
		if (x != NIL)
			return x->value;
	}
	void operator=(Pair<KeyType,ValueType> x)
	{
		Nod<KeyType,ValueType>* y = new Nod<KeyType,ValueType>(x.key, x.value);
		Insert(y);
	}
};
int main()
{
	MAP<int, char> m;
	Pair<int, char> p;
	p.key = 1;
	p.value = 'x';
	m = p;
	m.PrintTree(1);
	system("pause");
	return 0;
}