#pragma once
#include <iostream>
#include <string>
#include <random>
class Handle;

class Mat3D
{
const char colors[6] = { 'R', 'G', 'B', 'U', 'V', 'W' };
public:
	Mat3D(int m ,int n ,int r);
	Mat3D(int m, int n, int r, Handle* handler);
	~Mat3D();

	void printValueAndAddress(int x, int y, int z);
	void writeNewValue(int x, int y, int z, char newValue);
	void PrintALL();

	void HandlePrintPlane(std::string flat, int planeToPrint, Mat3D* mat);

	//getter
	char*** GetCoord();
	int GetM();
	int GetN();
	int GetR();
	const char* GetColors();

	//setter
	void SetCoord(Mat3D* mat);
	void SetM(int m);
	void SetN(int n);
	void SetR(int r);

private:
	int m, n, r;
	char*** coord;

	Handle* handler;
};


