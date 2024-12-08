#include "Layout.hpp"
#include <Logger.hpp>
#include <utils.h>

Layout::Layout()
{
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