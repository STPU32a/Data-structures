#include <iostream>
using namespace std;

class Element
{
	int Data;
	Element* pLeft;
	Element* pRight;

public:
	Element(int Data, Element* pRight = nullptr, Element* pLeft = nullptr)
	{
		this->Data = Data;
		this->pRight = pLeft;
		this->pLeft = pLeft;
		cout << "EConstructor:\t" << this << endl;
	}


	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}

	bool isLeaf()
	{
		if (pLeft == pRight)return true;
		return false;
	}

	friend class Tree;
};

class Tree
{
	Element* Root;


public:
	Element* getRoot()
	{
		return this->Root;
	}

	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}

	void Insert(const int& Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)
			{
				Root->pLeft = new Element(Data);
			}
			else
			{
				Insert(Data, Root->pLeft);
			}
		}
		//else
		if (Data > Root->Data)
		{
			if (Root->pRight)
			{
				Insert(Data, Root->pRight);
			}
			else
			{
				Root->pRight = new Element(Data);
			}
		}
	}

	void Insert(const int& Data)
	{
		Insert(Data, this->Root);
	}

	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}


	void Print(Element* Root)
	{
		if (Root == nullptr)return;
		Print(Root->pLeft);
		cout << Root->Data << "\t";
		Print(Root->pRight);
	}

	void Print()
	{
		if (this->Root == nullptr)cout << "Tree is empty!\n";
		Print(this->Root);
		cout << endl;
	}

	int minValue(Element* Root)
	{
		if (Root->pLeft == nullptr)return Root->Data;
		return minValue(Root->pLeft);
	}

	int maxValue(Element* Root)
	{
		if (Root->pRight == nullptr)return Root->Data;
		return maxValue(Root->pRight);
	}

	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
		this->Root = nullptr;
		//if (Root->pLeft)
		//{
		//	if (Root->pLeft->isLeaf())
		//	{
		//		delete Root->pLeft;
		//		Root->pLeft = nullptr;
		//	}
		//}
		//if (Root->pRight)
		//{
		//	if (Root->pRight->isLeaf())
		//	{
		//		delete Root->pRight;
		//		Root->pRight = nullptr;
		//	}
		//}
	}
};



void main()
{
	setlocale(LC_ALL, "Russian");
	int n;
	cout << "Введите кол-во элементов: "; cin >> n;
	Tree T800;
	for (int i = 0; i < n; i++)
	{
		T800.Insert(rand() % 10);
	}
	/*int a = 5;
	T800.Insert(a, T800.getRoot());*/
	//T800.Print(T800.getRoot());
	T800.Print();
	cout << "Минимальное значение в дереве: " << T800.minValue(T800.getRoot()) << endl;
	cout << "Максимальное значение в дереве: " << T800.maxValue(T800.getRoot()) << endl;
	T800.Clear(T800.getRoot());
	T800.Print();
}