//־נכמג ָכüÿ - BinaryTree
#include<iostream>
class Element
{
	int Data;
	Element*pLeft;
	Element*pRight;
public:
	Element(int Data, Element*pLeft = nullptr, Element*pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
	{
		std::cout << "Inserting:\t" << this->Data << "\t";
		std::cout << "EConstructor: " << this << std::endl;
	}
	~Element()
	{
		std::cout << "Deleting:\t" << this->Data << "\t" << std::endl;
		std::cout << "EDestructor: " << this << std::endl;
	}
	friend class Tree;
};

class Tree
{
	Element*Root;

	//Private Auxiliary Methods
	void Insert(int Data, Element*Root)
	{
		if (this->Root == nullptr)	this->Root = new Element(Data);
		if (Root == nullptr) return;
		if (Data <= Root->Data)
		{
			if (Root->pLeft == nullptr)	Root->pLeft = new Element(Data);
			else Insert(Data, Root->pLeft);		
		}
		if (Data > Root->Data)
		{
			if (Root->pRight == nullptr) Root->pRight = new Element(Data);
			else Insert(Data, Root->pRight);
		}
	}
	int Sum_branch_left(Element*root)
	{
		if (root == nullptr)return 0;
		return root->Data + Sum(root->pLeft);
	}
	int Sum_branch_right(Element*root)
	{
		if (root == nullptr)return 0;
		return root->Data + Sum(root->pRight);
	}
	int Sum(Element*root)
	{
		if (root == nullptr)return 0;
		return root->Data + Sum(root->pLeft) + Sum(root->pRight);
	}
	bool isLeaf(Element*root)
	{
		if (root == nullptr)return false;
		else{ return true; }
	}
	Element* erase(int value, Element*root)
	{
		Element* temp;
		if (root == nullptr)
		{
			return nullptr;
		}
		else if (value < root->Data)
			root->pLeft = erase(value, root->pLeft);
		else if (value>root->Data)
			root->pRight = erase(value, root->pRight);
		else if (root->pLeft&&root->pRight)
		{
			temp = findMin(root->pRight);
			root->Data = temp->Data;
			root->pRight = erase(root->Data, root->pRight);
		}
		else
		{
			temp = root;
			if (root->pLeft == nullptr)
				root = root->pRight;

			else if (root->pRight == nullptr)
				root = root->pLeft;
			delete temp;
		}
		return root;
	}
	void clear(Element*root)
	{
		if (root != nullptr)
		{
			clear(root->pLeft);
			clear(root->pRight);
			delete(root);
			Root = nullptr;
		}
	}
	void Print(Element*Root)
	{
		if (Root == nullptr)return;
		Print(Root->pLeft);
		std::cout << Root->Data << "\t";
		Print(Root->pRight);
	}

public:
	//Constructors
	Tree()
	{
		Root = nullptr;
	}
	Tree(const Tree& other) :Tree()
	{
		Copy(other.getRoot());
		std::cout << "CopyConstructor: " << this << std::endl;
	}
	Tree(Tree&&Data) : Root(Data.Root)
	{
		std::cout << "MoveConstructor: " << this << std::endl;
	}
	Tree(std::initializer_list<int> il)
	{
		Root = nullptr;
		for (const int* it = il.begin(); it != il.end(); it++)Insert(*it);
		std::cout << "Initializer Constructor: " << this << std::endl;
	}

	//Operator Overloading
	Tree&operator=(const Tree&other)
	{
		clear();
		Copy(other.getRoot());
		std::cout << "Operator '=' : " << this << std::endl;
		return *this;
	}
	Tree&operator= (Tree&&other)
	{
		clear();
		Copy(other.getRoot());
		std::cout << "Move Assignment: " << this << std::endl;
		return*this;
	}

	//Auxiliary Methods
	void Copy(Element*root)
	{
		if (root == nullptr)return;
		Insert(root->Data);
		Copy(root->pLeft);
		Copy(root->pRight);

	}
	void Insert(int Data)
	{
		Insert(Data, this->Root);
	}
	Element* getRoot() const
	{
		return Root;
	}
	int getMin()
	{
		Element*temp = this->Root;
		while (temp->pLeft->pLeft != nullptr) temp = temp->pLeft;
		return temp->pLeft->Data;
	}
	Element*findMin(Element*root)
	{
		if (root == nullptr)return 0;
		else if (root->pLeft == nullptr)return root;
		else
			return findMin(root->pLeft);
	}
	Element*findMax(Element*root)
	{
		if (root == nullptr)return 0;
		else if (root->pRight == nullptr)return root;
		else
			return findMin(root->pRight);
	}
	int getMax()
	{
		Element*temp = this->Root;
		while (temp->pRight->pRight != nullptr) temp = temp->pRight;
		return temp->pRight->Data;
	}
	int Sum()
	{
		 Sum(this->Root);
	}
	void  Sum_branch_left()
	{
		Sum_branch_left(this->Root);
	}
	void Sum_branch_right()
	{
		Sum_branch_right(this->Root);
	}
	bool  isLeaf()
	{
		 isLeaf(this->Root);
	}
	bool isContein(int value, Element*root)
	{
		if (root->Data == value) return true;
		if (root->pLeft)return isContein(value, root->pLeft);
		if (root->pRight)return isContein(value, root->pRight);
		return false;
	}
	void erase(int value)
	{
		while (this->isContein(value, this->getRoot()))
			erase(value, this->Root);
	}
	void clear()
	{
		clear(this->Root);
	}
	void Print()
	{
		if (Root == nullptr)std::cout << "Tree is empty." << std::endl;
		std::cout << "\n";
		Print(this->Root);
		std::cout <<'\n' <<std::endl;
	}
};
void main()
{
	setlocale(LC_ALL, "ru");
	Tree T800{ 50, 25, 20, 30, 75, 70,20, 80 };
	T800.Print();
	Tree t;
	t= T800;
	t.Print();
	t.clear();
	t.Print();
}