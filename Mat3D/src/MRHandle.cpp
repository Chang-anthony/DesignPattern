#include "../include/MRHandle.hpp"
#include "../include/Mat3D.hpp"

MRHandle::MRHandle(Handle* next) :PrintPlaneTemplate(next)
{
}

bool MRHandle::match(std::string flat)
{
	return flat == "mr";
}

//void MRHandle::PrintPlane(int planeToPrint, Mat3D* mat)
//{
//    int m = mat->GetM();
//    int n = mat->GetN();
//    int r = mat->GetR();
//    char*** coord = mat->GetCoord();
//
//    std::cout << "���� r = " << planeToPrint << " ���ȡG" << std::endl;
//    for (int i = 0; i < m; i++) {
//        for (int j = 0; j < r; j++) {
//            std::cout << coord[i][planeToPrint][j] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//}

bool MRHandle::IsBounder(int planeToPrint, Mat3D* mat)
{
    return planeToPrint >= 0 && planeToPrint < mat->GetN();
}


char MRHandle::GetValue(int i, int j, int planeToPrint, Mat3D* mat)
{
    char*** coord = mat->GetCoord();
    return coord[i][planeToPrint][j];
}
int  MRHandle::GetNum1(Mat3D* mat)
{
    return mat->GetM();
}

int  MRHandle::GetNum2(Mat3D* mat)
{
    return mat->GetR();
}


MRHandle::~MRHandle()
{
}