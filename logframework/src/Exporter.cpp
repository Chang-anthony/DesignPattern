#include <Exporter.hpp>
#include <Logger.hpp>
#include <utils.h>

Exporter::Exporter()
{
}

void Exporter::SetLogger(Logger* logger)
{
    utils::RequireNonNull(logger);
    this->logger = logger;
}

Logger* Exporter::GetLogger()
{
    return logger;
}

Exporter::~Exporter()
{
}