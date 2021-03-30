#include <iostream>
#include <thread>
#include <random>
#include <future>

using namespace std;
mutex g_mutex;

void counting_points (int &in_circle, int n) {
    
    lock_guard<mutex> lock (g_mutex);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, n);
    int x = dis(gen); 
    int y = dis(gen);
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