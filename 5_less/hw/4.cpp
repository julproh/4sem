#include <iostream>
#include <string>
#include <regex>


using namespace std;

int main() {

    string text = "23.09.2089 // 45.1.3000 // 32.19.2000 // 4.9.2012 // 23:50:23 // 1:23:22 // 77:01:20 ";
    regex regular("([^1-9][1-9]|0[1-9]|[12][0-9]|3[01])""\.""([1-9]|0[1-9]|1[012])""(.)""([0-9]{4})");
    regex regular2("([^1-9][1-9]|[01][0-9]|2[0-3])"":""([^1-9][1-9]|[012345][0-9])"":""([1-9]|[012345][0-9])");
    cmatch result;

    cout << "date: " << endl;

     while (regex_search(text.c_str(),result,regular)) {
        cout << result[0] << endl;
        text = result.suffix().str();
    }
    cout << "time: " << endl;

    while (regex_search(text.c_str(),result,regular2)) {
        cout << result[0] << endl;
        text = result.suffix().str();
    }

    return 0;
}