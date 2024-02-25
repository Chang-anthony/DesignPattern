#ifndef _VIDEO_H_
#define _VIDEO_H_

#include <iostream>
#include <string>
#include <utils.hpp>

class Video
{
private:
    /* data */
    std::string title;
    std::string description;
    int length; //calculate by sec

public:
    Video(std::string title, std::string description, int length);
    ~Video();

    //getter
    std::string getTitle();
    std::string getDescrtiption();
    int         getLength();

    //setter
    void        setTitle(std::string title);
    void        setDescription(std::string description);
    void        setLength(int length);
};

#endif /* _VIDEO_H_ */
