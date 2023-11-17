#include "../include/Handle.hpp"
#include "../include/Mat3D.hpp"

Handle::Handle(Handle* next) :next(next)
{
}

void Handle::HandlePrintPlane(std::string flat, int planeToPrint, Mat3D* mat)
{
	if (this->match(flat))
	{
		this->printHandle(planeToPrint, mat);
	}
	else
	{
		this->next->HandlePrintPlane(flat, planeToPrint, mat);
	}
}


Handle::~Handle()
{
}