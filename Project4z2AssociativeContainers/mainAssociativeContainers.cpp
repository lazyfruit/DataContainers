#include<iostream>
#include<string>
#include<set>
#include<map>
#include<list>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

//#define STL_SET
//#define STL_MAP

void main()
{
	setlocale(LC_ALL, "");
#ifdef STL_SET
	std::set<int> set1 = { 50, 25, 75, 16, 32, 64, 80, 16, 64, 50, 25, 88 };
	for (std::set<int>::iterator it = set1.begin(); it != set1.end(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	cout << set1.size() << endl;
	cout << set1.max_size() << endl;
	for (std::set<int>::reverse_iterator it = set1.rbegin(); it != set1.rend(); it++)
	{
		cout << *it << tab;
	}
	cout << endl;
	int value;
	//cout << "Ââåäèòå äîáàâëÿåìîå çíà÷åíèå: "; cin >> value;
	//set1.insert(set1.end(), value);
	//set1.insert({ 3,5,8,13,21,34,55,89 });

	for (int i : set1)cout << i << tab; cout << endl;
	cout << "Ââåäèòå óäàëÿåìîå çíà÷åíèå: "; cin >> value;
	set1.erase(value);
	for (int i : set1)cout << i << tab; cout << endl;
#endif // STL_SET

#ifdef STL_MAP
	std::map<int, std::string> week =
	{
		pair<int, std::string>(0, "Sunday"),
		pair<int, std::string>(1, "Monday"),
		pair<int, std::string>(2, "Tewsday"),
		pair<int, std::string>(3, "Wednesday"),
		pair<int, std::string>(4, "Thursday"),
		pair<int, std::string>(5, "Friday"),
		pair<int, std::string>(6, "Saturday"),
		pair<int, std::string>(1, "Sunday"),
		pair<int, std::string>(1, "Monday")
	};
	for (std::map<int, std::string>::iterator it = week.begin(); it != week.end(); ++it)
	{
		cout << it->first << tab << it->second << endl;
	}
#endif // STL_MAP

	std::map<std::string, std::list<std::string>> dictionary =
	{
		pair<std::string, std::list<std::string>>("buddy", std::list<std::string>{"äðóæèùå", "ïðèÿòåëü"}),
		pair<std::string, std::list<std::string>>("keen",  std::list<std::string>{"îñòðûé","÷óâñòâèòåëüíûé","ïðîíèöàòåëüíûé","ñîîáðàçèòåëüíûé"}),
		pair<std::string, std::list<std::string>>("wage",  std::list<std::string>{"çàðïëàòà"}),
		pair<std::string, std::list<std::string>>("mutual",std::list<std::string>{"âçàèìíûé","îáîþäíûé","ñîîòâåòñòâåííûé"}),
		pair<std::string, std::list<std::string>>("space", std::list<std::string>{"êîñìîñ","ïðîñòðàíñòâî"})
	};

	for (std::map<std::string, std::list<std::string>>::iterator it = dictionary.begin(); it != dictionary.end(); ++it)
	{
		cout << it->first << ":\t";
		for (std::list<std::string>::iterator l_it = it->second.begin(); l_it != it->second.end(); ++l_it)
		{
			cout << *l_it << ",";
		}
		cout << "\b;\n";
	}
}