#include "Layout.hpp"
#include <utils.h>

//TODO: implement Logger class
Layout::Layout(Logger* logger)
{
    SetLogger(logger);
}

Logger* Layout::GetLogger()
{
    return logger;
}

void Layout::SetLogger(Logger* logger)
{
    utils::RequireNonNull(logger);
    this->logger = logger;
}

Layout::~Layout()
{
}