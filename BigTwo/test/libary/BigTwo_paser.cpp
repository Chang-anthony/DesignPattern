#include <BigTwo_paser.hpp>
#include <FileIterator.hpp>

BigTwo_paser::BigTwo_paser(const std::string& file) : file(file)
{
    test = new FileIterator(file);

    while (*test)
    {
        std::cout << **test << std::endl; 
        ++test;
    }
    
    count = 0;
}


BigTwo_paser::~BigTwo_paser()
{
}