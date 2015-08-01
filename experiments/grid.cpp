#include "grid.h"

#include <iostream>

void grid::test()
{
    std::cout << "Grid" << std::endl << std::endl;

    Grid<int, 3, 3> g;
    g.at(1, 1) = 5;
    std::cout << g.at(4) << std::endl;

    std::cout << "----------------------------------------" << std::endl;
}