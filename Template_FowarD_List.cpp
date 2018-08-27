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
	T Data;//значение элемента
	Element<T>* pNext;//адресс следующего элемента
	static int Size;//количество элементов
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
	Element<T>* Head;//указатель на адрес нулевого элемента списка
	int Size;//количество элементов списка


public:
	T getSize()
	{
		return this->Size;
	}
	List()
	{
		this->Head = nullptr;//указатель на ноль в голове списка означает что список пустой
		this->Size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(int Size) :List()//конструктор на заданное число элементов
	{
		while (Size--)push_front(0);//а теперь добавим в него Size элементов
	}

	List(const List<T>& other) :List()
	{
		for (Element<T>* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)
			/*Element* Temp = other.Head;*/
			/*while (Temp != nullptr)*///Пока итерратор не равен нулю
		{
			push_back(Temp->Data);//добавляем в наш список значение элемента
		}
		/*Temp = Temp->pNext;*///и переходим к следующему элементу
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
	T &operator[](int Index)//Этот оператор по индексу элемента возврапщает его значение
	{
		if (Index < 0 || Index >= Size)
		{
			cout << "Eror: Вы за пределами списка!";
			/*return 0;*/
			throw 0;
		}
		Element<T>* Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;//доходим до нужного элемента
		return Temp->Data;//и возвращаем его значение
	}
	List<T> &operator=(const List<T>& other)
	{
		Clear();//очищаем список от старых элементов
		for (Element<T>* Temp = other.Head; Temp != nullptr; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "LCopy Assignments:" << tab << this << endl;
		return *this;
	}

	List<T> &operator=(List<T>&& other)
	{
		this->Clear();//очищаем список от старых элементов
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
		Element<T>* New = new Element<T>(Data);//Создали элемент
		New->pNext = Head;//Прицепили его к началу списка
		Head = New;// И сказали что теперь он являеться Головой списка
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
		/*Element* New = new Element(Data);*///Создаем новый элемент
		Element<T>* Temp = Head;//Создаем иттератор и заходим в список
		while (Temp->pNext != nullptr)Temp = Temp->pNext;//Доходим до конца списка
		/*{
		Temp = Temp->pNext;
		*/
		Temp->pNext = new Element<T>(Data);//Когда мы находимся в конце списка "пристёгиваем" новый элемент к последнему 
		Size++;
	}

	void Insert(T Data, int Index)
	{
		if (Index > Size || Index < 0)
		{
			cout << "Error:Вы вышли за пределы списка!" << endl;
			return;
		}
		if (Index == 0)
		{
			push_front(Data);
			return;
		}
		Element<T>* Temp = Head;//создаем элемент
		//добираемся до нового элемента
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
		Element<T>* Temp = Head;//Создаем иттератор и заходим в список
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
		Temp->pNext = Temp->pNext->pNext;//указатель на элемент через 1 элемент
		delete Buffer;
		Size--;
	}
	////////////////////////////Auxiliary methods/////////////////////
	void Print()
	{
		cout << "Адрес списка:\t" << this->Head << endl;
		for (Element<T>* Temp = Head; Temp != nullptr; Temp = Temp->pNext)cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//Element* Temp = Head;//создаем иттератор( это указатель при помощи которго можно получить доступ к элементам структуры данных)
		//while (Temp != nullptr)
		//{
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		//	Temp = Temp->pNext;
		//}
		cout << "-------------------------------------------" << endl;
		cout << "Количество элементов списка: " <</* Element::Size<<Head->Size*/this->Size << endl;
		cout << "-------------------------------------------" << endl;
	}
	void Clear()
	{
		while (Head != nullptr)pop_front();//пока список не пустой Удаляем первый элемент
	}
	///////////////////////////////////////////////HARDCORE////////////////////////
	void remove_value(T Value)
	{
		for (Element<T>* Temp = Head; Temp->pNext; (Temp->pNext != nullptr&&Temp->pNext->Data != Value) ? Temp = Temp->pNext : Temp)
		{
			if (Temp->pNext->Data == Value)//если значение следующего элемента совпало с удаляемым,то удаляем следующий элемент
			{
				//для этого:
				Element<T>* Buffer = Temp->pNext;//сохраняем адрес удаляемого(следующего) элемента
				Temp->pNext = Temp->pNext->pNext;//исключаем элемент из списка
				delete Buffer;//удаляем элемент из памяти
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
			if (Temp->pNext->Data > Value)//если значение следующего элемента больше ,то удаляем следующий элемент
			{
				//для этого:
				Element<T>* Buffer = Temp->pNext;//сохраняем адрес удаляемого(следующего) элемента
				Temp->pNext = Temp->pNext->pNext;//исключаем элемент из списка
				delete Buffer;//удаляем элемент из памяти
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
		Element<T>* Temp = Head;//Создаем иттератор и заходим в список
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

	List train;//создаем пустой список

	int n;
	cout << "Введите количество элементов списка:\t"; cin >> n;
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
	cout << "Введите значение добавляемого элемента:\t"; cin >> Data;
	cout << "Введите индекс добавляемого элемента:\t"; cin >> Index;
	train.Insert(Data, Index);
	train.pop_back();
	train.Print();
	int Index;
	cout << "Введите индекс элемента, который надо удалить из списка: ";	cin >> Index;
	train.Erase(Index);
	train.Print();


	List train2;
	train.Print();
	train2 = train;

	train2.Print();*/
	int n; cout << "Введите количество элементов списка:\t";
	cin >> n;
	int Data;//значение елементов
//	int Index;//индекс элементов

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
	cout << "Введите значение, которое нужно удалить из списка"; cin >> Data;
	train.remove_value(Data);
	//train.reverse();
	train.Print();
#endif
}