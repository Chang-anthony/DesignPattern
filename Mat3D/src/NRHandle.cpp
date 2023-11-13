#include "../include/NRHandle.hpp"
#include "../include/Mat3D.hpp"

NRHandle::NRHandle(Handle* next) :Handle(next)
{
}

bool NRHandle::match(std::string flat)
{
    return flat == "nr";
}

//void NRHandle::PrintPlane(int planeToPrint, Mat3D* mat)
//{
//    int m = mat->GetM();
//    int n = mat->GetN();
//    int r = mat->GetR();
//    char*** coord = mat->GetCoord();
//
//    std::cout << "���� r = " << planeToPrint << " ���ȡG" << std::endl;
//    for (int i = 0; i < n; i++) {
//        for (int j = 0; j < r; j++) {
//            std::cout << coord[planeToPrint][i][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//}

bool NRHandle::IsBounder(int planeToPrint, Mat3D* mat)
{
    return planeToPrint >= 0 && planeToPrint < mat->GetM();
}

char NRHandle::GetValue(int i, int j, int planeToPrint, Mat3D* mat)
{
    char*** coord = mat->GetCoord();
    return coord[planeToPrint][i][j];
}
int  NRHandle::GetNum1(Mat3D* mat)
{
    return mat->GetN();
}

int  NRHandle::GetNum2(Mat3D* mat)
{
    return mat->GetR();
}

NRHandle ::~NRHandle()
{
}