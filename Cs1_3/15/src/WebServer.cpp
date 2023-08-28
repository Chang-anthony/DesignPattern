#include "../include/WebServer.hpp"
#include "../include/Resource.hpp"
#include "../include/Response.hpp"

WebServer::WebServer(/* args */)
{

}

Response* WebServer::Request(std::string url)
{
    Response* response = new Response();
    this->resource = response->GetResource(url);
    return response;
}

WebServer::~WebServer()
{

}