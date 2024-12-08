#include <ConsoleExporter.hpp>
#include <Logger.hpp>
#include <Layout.hpp>

ConsoleExporter::ConsoleExporter(/* args */) : Exporter()
{
}

void ConsoleExporter::output(std::string message)
{
    if (!logger) {
        return;
    }
    
    std::string formattedMessage = logger->GetLayout()->format(message);
    std::cout << formattedMessage << std::endl;
}

ConsoleExporter::~ConsoleExporter()
{
}