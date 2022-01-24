#include<iostream>
#include<string>
#include<map>
#include<list>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"

class Crime
{
	std::string crime;
	std::string place;
public:
	const std::string& get_crime() const
	{
		return crime;
	}
	const std::string& get_place() const
	{
		return place;
	}
	void set_crime(std::string& crime)
	{
		this->crime = crime;
	}
	void set_place(std::string& place)
	{
		this->place = crime;
	}
	Crime(std::string& crime, std::string& place)
	{
		this->crime = crime;
		this->place = place;
		cout << "CrimeConstructor" << this << endl;
	}
	~Crime()//~, клавиша Tab - автоматически дописывает название деструктора
	{
		cout << "CrimeDestructor" << this << endl;
	}
	std::ostream& print(std::ostream& os)
	{
		return os << crime << ", " << place;
	}
	std::istream& scan(std::istream& is)
	{
		std::getline(is, crime, ',');
		std::getline(is, place, '.');
		return is;
	}
};

std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return obj.print(os);
}

void print(const std::map<std::string, std::list<Crime>>& base);

void main()
{
	setlocale(LC_ALL, "");

	std::map<std::string, std::list<Crime>> base =
	{
		std::pair<std::string, std::list<Crime>>("m77ko", std::list<Crime>{Crime("Превышение скорости", "Улица Ленина"), Crime("Проезд на красный сигнал светофора", "Улица Маяковского")}),
		std::pair<std::string, std::list<Crime>>("b510ma", std::list<Crime>{Crime("Парковка в неположенном месте", "ТЦ Экватор")}),
		std::pair<std::string, std::list<Crime>>("a213bb", std::list<Crime>{Crime("Пересечение двойной сплошной разметки", "Южное шоссе")})
	};
	print(base);
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	for (std::map<std::string, std::list<Crime>>::const_iterator it = base.begin(); it != base.end(); ++it)
	{
		cout << it->first << ":\n";
		for (std::list<Crime>::const_iterator l_it = it->second.begin(); l_it != it->second.end(); ++l_it)
		{
			cout << *l_it << endl;
		}
	}
}