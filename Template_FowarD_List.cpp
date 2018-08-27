#include <iostream>
using namespace std;

#define tab "\t"
//#define BaseCheck
//#define AddingElements
//#define ConstructorsCheck
#define HardcorCheck

template<typename T>class List;

template<typename T>
class Element
{
	T Data;//�������� ��������
	Element<T>* pNext;//������ ���������� ��������
	static int Size;//���������� ���������
public:
	/////////////////////////////////Get-methods/////////////////////////////
	//int GetData()
	//{
	//	return this->Data;
	//}
	//Element* GetpNext()
	//{
	//	return this->pNext;
	//}
	///////////////////////////////Set-methods///////////////////
	//void SetData()
	//{
	//	this->Data = Data;
	//}
	//void SetpNext()
	//{
	//	this->pNext = pNext;
	//}
	/////////////////////////////////CONSTRUCTOR///////////////////////////
	Element(T Data, Element<T>* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		Size++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		Size--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class List<T>;
};

template<typename T>
int Element<T>::Size = 0;

template<typename T>
void Exchange(T& a, T& b)
{
	T temp = a;
	a = b;
	b = T temp;
}

template<typename T>
class List
{
	Element<T>* Head;//��������� �� ����� �������� �������� ������
	int Size;//���������� ��������� ������


public:
	T getSize()
	{
		return this->Size;
	}
	List()
	{
		this->Head = nullptr;//��������� �� ���� � ������ ������ �������� ��� ������ ������
		this->Size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(int Size) :List()//����������� �� �������� ����� ���������
	{
		while (Size--)push_front(0);//� ������ ������� � ���� Size ���������
	}

	List(const List<T>& other) :List()
	{
		for (Element<T>* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
			/*Element* Temp = other.Head;*/
			/*while (Temp != nullptr)*///���� ��������� �� ����� ����
		{
			push_back(Temp->Data);//��������� � ��� ������ �������� ��������
		}
		/*Temp = Temp->pNext;*///� ��������� � ���������� ��������
		cout << "LCopy Constructor: " << tab << this << endl;
	}
	List(List<T>&& other)
	{
		this->Head = other.Head;
		this->Size = other.Size;
		other.Head = nullptr;
		cout << "LMove Constructor:" << tab << this << endl;
	}
	~List()
	{
		this->Clear();
		cout << "LDestructor:\t" << this << endl;
	}
	//////////////////////Operators Overloads////////////////////////////////////
	T &operator[](int Index)//���� �������� �� ������� �������� ����������� ��� ��������
	{
		if (Index < 0 || Index >= Size)
		{
			cout << "Eror: �� �� ��������� ������!";
			/*return 0;*/
			throw 0;
		}
		Element<T>* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;//������� �� ������� ��������
		return Temp->Data;//� ���������� ��� ��������
	}
	List<T> &operator=(const List<T>& other)
	{
		Clear();//������� ������ �� ������ ���������
		for (Element<T>* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopy Assignments:" << tab << this << endl;
		return *this;
	}

	List<T> &operator=(List<T>&& other)
	{
		this->Clear();//������� ������ �� ������ ���������
		this->Head = other.Head;
		this->Size = other.Size;
		other.Head = nullptr;
		cout << "LMove Assignments:" << tab << this << endl;
		return *this;
	}

	List<T> operator+(const List<T>& other)
	{
		List res = *this;
		//for (Element* Temp = this->Head; Temp != nullptr; Temp = Temp->pNext)res.push_back(Temp->Data);
		for (Element<T>* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)res.push_back(Temp->Data);
		cout << "Operator +" << tab << this << endl;
		return res;
	}
	/////////////////////Adding Elements/////////////////////////////////////////
	void push_front(T Data)
	{
		Element<T>* New = new Element<T>(Data);//������� �������
		New->pNext = Head;//��������� ��� � ������ ������
		Head = New;// � ������� ��� ������ �� ��������� ������� ������
		/*Head = new Element(Data, Head);*/
		Size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)
		{
			push_front(Data);
			return;
		}
		/*Element* New = new Element(Data);*///������� ����� �������
		Element<T>* Temp = Head;//������� ��������� � ������� � ������
		while (Temp->pNext != nullptr)Temp = Temp->pNext;//������� �� ����� ������
		/*{
		Temp = Temp->pNext;
		*/
		Temp->pNext = new Element<T>(Data);//����� �� ��������� � ����� ������ "�����������" ����� ������� � ���������� 
		Size++;
	}

	void Insert(T Data, int Index)
	{
		if (Index > Size || Index < 0)
		{
			cout << "Error:�� ����� �� ������� ������!" << endl;
			return;
		}
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		Element<T>* Temp = Head;//������� �������
		//���������� �� ������ ��������
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Temp->pNext = new Element<T>(Data, Temp->pNext);
		Size++;
	}
	/////////////////////Deleting Elements/////////////////////////////////////////
	void pop_front()
	{
		Element<T>* Buffer = Head;
		Head = Head->pNext;
		delete Buffer;
		Size--;
	}
	void pop_back()
	{
		Element<T>* Temp = Head;//������� ��������� � ������� � ������
		while (Temp->pNext->pNext != nullptr)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		Size--;
	}
	void Erase(int Index)
	{
		if (Index == 0)
		{
			pop_front();
			return;
		}
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element<T>* Buffer = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;//��������� �� ������� ����� 1 �������
		delete Buffer;
		Size--;
	}
	////////////////////////////Auxiliary methods/////////////////////
	void Print()
	{
		cout << "����� ������:\t" << this->Head << endl;
		for (Element<T>* Temp = Head; Temp != nullptr; Temp = Temp->pNext)cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//Element* Temp = Head;//������� ���������( ��� ��������� ��� ������ ������� ����� �������� ������ � ��������� ��������� ������)
		//while (Temp != nullptr)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;
		//}
		cout << "-------------------------------------------" << endl;
		cout << "���������� ��������� ������: " <</* Element::Size<<Head->Size*/this->Size << endl;
		cout << "-------------------------------------------" << endl;
	}
	void Clear()
	{
		while (Head != nullptr)pop_front();//���� ������ �� ������ ������� ������ �������
	}
	///////////////////////////////////////////////HARDCORE////////////////////////
	void remove_value(T Value)
	{
		for (Element<T>* Temp = Head; Temp->pNext; (Temp->pNext != nullptr&&Temp->pNext->Data != Value) ? Temp = Temp->pNext : Temp)
		{
			if (Temp->pNext->Data == Value)//���� �������� ���������� �������� ������� � ���������,�� ������� ��������� �������
			{
				//��� �����:
				Element<T>* Buffer = Temp->pNext;//��������� ����� ����������(����������) ��������
				Temp->pNext = Temp->pNext->pNext;//��������� ������� �� ������
				delete Buffer;//������� ������� �� ������
				Size--;
			}
			//if (Temp->pNext = nullptr)break;
		}
		if (Head->Data == Value) pop_front();
	}
	void remove_more_than(T Value)
	{
		for (Element<T>* Temp = Head; Temp->pNext; (Temp->pNext != nullptr&&Temp->pNext->Data != Value) ? Temp = Temp->pNext : Temp)
		{
			if (Temp->pNext->Data > Value)//���� �������� ���������� �������� ������ ,�� ������� ��������� �������
			{
				//��� �����:
				Element<T>* Buffer = Temp->pNext;//��������� ����� ����������(����������) ��������
				Temp->pNext = Temp->pNext->pNext;//��������� ������� �� ������
				delete Buffer;//������� ������� �� ������
				Size--;
			}
			//if (Temp->pNext = nullptr)break;
		}
		if (Head->Data == Value) pop_front();
	}

	void remove_less_than()
	{
		;
	}
	void sort()
	{
		for (Element<T>* selected = Head; selected; selected = selected->pNext)
		{
			for (Element<T>*search = selected->pNext; search; search = search->pNext)
			{
				if (search->Data < selected->Data)Exchange(search->Data, selected->Data);
			}
		}
	}
	void reverse()
	{
		Element<T>* Temp = Head;//������� ��������� � ������� � ������
		while (Temp->pNext->pNext != nullptr)Temp = Temp->pNext;
		delete Temp->pNext;
		Temp->pNext = nullptr;
		Size--;
	}

};
void main()
{
	setlocale(LC_ALL, "Russian");

	/*Element e1(123);
	cout << e1.GetData() << "\t" << e1.GetpNext() << endl;
	List l1;

	List train;//������� ������ ������

	int n;
	cout << "������� ���������� ��������� ������:\t"; cin >> n;
	for (int i = 0; i < n; i++)
	{
	train.push_front(rand() % 100);
	}
	train.Print();
	for (int i = 0; i < n; i++)
	{
	train.push_back(rand() % 100);
	}
	train.push_front(122);
	train.push_back(222);
	train.Print();

	int Index, Data;
	cout << "������� �������� ������������ ��������:\t"; cin >> Data;
	cout << "������� ������ ������������ ��������:\t"; cin >> Index;
	train.Insert(Data, Index);
	train.pop_back();
	train.Print();
	int Index;
	cout << "������� ������ ��������, ������� ���� ������� �� ������: ";	cin >> Index;
	train.Erase(Index);
	train.Print();


	List train2;
	train.Print();
	train2 = train;

	train2.Print();*/
	int n; cout << "������� ���������� ��������� ������:\t";
	cin >> n;
	int Data;//�������� ���������
//	int Index;//������ ���������

#ifdef BaseCheck
#endif

#ifdef ConstructorsCheck
	List train1 = n;

	for (int i = 0; i < train1.getSize(); i++)
	{
		train1[i] = rand() % 100;
	}
	//cout << "________________\n" << endl;
	train1.Print();
	//cout << "\n________________" << endl;
	//train1.pop_front();
	//cout << "\n________________" << endl;
	/*for (int i = 0; i < train1.getSize(); i++)
	{
	cout << train1[i] << tab;
	}*/
	//cout << "\n________________" << endl;
	List train2 = n;
	for (int i = 0; i < train2.getSize(); i++)
	{
		train2[i] = rand() % 100;
	}
	train2.Print();

	List train3 = n;
	train3 = train1 + train2;
	train3.Print();
	//train2 = train1;
	//cout << "________________\n" << endl;
	//train2.Print();
	//cout << "________________\n" << endl;

#endif
#ifdef HardcorCheck
	List/*<int>*/<double> train;
	for (int i = 0; i < n; i++)
	{
		train.push_back(double(rand() % 1000)/100);
	}
	train.Print();
	cout << "������� ��������, ������� ����� ������� �� ������"; cin >> Data;
	train.remove_value(Data);
	//train.reverse();
	train.Print();
#endif
}