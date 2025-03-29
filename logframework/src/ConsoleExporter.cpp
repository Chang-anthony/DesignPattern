#include <ConsoleExporter.hpp>
#include <Logger.hpp>

ConsoleExporter::ConsoleExporter(/* args */) : Exporter()
{
}

void ConsoleExporter::output(std::string message)
{
    if (!logger) {
        return;
    }
    std::cout << message << std::endl;
}

ConsoleExporter::~ConsoleExporter()
{
}