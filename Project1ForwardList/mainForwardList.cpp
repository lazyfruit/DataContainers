#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define line "\n____________________________________________________________________________________\n"
//#define DEBUG

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static int count;
public:
	int get_Data()const
	{
		return Data;
	}
	Element* get_pNext()const
	{
		return pNext;
	}
	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
};

int Element::count = 0;	//Статические переменные могут быть проинициализированы только за классом

//Element* operator++(Element*& Temp)
//{
//return Temp = Temp->get_pNext();
//}

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
	}
	//	Operators
	Iterator& operator++()	//Prefix increment
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator operator++(int)//Suffix increment
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}

	const int& operator*()const
	{
		return Temp->Data;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}

	operator bool()const
	{
		return Temp;
	}
};

class ForwardList
{
	Element* Head;	//Указывает на начальный элемент списка.\
					Является точкой входа в список.
	size_t size;
public:
	Element* get_Head()const
	{
		return Head;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	//	Constructors
	ForwardList()
	{
		this->Head = nullptr;	//Если "голова" указывает на 0, значит список пуст
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		//begin()	- возвращает итератор на начальный элемент контейнера
		//end()		- возвращает итератор на конец контейнера
		for (const int* it = il.begin(); it != il.end(); it++)
		{
			//it - итератор для проходжения по il (initializer_list)
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other)
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		cout << "LCopyConstructor:" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
		cout << line << endl;
	}
	//	Operators
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
		cout << "LCopyAssignment:" << this << endl;
		return *this;
	}
	//	Adding elements
	void push_front(int Data)
	{
		//1) Создаем элемент:
		//Element* New = new Element(Data, Head);
		//2) Присоединяем новый элемент к списку:
		//New->pNext = Head;
		//3) Переносим Голову на Новый элемент:
		//Head = New;
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		Element* Temp = Head;
		while (Temp->pNext)
			Temp = Temp->pNext;
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error: Выход за пределы списка." << endl;
			return;
		}
		if (Index == 0 || Head == nullptr)return push_front(Data);

		//0) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//Осуществляем вставку нового элемента в список:
		//2) Привязываем новый элемент к списку:
		//New->pNext = Temp->pNext;
		//3) Включаем элемент в список:
		//Temp->pNext = New;

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	//	Erasing element:
	void pop_front()
	{
		//1) Запоминвем адрес удаляемого элемента:
		Element* Erased = Head;
		//2) Исключаем элемент из списка:
		Head = Head->pNext;
		//3) Удаляем элемент из списка:
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		//1) Доходим до предпоследнего элемента:
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//Мы оказались в предпоследнем элементе

		//2) Удаляем последний элемент из памяти:
		delete Temp->pNext;

		//3) "Забываем" об удаленном элементе, то есть затираем его адрес нулем:
		Temp->pNext = nullptr;
		//Теперь Temp является последним элементом списка.
		size--;
	}
	void erase(int Index)
	{
		if (Index > Head->count)
		{
			cout << "Error: Выход за пределы списка!";
			return;
		}
		if (Index == 0 || Head == nullptr)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;
	}
	//	Methods
	void print()const
	{
		/*Element* Temp = Head;	//Temp - это итератор.
		//Итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;	//Переход на следующий элемент.
		}*/
		//for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		//	cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		for (Iterator Temp = Head; Temp != nullptr; Temp++)
			cout << *Temp << tab;
		cout << endl;
		cout << "Количество элементов в списке: " << size << endl;
		cout << "Общее количество элементов: " << Head->count << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;	//Копируем левый список в результат
	//for (Element* Temp = right.get_Head(); Temp; Temp = Temp->get_pNext())//Проходим по правому списку
	//	result.push_back(Temp->getData());//и добавляем все его элементы в конец результата
	for (Iterator Temp = right.get_Head(); Temp; Temp++)
	{
		result.push_back(*Temp);
	}
	return result;
}

//#define BASE_CHECK
//#define COUNT_CHECK
//#define COPY_METHODS_CHECK
//#define OPERATOR_PLUS_CHECK
//#define RANGE_BASED_FOR_ARR

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	/*ForwardList list;
	list.~ForwardList();*/

	int n;	//Размер списка
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
	/*list.pop_back();
	list.print();*/
	/*list.push_back(123);
	list.print();
	list.pop_back();
	list.print();*/

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
#endif // BASE_CHECK

#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);

	ForwardList list2;
	list2.push_back(34);
	list2.push_back(55);
	list2.push_back(89);

	list1.print();
	list2.print();
#endif // COUNT_CHECK

#ifdef COPY_METHODS_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1 = list1;
	list1.print();

	//ForwardList list2 = list1;	//CopyConstructor
	ForwardList list2;
	list2 = list1;	//CopyAssignment
	list2.print();
#endif // COPY_METHODS_CHECK

#ifdef OPERATOR_PLUS_CHECK
	int a = 2;
	int b = 3;
	int c = a + b;

	ForwardList list1 = { 3,5,8,13,21 };
	list1.print();
	ForwardList list2 = { 34,55,89 };
	list2.print();
	ForwardList list3 = list1 + list2;
	list3.print();
#endif // OPERATOR_PLUS_CHECK

#ifdef RANGE_BASED_FOR_ARR
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
		cout << arr[i] << tab;
	cout << endl;

	//Range-based for (foreach):
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
	
#endif // RANGE_BASED_FOR_ARR

	ForwardList list = { 3, 5, 8, 13, 21 };
	cout << "\n-------------------------------------------\n";
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
	cout << "\n-------------------------------------------\n";
}