#pragma once 

#include "../include/PrintPlaneTemplate.hpp"
class Mat3D;

class NRHandle :public PrintPlaneTemplate
{
public:
	NRHandle (Handle * next);
	~NRHandle ();

	bool match(std::string flat) override;
	//void PrintPlane(int planeToPrint, Mat3D* mat) override;
	bool IsBounder(int planeToPrint, Mat3D* mat) override;
	char GetValue(int i, int j, int planeToPrint, Mat3D* mat) override;
	int  GetNum1(Mat3D* mat) override;
	int  GetNum2(Mat3D* mat) override;

private:

};

