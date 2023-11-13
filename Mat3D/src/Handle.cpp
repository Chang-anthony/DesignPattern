#include "../include/Handle.hpp"
#include "../include/Mat3D.hpp"

Handle::Handle(Handle* next) :next(next)
{
}

void Handle::HandlePrintPlane(std::string flat, int planeToPrint, Mat3D* mat)
{
	if (this->match(flat))
	{
		this->doHandle(planeToPrint, mat);
	}
	else
	{
		this->next->HandlePrintPlane(flat, planeToPrint, mat);
	}
}

void Handle::doHandle(int planeToPrint, Mat3D* mat)
{
 
    if (this->IsBounder(planeToPrint, mat)) {
		this->PrintPlane(planeToPrint, mat);
    }
    else {
        std::cout << "超出可輸出的平面 !!!" << std::endl;
    }
}

void Handle::PrintPlane(int planeToPrint, Mat3D* mat)
{
    int num1 = this->GetNum1(mat);
    int num2 = this->GetNum2(mat);

    std::cout << "平面  = " << planeToPrint << " 輸出平面為:" << std::endl;
    for (int i = 0; i < num1; i++) {
        for (int j = 0; j < num2; j++) {
            std::cout << this->GetValue(i,j,planeToPrint, mat) << " ";
        }
        std::cout << std::endl;
    }
}

Handle::~Handle()
{
}