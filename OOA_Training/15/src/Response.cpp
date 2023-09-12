#include "../include/Response.hpp"
#include "../include/Resource.hpp"

Response::Response(/* args */)
{

}

Resource* Response::GetResource(std::string url)
{
    Resource* resource = new Resource();
    this->resource = resource;
    return resource;
}

void Response::SetResponse(Resource* resource)
{
    this->resource = resource;
}

Response::~Response()
{

}