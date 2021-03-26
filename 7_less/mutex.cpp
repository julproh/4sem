#include <string>
#include <iostream>
#include <thread>
#include <mutex>

std::mutex g_mutex;

void thread_func_inc() {
    //g_mutex.lock(); // take mutex manually
    std::lock_guard<std::mutex> _locker(g_mutex); // RAII-mutex

    //CRITICAL SECTION
    for (auto i = 0; i < 1000; i++)
        std::cout << std::this_thread::get_id() << std::endl;
    //END OF CRITICAL SECTION

    //g_mutex.unlock(); // release mutex manually
}

void thread_func_dec() {
    //g_mutex.lock(); // take mutex manually 
    std::lock_guard<std::mutex> _locker(g_mutex); // RAII-mutex
    
    //CRITICAL SECTION
    for (auto i = 0; i < 1000; i++)
        std::cout << std::this_thread::get_id() << std::endl;
    //END OF CRITICAL SECTION

    //g_mutex.unlock(); // release mutex manually
}

int main()
{
    std::cout <<"harware concurrency: " << std::thread::hardware_concurrency() << std::endl;
    int n = 0;

    std::thread thr1(thread_func_inc);
    std::thread thr2(thread_func_dec);
    thr1.join();  //thr1.detatch();
    thr2.join();  //thr1.detatch();

    return 0;
}