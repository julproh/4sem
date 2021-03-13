#include <iostream>
#include <fstream>
#include <cstdlib>

int main() {

    using namespace std;
    cout << "Insert number: ";
    int n;
    cin >> n;

    ofstream out("file.txt"); // открыли на перезапись
    if(!out.is_open()) {
        cerr << "Can't open \"file.txt\"";
        exit(EXIT_FAILURE);
    }

    out << n;
    out.close();


    ifstream in("file.txt"); 
    if(!in.is_open()) {
        cerr << "Can't open \"file.txt\"";
        exit(EXIT_FAILURE);
    }

    in >> n;
    cout << "n = " << n << endl;

    return 0;

}