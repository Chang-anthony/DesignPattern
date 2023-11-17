#include "../include/Mat3D.hpp"
#include "../include/MNHandle.hpp"

MNHandle::MNHandle(Handle* next) :PrintPlaneTemplate(next)
{

}

bool MNHandle::match(std::string flat)
{
    return flat == "mn";
}

//void MNHandle::PrintPlane(int planeToPrint, Mat3D* mat)
//{
//    int m = mat->GetM();
//    int n = mat->GetN();
//    int r = mat->GetR();
//    char*** coord = mat->GetCoord();
//    
//    std::cout << "���� r = " << planeToPrint << " ���ȡG" << std::endl;
//    for (int i = 0; i < m; i++) {
//        for (int j = 0; j < n; j++) {
//            std::cout << coord[i][j][planeToPrint] << " ";
//        }
//        std::cout << std::endl;
//    }
//
//}

bool MNHandle::IsBounder(int planeToPrint,Mat3D* mat)
{
    return planeToPrint >= 0 && planeToPrint < mat->GetR();
}

char MNHandle::GetValue(int i, int j, int planeToPrint, Mat3D* mat)
{
    char*** coord = mat->GetCoord();
    return coord[i][j][planeToPrint];
}
int  MNHandle::GetNum1(Mat3D* mat)
{
    return mat->GetM();
}

int  MNHandle::GetNum2(Mat3D* mat)
{
    return mat->GetN();
}


MNHandle::~MNHandle()
{
}