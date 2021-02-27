#include <iostream>
#include <random> // std::random_device и std::mt19937

int main()
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    // std::mt19937 mersenne(static_cast<unsigned int>(time(0))); // for Visual Studio/MinGW
    std::cout << "*************************************************************************" << std::endl;
    std::cout << "mersenne():" << "\n";
    for (int count = 0; count < 48; ++count)
    {
        std::cout << mersenne() << "\t";
        if ((count + 1) % 5 == 0)
            std::cout << "\n";
    }
    std::cout << "\n*************************************************************************" << std::endl;

    std::uniform_int_distribution<> un_distrib(1, 100);
    std::cout << "uniform_int_distribution<> un_distrib(1, 100):" << "\n";
    for (int count = 0; count < 48; ++count)
    {
        std::cout << un_distrib(mersenne)<< "\t";
        if ((count + 1) % 5 == 0)
            std::cout << "\n";
    }
    std::cout << "\n*************************************************************************" << std::endl;

    std::normal_distribution<> norm_distrib{ 10, 2 };
    std::cout << "normal_distribution<> norm_distrib(10, 2), mean = 10, standard deviation = 2:" << "\n";
    for (int count = 0; count < 48; ++count)
    {
        std::cout << norm_distrib(mersenne) << "\t";
        if ((count + 1) % 5 == 0)
            std::cout << "\n";
    }


}
