#include "visualizer.hpp"

int main()
{
    Visualizer visualizer;

    visualizer.start_motion();

    return 0;
}

//g++ -std=c++17 main.cpp  visualizer.cpp   -o main  -lsfml-graphics -lsfml-window -lsfml-system -pthread