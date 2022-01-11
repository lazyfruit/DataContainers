#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;		//Значение элемента
	Element* pNext;	//Адрес следующего элемента
	static int count;
public:
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
};

int Element::count = 0;

class ForwardList
{
	Element* Head;		//Указывает на начальный элемент списка. Является точкой входа в список.
public:
	ForwardList()
	{
		this->Head = nullptr;	//Если "голова" указывает на 0, значит список пуст
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//		Adding elements
	void push_front(int Data)
	{
		//1. Создаем элемент
		Element* New = new Element(Data);
		//2. Присоединяем новый элемент к списку
		New->pNext = Head;
		//3. Переносим голову на новый элемент
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) //Проверочный код
		{
			push_front(Data);
		}
		Element* Temp = Head;
		while (Temp->pNext)Temp = Temp->pNext;
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
		if (Index == 0 || Head == nullptr)return push_front(Data);	//Проверяем код
		//0. Доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		//1. Создаем новый элемент
		Element* New = new Element(Data);
		//2. Привязываем новый элемент к списку
		New->pNext = Temp->pNext;
		//3. Включаем элемент в список
		Temp->pNext = New;
		size++;
	}
	//		Erasing element:
	void pop_front()
	{
		//1. Запоминаем адрес удаляемого элемента
		Element* Erased = Head;
		//2. Исключаем первый элемент из списка
		Head = Head->pNext;
		//3. Удаляем первый элемент
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();	//Проверочный код
		//1. Доходим до предпоследнего элемента
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2. Удаляем последний элемент из памяти
		delete Temp->pNext;
		//3. Заменяем адрес удаленного элемента нулем (nullptr)
		Temp->pNext = nullptr;
		size--;
	}

	//		Methods
	void print()const
	{
		Element* Temp = Head;		//Temp - это итератор\
		Итератор - это указатель, при помощи которого можно получить доступ к элементам
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;		//Переход на следующий элемент
		}
		cout << "Количество элементов в списке: " << size << endl;
		cout << "Общее количество элементов: " << Head->count << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int listSize;		//Размер списка
	cout << "Введите размер списка: "; cin >> listSize;

	ForwardList list;
	//list.~ForwardList;

	for (int i = 0; i < listSize; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.print();
#endif // BASE_CHECK

	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	
	ForwardList list2;
	list1.push_back(33);
	list1.push_back(55);
	list1.push_back(89);

	list1.print();
	list2.print();
}