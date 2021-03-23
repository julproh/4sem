#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include<string>
#include<chrono>

using namespace std;
using namespace std::chrono_literals;

template <typename T>
time_t to_time_t(T t)
{
    using namespace chrono;
    auto tp = time_point_cast<system_clock::duration>(t - T::clock::now()+ system_clock::now());
    return system_clock::to_time_t(tp);
}

int main() {
    string path;
    cout << "Введите нужную директорию" << endl;
    getline(cin, path);
    cout << "В содержатся:" << endl;

    if (filesystem::exists(path) && filesystem::is_directory(path))
    {
        for (const auto& entry : filesystem::directory_iterator(path))
        {
            auto file_name = entry.path().filename().string();
            auto ftime = filesystem::last_write_time(entry.path());
            time_t cftime = to_time_t(ftime);
            cout << file_name << " " << asctime(localtime(&cftime)) << endl;
        }
    } else {
        cerr<<"Нет такой директории" << endl;
        exit(EXIT_FAILURE);
    }
    return 0;
}

//для компиляции
// g++-10 -std=c++17 3.cpp -o 3