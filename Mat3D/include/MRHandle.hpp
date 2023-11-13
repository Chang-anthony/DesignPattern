#pragma once
#include "../include/Handle.hpp"
class Mat3D;

class MRHandle : public Handle
{
public:
	MRHandle(Handle* next);
	~MRHandle();

	bool match(std::string flat) override;
	//void PrintPlane(int planeToPrint, Mat3D* mat) override;
	bool IsBounder(int planeToPrint, Mat3D* mat) override;
	char GetValue(int i, int j, int planeToPrint, Mat3D* mat) override;
	int GetNum1(Mat3D* mat) override;
	int GetNum2(Mat3D* mat) override;

private:

};

