#ifndef _BIGTWO_PASER_H_
#define _BIGTWO_PASER_H_

#include <iostream>
#include <vector>
#include <string>

class FileIterator;

class BigTwo_paser
{
private:
    /* data */
    std::string file;
    int count;
    FileIterator* test;
public:
    BigTwo_paser(const std::string& file);
    ~BigTwo_paser();

    const std::string& read(); 
protected:
};

#endif /* _BIGTWO_PASER_H_ */
