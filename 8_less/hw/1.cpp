#include <iostream>
#include <thread>
#include <random>
#include <future>

using namespace std;
mutex g_mutex;

void counting_points (int N, int &in_circle, int n) {
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, n);
    uniform_int_distribution<> dis_(1, n);

    int count = 0;
    for (auto j = 0; j < N; j++){
    int x = dis(gen); 
    int y = dis_(gen);

    if (x*x+y*y <= n*n) {
        count++;
    }   
    }

    g_mutex.lock();
    lock_guard <mutex> lock(mutex);

    in_circle +=count;
    
    g_mutex.unlock();

}
int main () {

    int in_circle = 0;
    int n;

    
    cout << "Введите количество точек: ";
    cin >> n;
    
    int m =  thread::hardware_concurrency() != 0 ? thread::hardware_concurrency() : 4;
    int N =n / m; 

    vector <thread> threads(thread::hardware_concurrency());
    for (int i = 0; i < threads.size(); i++)
    {   
        threads[i] = thread(counting_points,N, ref(in_circle), n);
    }


    for (int i = 0; i < threads.size(); i++)
    {   
        threads[i].join();
    }

    cout << in_circle << endl;
    
    cout << "Значение числа Пи: " << 4.0*float(in_circle)/ float(n) << endl;

    return 0;
}