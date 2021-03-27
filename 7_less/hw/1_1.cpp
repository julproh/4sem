#include <iostream> 
#include <random>

using namespace std; 

int main () {

    int in_circle = 0.0;
    int n;

    random_device rd;
    
    
    
    cout << "Введите количество точек: ";
    cin >> n;

    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, n);

    for (int i = 0; i < n; i++)
    {
        int x = dis(gen);
        int y = dis(gen);
        if (x*x+y*y <= n*n) {

            in_circle++;
        }
    }
    
    cout << "Значение числа Пи: " << 4.0*float(in_circle)/ float(n) << endl;

    return 0;
}