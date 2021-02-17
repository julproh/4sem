#include <iostream>
#include <bitset>

using namespace std;

int main() {

    enum Color{red, yellow, green, white, black, //..
    quantity};
    bitset<quantity> colors;
    colors.set(red);
    colors.set(white);// ставит true

    cout << " bitset or uses colors " << colors << endl;
    cout << "quantity of used colors " << colors.count() <<endl;
    cout << "bitset of unused colors " << ~colors << endl;


    return 0;
}
