#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define razdel "\n--------------------------------------------\n"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
			:Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;	//Познакомили класс Element c классом Tree
	}*Root;	//Корень дерева
public:
	Element* getRoot()const
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
	int minValue()const
	{
		return minValue(this->Root);
	}
	int maxValue()const
	{
		return maxValue(this->Root);
	}
private:
	void insert(int Data, Element* Root)
	{
		//Root - корень поддерева
		//this->Root - корень всего дерева
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)//Если есть место для добавления элемента,
				Root->pLeft = new Element(Data);//Добавляем элемент прямо сюда
			else//В противном случае
				insert(Data, Root->pLeft);//Идем налево и ищем место куда добавить элемент
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}

	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}

	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);*/
		//return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
		return Root->pLeft ? minValue(Root->pLeft) : Root->Data;
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/
		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
};

void main()
{
	setlocale(LC_ALL, "");

	int n;
	cout << "Введите количесто элементов дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
}