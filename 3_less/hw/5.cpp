#include <iostream>
#include <string>
#include <clocale>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/random_access_index.hpp>

using namespace boost::multi_index;
using namespace std;
struct Information_about_person
{
	string name, phone, house;
	struct Name {};
	struct Phone {};
	struct House {};
}; 

typedef Information_about_person Info;

typedef boost::multi_index_container< Info,
        indexed_by< ordered_unique< tag<Info::Name>, member<Info, std::string, &Info::name> >, 
        ordered_non_unique< tag<Info::Phone>, member<Info, std::string, &Info::phone> >,
        ordered_non_unique< tag<Info::House>, member<Info, std::string, &Info::house> > >
        > Contacts;

void find_using_name (Contacts& persons); 
void find_using_phone (Contacts& persons);
void find_using_adress (Contacts& persons); 
void sort_by_name (Contacts& persons);

int main(int argc, char** argv)
{
	Contacts persons { {"Person2", "22-22-22", "2"},{"Person1", "11-11-11", "1"}, {"Person3", "33-33-33", "3"}, {"Person4", "44-44-44", "4"}, {"Person5", "55-55-55", "5"}};

    find_using_name(persons);

    cout << endl;

    find_using_phone(persons);

    cout << endl;

    find_using_adress(persons);

    cout << endl;

    sort_by_name (persons);

	return 0;
}

void sort_by_name (Contacts& persons) {

    size_t count = 1;
	for (auto it = persons.begin(); it != persons.end(); ++it)
	{
		cout << "Пользователь №" << count << endl;
		cout << "Имя: " << (*it).name << ", номер телефона: " << (*it).phone << ", дом: " << (*it).house << ";" << endl;
		count++;
	}
}

void find_using_adress (Contacts& persons) {

    cout << "Поиск по номеру дома" << endl;
	string house;
    cin >> house;
	Contacts::index<Info::House>::type::iterator it_2, it_3;
	tie(it_2, it_3) = persons.get<Info::House>().equal_range(house);
	while (it_2 != it_3)
	{
		cout << "Имя: " << (*it_2).name << endl;
        cout << "Номер телефона: " << (*it_2).phone << endl;
		++it_2;
	}
}

void find_using_phone (Contacts& persons) {

    std::cout << "Поиск по номеру телефона" << std::endl;
	string phone;
    cin >> phone;
	Contacts::index<Info::Phone>::type::iterator it_1, it_2;
	tie(it_1, it_2) = persons.get<Info::Phone>().equal_range(phone);
	while (it_1 != it_2)
	{
		cout << "Имя: " << (*it_1).name << endl;
        cout << "Номер дома: " << (*it_1).house << endl;
		++it_1;
	}
}

void find_using_name (Contacts& persons) {
    cout << "Введите имя человека, которого хотите найти:" << endl;
    string name;
    cin >> name;
	typedef Contacts::index<Info::Name>::type List;
	const List& ls = persons.get<Info::Name>();
	List::const_iterator it = ls.find(name);
	if (it != ls.end())
	{
        cout << "Номер телефона: " << (*it).phone << endl;
		cout << "Номер дома: " << (*it).house << endl;
	}
}