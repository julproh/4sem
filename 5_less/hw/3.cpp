#include <iostream>
#include <regex>
#include <string>
#include <vector>

using namespace std;

int main()
{
    vector <string> v{"alex@yandex.ru",
                    "alex-27@yandex.com",
                    "alex.27@yandex.com",
                    "alex111@devcolibri.com",
                    "alex.100@devcolibri.com.ua",
                    "alex@1.com",
                    "alex@gmail.com.com",
                    "alex+27@gmail.com",
                    "alex-27@yandex-test.com"};

	std::regex regular("([\\w-]+)"
                        "(@)"
                        "([\\w-]+)"
                        "(\.)"
                        "([A-Za-z]{2,4})");

    for (auto i : v) {
        cmatch result;
        if (std::regex_match(i.c_str(), result, regular)) 
            cout << result[0] << " - " << result[3] << result[4] << result[5] << endl;
        else 
            cout << i << " - неверная запись" << endl; 
    }
	return 0;
}