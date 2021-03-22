#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector <string> v{"alex@yandex.ru",
                    "alex_27@yandex.com",
                    "alex.27@yandex.com",
                    "alex111@devcolibri.com",
                    "alex100@devcolibri.com.ua",
                    "alex@buf1.com",
                    "alex@gmail.com.com",
                    "alex+27@gmail.com",
                    "alex-27@yandex-test.com",
                    "re34@q.w.e"};

	std::regex regular("([\\w-]+)"
                        "(@)"
                        "([\\w-]+)"
                        "(\\x2E.)"
                        "([A-Za-z]{2,6})"
                        "((\\x2E.[A-Za-z]{1,6}){0,1})");

    for (auto i : v) {
        cmatch result;
        if (std::regex_match(i.c_str(), result, regular)) {
            cout << result[0] << " - " << result[3] << result[4] << result[5] << result[6] << endl; 
        }
        else 
            cout << i << " - неверная запись" << endl; 
    }
	return 0;
}