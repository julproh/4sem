
#include <iostream>
#include <fstream>
#include <string>


using namespace std;
int main()
{
    ifstream in("second_task.txt");

    if (!in)
    {
        cerr << "Не могу открыть \"second_task.txt\"!" << endl;
        exit(1);
    }

    int n;
    cout<<"Введите номер нужной строки (от 1 до 7):" << endl; 
    cin>>n;

    in.seekg((n-1)*4);
    
    string str;
    getline(in, str);

    cout<< "Полученная строка: "<< endl << str <<endl;
    return 0;
}