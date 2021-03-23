
#include <boost/filesystem/operations.hpp>
#include <boost/system/config.hpp>
//#include <filesystem>
#include <fstream>
#include <iomanip>
#include <istream>
#include <locale>
#include <ostream>
#include <iostream>
#include <string>
#include <vector>

#include "json.hpp"

using nlohmann::json;
using namespace boost::filesystem;
using namespace std;

struct Human {
    string name;
    unsigned int age;
    double weight;

    friend istream& operator>> (istream &in, Human &human);
};

std::istream& operator>> (istream &in, Human &human)
{
    in >> human.name;
    in >> human.age;
    in >> human.weight;
    return in;
}

int main(int argc, char ** argv)
{

    vector <Human> human(3);

    for (size_t i = 0; i < human.size(); i++) {
        cout << "Введите информацию о человеке " << i + 1 << ": ";
        cin >> human[i];
    }

	json js;

    boost::filesystem::path p = boost::filesystem::current_path();
    boost::filesystem::create_directory(p / "task4");
    boost::filesystem::current_path(p/"task4");

    string file_name;

    for (size_t i = 0; i < human.size(); i++) {
        file_name= "json_" + to_string(i + 1) + ".txt";
        ofstream out(file_name);

        if (!out.is_open()) {
            cerr << "Can not open: " << file_name << endl;
            return EXIT_FAILURE;
        }

        js["name"] = human[i].name;
        js["age"] = human[i].age;
        js["weight"] = human[i].weight;

        for (auto iterator = js.begin(); iterator != js.end(); ++iterator) {
            out << iterator.key() << ": " << iterator.value() << "\n";
        }

        out.close();
    }

	return 0;
}