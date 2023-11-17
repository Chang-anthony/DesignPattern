#ifndef _PRINTPLANETEMPLATE_H_
#define _PRINTPLANETEMPLATE_H_

#include "../include/Handle.hpp"
class Mat3D;

class PrintPlaneTemplate : public Handle
{
private:
    /* data */
public:
    PrintPlaneTemplate(Handle* next);
    ~PrintPlaneTemplate();

    void printHandle(int planeToPrint, Mat3D* mat) override;
    virtual char GetValue(int i, int j, int planeToPrint, Mat3D* mat) = 0;
	virtual int  GetNum1(Mat3D* mat) = 0;
	virtual int  GetNum2(Mat3D* mat) = 0;
    virtual bool IsBounder(int planeToPrint, Mat3D* mat) = 0; 
};





#endif /* _PRINTPLANETEMPLATE_H_ */
