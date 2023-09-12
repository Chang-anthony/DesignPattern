#include "../include/Browser.hpp"
#include "../include/WebServer.hpp"
#include "../include/File.hpp"
#include "../include/Response.hpp"
#include "../include/Resource.hpp"

Browser::Browser()
{

}

void Browser::SendRequest(WebServer* server,std::string url)
{
    Response* response = server->Request(url);
    this->Render(response->GetResource(url));
}

void Browser::Render(File* file)
{

}

Browser::~Browser()
{
}