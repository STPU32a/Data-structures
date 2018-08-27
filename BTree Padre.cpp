//Mетод Print для Бинарного дерева(if\else через терн. опер.);
//СТПУ32А
//Выжик Евгений 
#include<iostream>
using namespace std;

class element//класс element для Бинарного дерева, содержит значения('data') и указатель на дочерние элементы('element* pLeft' и 'element pRight');
{
	int data;
	element* pLeft;
	element* pRight;
public:
	element(int data, element* pLeft = nullptr, element* pRight = nullptr)/* Конструктор для создания элементов со списком инициализации*/ :data(data), pLeft(pLeft), pRight(pRight)
	{
		cout << "EConstructor :\t" << this << endl;
	}

	~element()//Деструктор
	{
		cout << "EDestructor :\t" << this << endl;
	}

	bool is_leaf()// Проверка наличия дочерних элементов;
	{
		return (pLeft == pRight) ? true : false;

		/*if (pLeft == pRight)
		{
		return true;
		}
		else
		{
		return false;
		}*/

	}

	friend class tree;//добавление дружественного класса tree;
};

class tree
{
	element* root;//указатель на 'корень' класса tree;
public:

	element* getroot()
	{
		return this->root;
	}

	tree()
	{
		root = nullptr;
		cout << "TConstructor :\t" << this << endl;
	}

	tree(initializer_list<int> list) :tree()
	{
		for (const int* i = list.begin(); i != list.end(); i++)insert(*i);
	}


	~tree()
	{
		cout << "TDestructor :\t" << this << endl;
	}

	void insert(int data, element* root)
	{
		if (this->root == nullptr)this->root = new element(data);
		if (root == nullptr)return;
		if (data < root->data)
		{
			(root->pLeft == nullptr) ? root->pLeft = new element(data)/*if (root->pLeft !=nullptr)*/ : insert(data, root->pLeft);
		}
		if (data > root->data)/*else//if(data>root->data)*/
		{
			(root->pRight != nullptr) ? insert(data, root->pRight)/*if(root->pRight==nullptr)*/ : root->pRight = new element(data);
		}
	}

	void insert(const int& data)
	{
		insert(data, this->root);
	}

	void print(element* root)
	{
		if (root == nullptr)return;
		print(root->pLeft);
		cout << root->data << "\t";
		print(root->pRight);
	}

	void print()
	{
		if (this->root == nullptr)cout << "Tree is empty!";
		print(this->root);
		cout << endl;
	}

	int minValue(element* root)
	{
		//return (root->pLeft == nullptr) ? root->data : minValue(root->pLeft);

		if (root->pLeft == nullptr)
		{
			return root->data;
		}
		else
		{
			return minValue(root->pLeft);
		}


	}

	int maxValue(element* root)
	{
		return (root->pRight == nullptr) ? root->data : maxValue(root->pRight);
	}

	void clear(element* root)
	{
		if (root == nullptr)return;
		clear(root->pLeft);
		clear(root->pRight);
		delete root;
		this->root = nullptr;
	}
};


void main()
{
	setlocale(LC_ALL, "Russian");

	int n;
	cout << "Введите количество элементов Tree:\t" << endl;	cin >> n;
	tree T;// { 50, 25, 75, 20, 30, 70, 80, 15, 21, 28, 32, 64, 72, 77, 88 };
	for (int i = 0; i < n; i++)
	{
		T.insert(rand() % 100);
	}

	//T.print(T.getroot());
	T.print();
	//cout << "Корень tree -\t" << T.is_leaf(T.getroot()) << endl;
	cout << "Корень tree -\t" << T.getroot() << endl;
	cout << "Минимальное значение -\t" << T.minValue(T.getroot()) << endl;
	cout << "Максимальное значение -\t" << T.maxValue(T.getroot()) << endl;

	T.clear(T.getroot());
	//T.clear(T.getroot());//проверочный вызов;
	T.print();
	/*cout << "Элемент ---\t" << element* root;*/
}