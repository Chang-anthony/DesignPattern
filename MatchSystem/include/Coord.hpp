#ifndef _COORD_H_
#define _COORD_H_

class Coord
{
private:
    int x;
    int y;
public:
    Coord(int x,int y);
    ~Coord();

    //getter
    int GetX();
    int GetY();

    //setter
    void SetX(int x);
    void SetY(int y);
};

#endif /* _COORD_H_ */
