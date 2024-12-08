#include <CompositeExporter.hpp>
#include <utils.h>

CompositeExporter::CompositeExporter(std::vector<Exporter*> exporters) : Exporter()
{
    SetExporters(exporters);
}

void CompositeExporter::output(std::string message)
{
    for (auto exporter : exporters) {
        exporter->output(message);
    }
}

void CompositeExporter::SetExporters(std::vector<Exporter*> exporters)
{
    utils::SizeShouldBigger(exporters, 1);
    for (auto exporter : exporters) {
        utils::RequireNonNull(exporter);
    }
    this->exporters = exporters;
}

CompositeExporter::~CompositeExporter()
{
}