#include <iostream>
#include <cstdlib>
#include <ctime>
#include "../include/Mat3D.hpp"
#include "../include/Handle.hpp"
#include "../include/MNHandle.hpp"
#include "../include/MRHandle.hpp"
#include "../include/NRHandle.hpp"



void rotatePlane(char*** threeDArray, int m, int n, int r, std::string flat, int rotationLayer, int isClockwise) {
    if (flat == "mn") {
        if (rotationLayer >= 0 && rotationLayer < r) {
            if (rotationLayer >= 0 && rotationLayer < r) {
                if (isClockwise == 0) {
                    char** rotatedPlane = new char* [n];
                    for (int i = 0; i < n; ++i) {
                        rotatedPlane[i] = new char[m];
                    }

                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < m; ++j) {
                            rotatedPlane[i][j] = threeDArray[j][n - i - 1][rotationLayer];
                        }
                    }

                    std::cout << "旋轉前平面 r = " << rotationLayer << " 的值：" << std::endl;
                    for (int i = 0; i < m; ++i) {
                        for (int j = 0; j < n; ++j) {
                            std::cout << threeDArray[i][j][rotationLayer] << " ";
                        }
                        std::cout << std::endl;
                    }

                    std::cout << "逆時針旋轉後平面 r = " << rotationLayer << " 的值：" << std::endl;
                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < m; ++j) {
                            std::cout << rotatedPlane[i][j] << " ";
                        }
                        std::cout << std::endl;
                    }

                    for (int i = 0; i < n; ++i) {
                        delete[] rotatedPlane[i];
                    }
                    delete[] rotatedPlane;
                }
                else {
                    char** rotatedPlane = new char* [n];
                    for (int i = 0; i < n; ++i) {
                        rotatedPlane[i] = new char[m];
                    }

                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < m; ++j) {
                            rotatedPlane[i][j] = threeDArray[m - j - 1][i][rotationLayer];
                        }
                    }

                    std::cout << "旋轉前平面 r = " << rotationLayer << " 的值：" << std::endl;
                    for (int i = 0; i < m; ++i) {
                        for (int j = 0; j < n; ++j) {
                            std::cout << threeDArray[i][j][rotationLayer] << " ";
                        }
                        std::cout << std::endl;
                    }

                    std::cout << "順時針旋轉後平面 r = " << rotationLayer << " 的值：" << std::endl;
                    for (int i = 0; i < n; ++i) {
                        for (int j = 0; j < m; ++j) {
                            std::cout << rotatedPlane[i][j] << " ";
                        }
                        std::cout << std::endl;
                    }

                    for (int i = 0; i < n; ++i) {
                        delete[] rotatedPlane[i];
                    }
                    delete[] rotatedPlane;
                }
            }
            else {
                std::cout << "無效的旋轉層數。" << std::endl;
            }
        }
    }
    else if (flat == "nr") {
        if (rotationLayer >= 0 && rotationLayer < m) {
            if (isClockwise == 0) {
                char** rotatedPlane = new char* [r];
                for (int i = 0; i < r; ++i) {
                    rotatedPlane[i] = new char[n];
                }

                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < n; ++j) {
                        rotatedPlane[i][j] = threeDArray[rotationLayer][j][r - i - 1];
                    }
                }

                std::cout << "旋轉前平面 r = " << rotationLayer << " 的值：" << std::endl;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < r; ++j) {
                        std::cout << threeDArray[rotationLayer][i][j] << " ";
                    }
                    std::cout << std::endl;
                }

                std::cout << "逆時針旋轉後平面 r = " << rotationLayer << " 的值：" << std::endl;
                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < n; ++j) {
                        std::cout << rotatedPlane[i][j] << " ";
                    }
                    std::cout << std::endl;
                }

                for (int i = 0; i < r; ++i) {
                    delete[] rotatedPlane[i];
                }
                delete[] rotatedPlane;
            }
            else {
                char** rotatedPlane = new char* [r];
                for (int i = 0; i < r; ++i) {
                    rotatedPlane[i] = new char[n];
                }

                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < n; ++j) {
                        rotatedPlane[i][j] = threeDArray[rotationLayer][n - j - 1][i];
                    }
                }

                std::cout << "旋轉前平面 r = " << rotationLayer << " 的值：" << std::endl;
                for (int i = 0; i < n; ++i) {
                    for (int j = 0; j < r; ++j) {
                        std::cout << threeDArray[rotationLayer][i][j] << " ";
                    }
                    std::cout << std::endl;
                }

                std::cout << "順時針旋轉後平面 r = " << rotationLayer << " 的值：" << std::endl;
                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < n; ++j) {
                        std::cout << rotatedPlane[i][j] << " ";
                    }
                    std::cout << std::endl;
                }

                for (int i = 0; i < r; ++i) {
                    delete[] rotatedPlane[i];
                }
                delete[] rotatedPlane;
            }
        }
        else {
            std::cout << "無效的旋轉層數。" << std::endl;
        }
    }
    else if (flat == "mr") {
        if (rotationLayer >= 0 && rotationLayer < n) {
            if (isClockwise == 0) {
                char** rotatedPlane = new char* [r];
                for (int i = 0; i < r; ++i) {
                    rotatedPlane[i] = new char[m];
                }

                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < m; ++j) {
                        rotatedPlane[i][j] = threeDArray[j][rotationLayer][r - i - 1];
                    }
                }

                std::cout << "旋轉前平面 r = " << rotationLayer << " 的值：" << std::endl;
                for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < r; ++j) {
                        std::cout << threeDArray[i][rotationLayer][j] << " ";
                    }
                    std::cout << std::endl;
                }

                std::cout << "逆時針旋轉後平面 r = " << rotationLayer << " 的值：" << std::endl;
                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < m; ++j) {
                        std::cout << rotatedPlane[i][j] << " ";
                    }
                    std::cout << std::endl;
                }

                for (int i = 0; i < r; ++i) {
                    delete[] rotatedPlane[i];
                }
                delete[] rotatedPlane;
            }
            else {
                char** rotatedPlane = new char* [r];
                for (int i = 0; i < r; ++i) {
                    rotatedPlane[i] = new char[m];
                }

                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < m; ++j) {
                        rotatedPlane[i][j] = threeDArray[m - j - 1][rotationLayer][i];
                    }
                }

                std::cout << "旋轉前平面 r = " << rotationLayer << " 的值：" << std::endl;
                for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < r; ++j) {
                        std::cout << threeDArray[i][rotationLayer][j] << " ";
                    }
                    std::cout << std::endl;
                }

                std::cout << "順時針旋轉後平面 r = " << rotationLayer << " 的值：" << std::endl;
                for (int i = 0; i < r; ++i) {
                    for (int j = 0; j < m; ++j) {
                        std::cout << rotatedPlane[i][j] << " ";
                    }
                    std::cout << std::endl;
                }

                for (int i = 0; i < r; ++i) {
                    delete[] rotatedPlane[i];
                }
                delete[] rotatedPlane;
            }
        }
        else {
            std::cout << "無效的旋轉層數。" << std::endl;
        }
    }
    else {
       std::cout << "指定的平面不存在。" << std::endl;
    }
}

int main() {
    Handle* handler = new MRHandle(new MNHandle(new NRHandle(nullptr)));

    std::srand(static_cast<unsigned int>(time(0)));

    std::cout << "====================第一題====================" << std::endl;
    int m, n, r;

    std::cout << "請輸入 m: ";
    std::cin >> m;

    std::cout << "請輸入 n: ";
    std::cin >> n;

    std::cout << "請輸入 r: ";
    std::cin >> r;


    Mat3D* mat = new Mat3D(m, n, r, handler);

    std::string flat = "";
    int planeToPrint;
    std::cout << "輸入要列印的平面 (mn, nr, mr): ";
    std::cin >> flat;
    std::cout << "輸入要列印的層數: ";
    std::cin >> planeToPrint;

    mat->HandlePrintPlane(flat, planeToPrint, mat);

    std::cout << "====================第二題====================" << std::endl;
    int x, y, z;
    std::cout << "請輸入要查找的位置 (m, n, r): ";
    std::cin >> x >> y >> z;
    mat->printValueAndAddress(x, y, z);

    std::cout << "====================第三題====================" << std::endl;
    char newValue;
    std::cout << "請輸入要寫入新值的位置 (m, n, r): ";
    std::cin >> x >> y >> z;
    std::cout << "請輸入要寫入的新值: ";
    std::cin >> newValue;
    mat->writeNewValue(x, y, z, newValue);
    mat->HandlePrintPlane("mn", z, mat);

    //cout << "====================第四題====================" << endl;
    //int rotationLayer, isClockwise;
    //cout << "輸入要旋轉的平面 (mn, nr, mr): ";
    //cin >> flat;
    //cout << "輸入要旋轉的層數: ";
    //cin >> rotationLayer;
    //cout << "順時針還是逆時針旋轉 (1: 順時針, 0: 逆時針): ";
    //cin >> isClockwise;

    //rotatePlane(threeDArray, m, n, r, flat, rotationLayer, isClockwise);

    //delete3DArray(threeDArray, m, n, r);

    return 0;
}
