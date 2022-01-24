#include<iostream>
#include<Windows.h>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define line "\n___________________________________________________\n"

class Tree
{
protected:
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
			cout << "EDestrcutor:\t" << this << endl;
		}
		bool is_leaf()const
		{
			return pLeft == pRight;
		}
		friend class Tree;
		friend class UniqueTree;
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
	Tree(const std::initializer_list<int>& il) :Tree()
	{
		for (int i : il)insert(i, Root);
	}
	Tree(const Tree& other) :Tree()
	{
		copy(other.Root);
		cout << "CopyConstructor:\t" << this << endl;
	}
	Tree(Tree&& other)
	{
		this->Root = other.Root;
		other.Root = nullptr;
		cout << "MoveConstructor:\t" << this << endl;
	}
	~Tree()
	{
		Clear(Root);
		Root = nullptr;
		cout << "TDestructor:\t" << this << endl;
		cout << "\n-------------------------------------\n";
	}


	void insert(int Data)
	{
		insert(Data, this->Root);
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	int minValue()const
	{
		return minValue(this->Root);
	}
	int maxValue()const
	{
		return maxValue(this->Root);
	}
	int Count()const
	{
		return Count(Root);
	}
	int Sum()const
	{
		return Sum(Root);
	}
	double Avg()const
	{
		return (double)Sum(Root) / Count(Root);
	}
	void Clear()
	{
		Clear(Root);
		Root = nullptr;
	}

	int depth()const
	{
		return depth(this->Root);
	}
	void copy(Element* Root)
	{
		if (Root == nullptr) return;
		insert(Root->Data, this->Root);
		copy(Root->pLeft);
		copy(Root->pRight);
	}
	void print()const
	{
		print(this->Root);
		cout << endl;
	}
	void print(int depth, int interval)const
	{
		print(this->Root, depth, interval);
		cout << endl;
	}
	void tree_print()
	{
		tree_print(0);
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
				Root->pLeft = new Element(Data);//Добавляем элемент прямо сюда.
			else//В противном случае
				insert(Data, Root->pLeft);	//идем налево, и ищим место, 
											//куда добавить элемент.
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->is_leaf())	//Если элемент является листком
			{
				//то его можно удалять
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (Count(Root->pLeft) > Count(Root->pRight))//Если в левой ветке больше элементов чем в правой ветке
				{
					Root->Data = maxValue(Root->pLeft);	//то заменяем значение удаляемого элемента максимальным значением в левой ветке
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else//В противном случае
				{
					Root->Data = minValue(Root->pRight);//заменяем значение удаляемого элемента минимальным значение в правой ветке
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}

	int minValue(Element* Root)const
	{
		if (Root->pLeft == nullptr)return Root->Data;
		return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pRight);*/

		//return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}

	int Count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return Count(Root->pLeft) + Count(Root->pRight) + 1;*/
		//return Root ? Count(Root->pLeft) + Count(Root->pRight) + 1 : 0;
		return !Root ? 0 : Count(Root->pLeft) + Count(Root->pRight) + 1;
	}
	int Sum(Element* Root)const
	{
		return Root ? Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data : 0;
	}
	void Clear(Element* Root)
	{
		if (Root == nullptr)return;
		Clear(Root->pLeft);
		Clear(Root->pRight);
		delete Root;
	}

	int depth(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1 : depth(Root->pRight) + 1;
	}



	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	void print(Element* Root, int depth, int interval)const
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		static CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		if (Root == nullptr || depth == -1)return;
		/*{
			csbi.dwCursorPosition.X += interval;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
			return;
		}*/
		//if (depth == 1 && Root->pLeft == nullptr)cout << "  " << tab;
		//if (depth == 1 && Root->pRight == nullptr)cout << "  " << tab;
		if (depth == 1 && Root->pLeft == nullptr)
		{
			csbi.dwCursorPosition.X += interval;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
		}
		print(Root->pLeft, depth - 1, interval);
		//cout << tab;
		//static int cursor_x = csbi.dwCursorPosition.X;
		//static int cursor_y = csbi.dwCursorPosition.Y;
		if (depth == 0)
		{
			cout << Root->Data /*<< tab*/;
			csbi.dwCursorPosition.X += interval;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
		}
		//for (int i = 0; i < (this->depth() - depth)*1; i++)cout << tab;
		int min_distance = 4;
		//cout.width(min_distance*(this->depth() - depth));
		//if (depth == 1 && Root->pRight == nullptr)cout << "  " << tab;
		//for (int i = 0; i < (this->depth() - depth)*1; i++)cout << tab;
		if (depth == 1 && Root->pRight == nullptr)
		{
			csbi.dwCursorPosition.X += interval;
			SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
		}
		print(Root->pRight, depth - 1, interval);
		//cout << tab;
	}
	void tree_print(int depth)
	{
		if (depth == this->depth())return;
		int min_distance = 8;
		//cout.width(min_distance*(this->depth() - depth));
		//for (int i = 0; i < (this->depth() - depth) * (this->depth() - depth); i++)	cout << tab;

		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(hConsole, &csbi);
		static int start_x = csbi.dwMaximumWindowSize.X / 2;
		static int start_y = csbi.dwCursorPosition.Y;
		static COORD position = { start_x, start_y };
		SetConsoleCursorPosition(hConsole, position);
		static int interval = start_x * 2;
		print(depth, interval);
		//for (int i = 0; i < (this->depth() - depth) * (this->depth() - depth); i++)	cout << tab;
		//cout << endl;
		position.X /= 2;
		position.Y += 5;
		interval /= 2;
		tree_print(depth + 1);
	}
};

Tree operator+(const Tree& left, const Tree& right)
{
	Tree res = left;
	res.copy(right.getRoot());
	return res;
}

class UniqueTree : public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)//Если есть место для добавления элемента,
				Root->pLeft = new Element(Data);//Добавляем элемент прямо сюда.
			else//В противном случае
				insert(Data, Root->pLeft);	//идем налево, и ищим место, 
											//куда добавить элемент.
		}
		else if (Data > Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

//#define BASE_CHECK
//#define MOVE_SEMANTIC

void main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 150,44 };
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите количество элементов: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве:  " << tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
	cout << "Количество элементов в дереве:  " << tree.Count() << endl;
	cout << "Сумма элементов дерева:  " << tree.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.Avg() << endl;

	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << endl;
	cout << "Минимальное значение в дереве:  " << u_tree.minValue() << endl;
	cout << "Максимальное значение в дереве: " << u_tree.maxValue() << endl;
	cout << "Количество элементов в дереве:  " << u_tree.Count() << endl;
	cout << "Сумма элементов дерева:  " << u_tree.Sum() << endl;
	cout << "Среднее арифметическое элементов дерева: " << u_tree.Avg() << endl;
	u_tree.Clear();
	u_tree.print();
#endif // BASE_CHECK

	Tree tree = { 50, 25, 75, 16, 32, 64, 80, 8, 18, 48, 77, 85/*, 4,11,69,87,44 ,17,19*/ };
	tree.print();
	int value;
	//cout << "Введите удавляемое значение: "; cin >> value;
	//tree.erase(value);
	//tree.print();
	cout << "Глубина дерева: " << tree.depth() << endl;
	//tree.print(3);
	tree.tree_print();

#ifdef MOVE_SEMANTIC
	Tree oak = { 67, 34, 88, 22, 53 };
	oak.print();
	cout << line;
	Tree res = tree + oak;
	cout << line;
	res.print();
#endif // MOVE_SEMANTIC
}