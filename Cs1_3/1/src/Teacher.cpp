#include "../include/Teacher.hpp"
#include "../include/Handout.hpp"

Teacher::Teacher(/* args */)
{
}

void Teacher::Teach(Handout* handout)
{
    utils::RequireNonNull(handout);
    std::cout << "teach teaching use handout" << std::endl;
}

Teacher::~Teacher()
{
    
}