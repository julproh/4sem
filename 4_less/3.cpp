#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;
int main() {

    srand(static_cast<unsigned int>(time(0)));

    for (int count = 0; count < 1000; ++count)
    {
        cout << rand() << "\t";
        if ((count+1)%5 == 0)
        cout << endl;
    } 
    return 0;
}