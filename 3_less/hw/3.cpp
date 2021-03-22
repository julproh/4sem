#include <iostream>
#include <iomanip>
#include <functional>
#include <vector>
#include <boost/functional/hash.hpp>
#include <ctime>
#include <string>
#include <fstream>
#include <random>
#include <algorithm>

using namespace std;

int N = 1000;

struct Person
{   
    Person () {
        m_name = "name";
        m_age = 0;
    }
    Person(string name, unsigned int age): m_name(name), m_age(age){};
    ~Person() = default;
    string m_name;
	unsigned int m_age;
    float m_weight;
    friend size_t has_value (const Person& h);

};

size_t hash_value(const Person& person) noexcept
{
    size_t seed = 0;
    boost::hash_combine(seed, person.m_age);
    boost::hash_combine(seed, person.m_name);
    //boost::hash_combine(seed, person.m_weight);
    return seed;
}

string Name() {
    auto randchar = []() -> char
    {
        const char charset[] = "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = (sizeof(charset) - 1);
        random_device rd;
        return charset[ rd() % max_index ];
    };
    std::string str(2,0);
    generate_n( str.begin(), 2, randchar );
    return str;
}

int main(int argc, char ** argv)
{
	vector <Person> persons(N);
    vector <int> hashes(N);

    // for (int i = 0 ; i < 200; i ++) {
    //     int r = 0;
    //     srand(time(0) * r++*15);
    //     cout << Name() << endl;
    // }

    int r = 0;
    for (int i = 0; i < N; i++) {
        random_device rd;
        persons[i] = Person(Name(), 30 + (rd() % 75));
        hashes[i] = hash_value(persons[i]);
        cout << persons[i].m_name << " " << persons[i].m_age << " " << hashes[i] << endl;
     }	

    std::string File_ = "out.dat";
    std::ofstream out(File_);

    if (!out.is_open()) {
        std::cerr << "Can not open: " << File_ << std::endl;
        return 1;
    }

    for (unsigned int k = 1; k < N; k++) {
        vector <size_t> dub;
        int count = 0;

        for (int i = 0; i < k - 1; i++) {
            bool fl = true;

            for (int j = 0; j < dub.size(); j++) {
                if (dub[j] == hashes[i]) {
                    fl = false;
                    break;
                }
            }

            if (fl == true) {
                dub.push_back(hashes[i]);

                for (int j = i + 1; j < k; j++) {
                    if (hashes[j] == hashes[i]) {
                        count++;
                    }
                }
            }
        }
        out<< int(k + 1) << "\t" << int(count) << "\n";
    }

    out.close();
	return 0;
}