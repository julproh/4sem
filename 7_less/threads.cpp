#include <thread>
#include <iostream>


using namespace std;

void thread_func() {
    cout << "Thread id: " << this_thread::get_id()<< endl;
}

int main() {

    cout << "Number of cores: "<< thread :: hardware_concurrency() << endl; // сообщает сколько ядер доступно 
    cout << "Main thread id: "<< this_thread::get_id() << endl; 
    thread thr1(thread_func);
    thr1.join(); //присоединяемся к потоку, ждем пока завершится
    //thr1.detach(); // бросаем на произвол судьбы
    return 0;
}

// для зпуска - g++ threads.cpp -o threads -pthread