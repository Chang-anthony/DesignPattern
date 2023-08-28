#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include <iostream>
#include <string>
#include <vector>

class Resource;
class Response
{
private:
    Resource* resource;
    /* data */
public:
    Response(/* args */);
    ~Response();

    //getter
    Resource* GetResource(std::string url);

    //setter 
    void SetResponse(Resource* resource);
};


#endif /* _RESPONSE_H_ */
