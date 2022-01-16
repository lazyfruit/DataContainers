#include<iostream>
#include<array>
#include<vector>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define line "\n____________________________________________________________________________________\n"

//#define STL_ARRAY
#define STL_VECTOR

void main()
{
	setlocale(LC_ALL, "");

#ifdef STL_ARRAY
	cout << tab << "\n______Array______" << endl;
	array<int, 5> arr = { 3, 5, 8, 13, 21 };
	for (int i = 0; i < arr.size(); i++)
	{
		cout << "Массив: " << arr[i] << tab;
	}
	cout << endl;
#endif // STL_ARRAY

#ifdef STL_VECTOR
	cout << "\n______Vector______" << endl;
	vector<int> vec = {0, 1, 1, 2, 3, 5, 8, 13, 21, 34};
	cout << "Size: " << tab tab << vec.size() << endl;
	cout << "Capasity: " << tab << vec.capacity() << endl;	//Есть только у vector'а
	cout << "MaxSize: " << tab << vec.max_size() << endl;
	cout << sizeof(vec) << endl;
	
	int* data = vec.data();//Объявлено для просмотра в отладчике
	vec.push_back(55);
	data = vec.data();
	vec.push_back(89);
	try //Отслеживает исключения
	{//Исключительная ситуация - ошибка на этапе выполнения, которая приводет к прерыванию выполнения программы.
		for (int i = 0; i < /*vec.size()*/ vec.capacity() /*-1*/; i++)
		{
			//cout << vec[i] << tab;
			//cout << vec.at(i) << tab;
			cout << *(data + i) << tab;
		}
		cout << endl;
		//subscript - индексирование
	}
	catch (const std::exception& e)
	{
		cerr << e.what() << endl;
	}
	cout << "Size: " << tab tab << vec.size() << endl;
	cout << "Capasity: " << tab << vec.capacity() << endl;	//Есть только у vector'а
	cout << "MaxSize: " << tab << vec.max_size() << endl;
	cout << sizeof(vec) << endl;

	cout << "\n______Vector<Vector>______" << endl;
	vector<vector<int>> vec2;
	cout << "Size: " << tab tab << vec2.size() << endl;
	cout << "Capasity: " << tab << vec2.capacity() << endl;	//Есть только у vector'а
	cout << "MaxSize: " << tab << vec2.max_size() << endl;
	cout << sizeof(vec2) << endl;

#endif // STL_VECTOR

}