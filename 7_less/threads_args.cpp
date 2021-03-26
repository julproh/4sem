#include <thread>
#include <iostream>


using namespace std;



int main() {

    int n = 0;
    auto thread_lambda_1 =[](int &n){n++;};
    auto thread_lambda_2 =[](int &n){n+=2;};

    thread thr1(thread_lambda_1, ref(n));
    thread thr2(thread_lambda_2, ref(n));

    thr1.join();

    thr2.join();

    cout << "n = " << n << endl;

    return 0;
}