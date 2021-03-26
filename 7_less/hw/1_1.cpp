#include <iostream> 
#include <random>

using namespace std; 

int main () {

    int in_circle = 0.0;
    int n;

    random_device rd;
    
    cout << "Введите количество точек: ";
    cin >> n;


    for (int i = 0; i < n; i++)
    {
        int x = rd() % n; // делим длину стороны квадратика на n одинаковых частей и смотрим, в какой мини-квадратик попадет точка
        int y = rd() % n;
        if (x*x+y*y <= n*n) {

            in_circle++;
        }
    }
    
    cout << "Значение числа Пи: " << 4.0*float(in_circle)/ float(n) << endl;

    return 0;
}