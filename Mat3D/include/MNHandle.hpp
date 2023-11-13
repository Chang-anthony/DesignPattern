#pragma once
#include "../include/Handle.hpp"
class Mat3D;

class MNHandle : public Handle
{
public:
	MNHandle(Handle* next);
	~MNHandle();

	bool match(std::string flat) override;
	//void PrintPlane(int planeToPrint, Mat3D* mat) override;
	bool IsBounder(int planeToPrint, Mat3D* mat) override;
	char GetValue(int i, int j, int planeToPrint, Mat3D* mat) override;
	int  GetNum1(Mat3D* mat) override;
	int  GetNum2(Mat3D* mat) override;

private:

};

