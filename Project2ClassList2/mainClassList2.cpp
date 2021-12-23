﻿#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

template<typename T>
class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail;//Объявляем два указателя сразу же после описания класса
	//Эти указатели будут переменными членами класса List.
	size_t size;	//Размер списка
	class BaseIterator
	{
	protected:
		Element* Temp;
	public:
		BaseIterator(Element* Temp);
		~BaseIterator();
		bool operator==(const BaseIterator& other)const;
		bool operator!=(const BaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator :public BaseIterator
	{
	public:
		ConstIterator(Element* Temp);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp)
		{

		}
		~Iterator()
		{

		}
		T& operator*();
	};
	class ConstReverseIterator :public BaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();
	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();
	//		Operators:
	List<T>& operator=(const List<T>& other);
	//		Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);
	//		Removing elements:
	void pop_front();
	void pop_back();
	//		Methods:
	void print()const;
	void reverse_print()const;
};

//7. Класс ReverseIterator:
template<typename T>
T& List<T>::ReverseIterator::operator*()
{
	return BaseIterator::Temp->Data;
}
//7. Класс ReverseIterator

//6. Класс ConstReverseIterator:
template <typename T>
List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>
List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template <typename T>
typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}
template <typename T>
typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}
template <typename T>
typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}
//6. Класс ConstReverseIterator

//5. Класс Iterator:
template <typename T>
T& List<T>::Iterator::operator*()
{
	return BaseIterator::Temp->Data;
}
//5. Класс Iterator

//4. Класс ConstIterator:
template<typename T>
List<T>::ConstIterator::ConstIterator(Element* Temp) :BaseIterator(Temp)
{
#ifdef DEBUG
	cout << "IConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>
List<T>::ConstIterator::~ConstIterator()
{
#ifdef  DEBUG
	cout << "IDestructor:\t" << this << endl;
#endif //  DEBUG

}
template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return *this;
}
template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pNext;
	return old;
}
template<typename T>
typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return *this;
}
template<typename T>
typename List<T>::ConstIterator List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	BaseIterator::Temp = BaseIterator::Temp->pPrev;
	return old;
}
//4. Класс ConstIterator

//3. Класс BaseIterator:
template<typename T>
List<T>::BaseIterator::BaseIterator(Element* Temp) :Temp(Temp)
{
#ifdef DEBUG
	cout << "IConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>
List<T>::BaseIterator::~BaseIterator()
{
#ifdef DEBUG
	cout << "IDestructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T>
bool List<T>::BaseIterator::operator==(const BaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T>
bool List<T>::BaseIterator::operator!=(const BaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T>
const T& List<T>::BaseIterator::operator*()const
{
	return Temp->Data;
}
//3. Класс BaseIterator

//2. Класс Element:
template<typename T>
List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :
	Data(Data), pNext(pNext), pPrev(pPrev)
{
	cout << "EConstructor:\t" << this << endl;
}
template<typename T>
List<T>::Element::~Element()
{
	cout << "EDestructor:\t" << this << endl;
}
//2. Класс Element

//1. Класс List:
template <typename T>
typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template <typename T>
typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template <typename T>
typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template <typename T>
typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template <typename T>
typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}
template <typename T>
typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}
template <typename T>
typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}
template <typename T>
typename List<T>::ConstReverseIterator List<T>::crend()const//c-потому что const
{
	return nullptr;
}
//		Constructors:
template <typename T>
List<T>::List()
{
	Head = Tail = nullptr;	//Если список пуст, его Голова и Хвост указывают на 0
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template <typename T>
List<T>::List(const std::initializer_list<T>& il) :List()
{
	cout << typeid(il.begin()).name() << endl;;
	for (int const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template <typename T>
List<T>::List(const List<T>& other) :List()
{
	//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
	*this = other;	//Из конструктора копирования вызываем оператор присваивания
	cout << "LCopyConstructor:\t" << this << endl;
}
template <typename T>
List<T>::~List()
{
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
	cout << "\n-------------------------------------\n";
}
//		Operators:
template <typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)this->push_back(Temp->Data);
	cout << "LCopyAssignment:\t" << this << endl;
	return *this;
}
//		Adding elements:
template <typename T>
void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		//Когда в списке появляется первый элемент, 
		//он одновременно является и Головой и Хвостом.
		Head = Tail = new Element(Data);
		size++;
		return;
	}
	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template <typename T>
void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)return push_front(Data);
	Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	size++;
}
template <typename T>
void List<T>::insert(T Data, int Index)
{
	if (Index >= size)
	{
		cout << "Error: Выход за пределы списка!" << endl;
		return;
	}

	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	size++;
}
//		Removing elements:
template <typename T>
void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		size--;
		return;
	}
	Head = Head->pNext;
	delete Head->pPrev;
	Head->pPrev = nullptr;
	size--;
}
template <typename T>
void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
//		Methods:
template <typename T>
void List<T>::print()const
{
	cout << "Head:\t" << Head << endl;
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Tail:\t" << Tail << endl;
	cout << "Количество элементов списка: " << size << endl;
}
template <typename T>
void List<T>::reverse_print()const
{
	cout << "Tail:\t" << Tail << endl;
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Head:\t" << Head << endl;
}
//1. Класс List

template<typename T>
void print_list(const List<T>& list)
{
	for (typename List<T>::ConstIterator it = list.cbegin(); it != list.cend(); it++)
	{
		//*it*=123;//it works
		cout << *it << tab;
	}
	cout << endl;
}
template<typename T>
void reverse_print_list(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
}

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	cout << "\n------------------------------------------------\n";
	/*list.pop_front();
	list.pop_back();*/
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK

	List<int> list = { 3,5,8,13,21 };
	list.print();

	List<int> list1;
	list1 = list;
	//list1.print();
	for (int i : list1)cout << i << tab; cout << endl;

	for (List<int>::ConstReverseIterator rit = list.rbegin(); rit != list.rend(); ++rit)
	{
		cout << *rit << tab;
	}
	cout << endl;
	reverse_print_list(list1);
	print_list(list1);
}