#include <FileExporter.hpp>
#include <Logger.hpp>
#include <Layout.hpp>

FileExporter::FileExporter(std::string filename) : Exporter()
{
    this->filename = filename;
}

void FileExporter::output(std::string message)
{
    if (!logger) {
        return;
    }

    file.open(filename, std::ios::app);
    if (!file.is_open()) {
        throw std::invalid_argument("File could not be opened");
    }
    
    std::string formattedMessage = logger->GetLayout()->format(message);
    file << formattedMessage << std::endl;
    file.close();
}

FileExporter::~FileExporter()
{
}