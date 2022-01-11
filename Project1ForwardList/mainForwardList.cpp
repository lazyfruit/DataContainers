#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;		//�������� ��������
	Element* pNext;	//����� ���������� ��������
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
	Element* Head;		//��������� �� ��������� ������� ������. �������� ������ ����� � ������.
public:
	ForwardList()
	{
		this->Head = nullptr;	//���� "������" ��������� �� 0, ������ ������ ����
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//		Adding elements
	void push_front(int Data)
	{
		//1. ������� �������
		Element* New = new Element(Data);
		//2. ������������ ����� ������� � ������
		New->pNext = Head;
		//3. ��������� ������ �� ����� �������
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) //����������� ���
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
			cout << "Error: ����� �� ������� ������." << endl;
			return;
		}
		if (Index == 0 || Head == nullptr)return push_front(Data);	//��������� ���
		//0. ������� �� ������� ��������
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) Temp = Temp->pNext;
		//1. ������� ����� �������
		Element* New = new Element(Data);
		//2. ����������� ����� ������� � ������
		New->pNext = Temp->pNext;
		//3. �������� ������� � ������
		Temp->pNext = New;
		size++;
	}
	//		Erasing element:
	void pop_front()
	{
		//1. ���������� ����� ���������� ��������
		Element* Erased = Head;
		//2. ��������� ������ ������� �� ������
		Head = Head->pNext;
		//3. ������� ������ �������
		delete Erased;
		size--;
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();	//����������� ���
		//1. ������� �� �������������� ��������
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2. ������� ��������� ������� �� ������
		delete Temp->pNext;
		//3. �������� ����� ���������� �������� ����� (nullptr)
		Temp->pNext = nullptr;
		size--;
	}

	//		Methods
	void print()const
	{
		Element* Temp = Head;		//Temp - ��� ��������\
		�������� - ��� ���������, ��� ������ �������� ����� �������� ������ � ���������
		while (Temp != nullptr)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;		//������� �� ��������� �������
		}
		cout << "���������� ��������� � ������: " << size << endl;
		cout << "����� ���������� ���������: " << Head->count << endl;
	}
};

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int listSize;		//������ ������
	cout << "������� ������ ������: "; cin >> listSize;

	ForwardList list;
	//list.~ForwardList;

	for (int i = 0; i < listSize; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();

	int index;
	int value;
	cout << "������� ������ ������������ ��������: "; cin >> index;
	cout << "������� �������� ������������ ��������: "; cin >> value;
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