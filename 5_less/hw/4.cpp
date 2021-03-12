#include <iostream>
#include <string>
#include <regex>


using namespace std;

int main() {

    string text = "23.09.2089 // 45.1.3000 // 32.19.2000 // 4.9.2012 ";
    regex regular("([^1-9][1-9]|0[1-9]|[12][0-9]|3[01])""\.""([1-9]|0[1-9]|1[012])""(.)""([0-9]{4})");
    cmatch result;


     while (regex_search(text.c_str(),result,regular)) {
        cout << result[0] << endl;
        text = result.suffix().str();
    }

    return 0;
}