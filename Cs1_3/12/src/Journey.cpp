#include "../include/Journey.hpp"
#include "../include/Chapter.hpp"

Journey::Journey(/* args */)
{
    this->chapters = std::set<Chapter*>();
}

void Journey::AddChapter(Chapter* chapter)
{
    this->chapters.insert(chapter);
}

Journey::~Journey()
{
}