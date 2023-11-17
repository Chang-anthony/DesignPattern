#pragma once

#include <iostream>
#include <string>

//forward declare �e�V�ŧi
class Mat3D;

class Handle
{
public:
	Handle(Handle* next);
	~Handle();

	void HandlePrintPlane(std::string flat, int planeToPrint, Mat3D* mat);
	virtual void printHandle(int planeToPrint, Mat3D* mat) = 0;
	virtual bool match(std::string flat) = 0;


private:
	Handle* next;
};

