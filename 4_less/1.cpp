#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

int main() {

    string outFile = "out.dat";
    ofstream out(outFile); 
    //OR ofstream out;
    //out.open(outFile);
    if (!out.is_open()) { // OR if(!out)
        cerr << "Can not open:" << outFile << endl;
        return EXIT_FAILURE; //-1
    }

    double h = 0.1;
    for (auto i = 0U; i < 100; ++i) {
        out << i*h << "\t" << sin(i*h) << "\n";
    }
    
    out.close();

    return 0;
}
