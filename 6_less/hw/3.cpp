#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include<string>
#include<chrono>

using namespace std;
using namespace std::chrono_literals;

template <typename TP>
std::time_t to_time_t(TP tp)
{
    using namespace std::chrono;
    auto sctp = time_point_cast<system_clock::duration>(tp - TP::clock::now()+ system_clock::now());
    return system_clock::to_time_t(sctp);
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