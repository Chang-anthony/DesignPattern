#ifndef _CLASSROOM_H_
#define _CLASSROOM_H_


class School;
class Classroom
{
private:
    /* data */
    School* school;//因為教室是依附於學校的所以學校不存在就沒有教室，所以建構子就必須要有學校
public:
    Classroom(School* school);
    ~Classroom();
};





#endif // __CLASSROOM_H__