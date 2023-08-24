#include "../include/Road.hpp"
#include "../include/City.hpp"

Road::Road(City* A ,City* B):A(A),B(B)
{
    std::cout << "city A connect to B use this road" << std::endl;
}

Road::~Road()
{
}