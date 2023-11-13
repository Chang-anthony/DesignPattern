#include "../include/Mat3D.hpp"
#include "../include/Handle.hpp"

Mat3D::Mat3D(int m, int n, int r)
{
    this->m = m;
    this->n = n;
    this->r = r;

    //lambda function
    const char* color = this->GetColors();
    
    auto getrandom = [color]()
    {
        int randomIndex = rand() % 6;
        return color[randomIndex];
    };

    this->coord = new char** [this->m];

   
    for (int i = 0; i < m; i++) {
        this->coord[i] = new char* [this->n];
        for (int j = 0; j < n; j++) {
            this->coord[i][j] = new char[this->r];
            for (int k = 0; k < r; k++) {
                this->coord[i][j][k] = getrandom();
            }
        }
    }

    //  this->PrintALL();
}

Mat3D::Mat3D(int m, int n, int r,Handle* handler)
{
    this->m = m;
    this->n = n;
    this->r = r;
    this->handler = handler;

    //lambda function
    const char* color = this->GetColors();

    auto getrandom = [color]()
        {
            int randomIndex = rand() % 6;
            return color[randomIndex];
        };

    this->coord = new char** [this->m];


    for (int i = 0; i < m; i++) {
        this->coord[i] = new char* [this->n];
        for (int j = 0; j < n; j++) {
            this->coord[i][j] = new char[this->r];
            for (int k = 0; k < r; k++) {
                this->coord[i][j][k] = getrandom();
            }
        }
    }

    this->PrintALL();
}

void Mat3D::HandlePrintPlane(std::string flat, int planeToPrint, Mat3D* mat)
{
    this->handler->HandlePrintPlane(flat, planeToPrint, mat);
}

void Mat3D::printValueAndAddress(int x, int y, int z)
{
    int m = this->GetM();
    int n = this->GetN();
    int r = this->GetR();
    char*** coord = this->GetCoord();
    if (x >= 0 && x < m && y >= 0 && y < n && z >= 0 && z < r) {
        char value = coord[x][y][z];
        char* address = &coord[x][y][z];

        std::cout << "值 (" << x << ", " << y << ", " << z << ") 為: " << value << std::endl;
        std::cout << "位址 (" << x << ", " << y << ", " << z << ") 為: " << static_cast<void*>(address) << std::endl;
    }
    else {
        std::cout << "超出範圍!!!" << std::endl;
    }
}

void Mat3D::writeNewValue(int x, int y, int z, char value)
{
    int m = this->GetM();
    int n = this->GetN();
    int r = this->GetR();
    char*** coord = this->GetCoord();
    if (x >= 0 && x < m && y >= 0 && y < n && z >= 0 && z < r) {
        coord[x][y][z] = value;
        char* address = &coord[x][y][z];
        std::cout << "值 (" << x << ", " << y << ", " << z << ") 為: " << coord[x][y][z] << std::endl;
        std::cout << "位址 (" << x << ", " << y << ", " << z << ") 為: " << static_cast<void*>(address) << std::endl;
    }
    else {
        std::cout << "超出範圍!!!" << std::endl;
    }
}

void Mat3D::PrintALL()
{
    int m = this->GetM();
    int n = this->GetN();
    int r = this->GetR();
    char*** coord = this->GetCoord();

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < r; k++)
            {
                std::cout << coord[i][j][k];
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    std::cout << "All done " << std::endl;

}

int Mat3D::GetM()
{
    return this->m;
}

int Mat3D::GetN()
{
    return this->n;
}

int Mat3D::GetR()
{
    return this->r;
}

char*** Mat3D::GetCoord()
{
    return this->coord;
}


const char* Mat3D::GetColors()
{ 
    const char* c = this->colors;
    return c;
}

Mat3D::~Mat3D()
{
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            delete[] this->coord[i][j];
        }
        delete[] this->coord[i];
    }
    delete[] this->coord;
}