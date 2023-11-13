#pragma once

#include <iostream>
#include <string>

//forward declare «e¦V«Å§i
class Mat3D;

class Handle
{
public:
	Handle(Handle* next);
	~Handle();

	void HandlePrintPlane(std::string flat, int planeToPrint, Mat3D* mat);
	void doHandle(int planeToPrint, Mat3D* mat);
	void PrintPlane(int planeToPrint, Mat3D* mat);
	
	virtual bool IsBounder(int planeToPrint, Mat3D* mat) = 0; 
	virtual bool match(std::string flat) = 0;
	virtual char GetValue(int i, int j, int planeToPrint, Mat3D* mat) = 0;
	virtual int  GetNum1(Mat3D* mat) = 0;
	virtual int  GetNum2(Mat3D* mat) = 0;

private:
	Handle* next;
};

