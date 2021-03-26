#include <iostream>
#include <thread>
#include <random>
#include <future>

using namespace std;


void counting_points (int &in_circle, int n) {
    
    random_device rd;
    int x = rd() % n; // делим длину стороны квадратика на n одинаковых частей и смотрим, в какой мини-квадратик попадет точка
    int y = rd() % n;
    if (x*x+y*y <= n*n) {
        in_circle++;
    }
}
int main () {

    int in_circle = 0;
    int n;

    
    cout << "Введите количество точек: ";
    cin >> n;

    vector <thread> threads;
    for (int i = 0; i < n; i++)
    {   
        threads.push_back(thread(counting_points, ref(in_circle), n));
    }


    for (int i = 0; i < n; i++)
    {   
        threads[i].join();
    }
    
    cout << "Значение числа Пи: " << 4.0*float(in_circle)/ float(n) << endl;

    return 0;
}