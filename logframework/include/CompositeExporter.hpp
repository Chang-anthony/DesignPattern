#ifndef _COMPOSITEEXPORTER_H_
#define _COMPOSITEEXPORTER_H_

#include <iostream>
#include <string>
#include <vector>
#include <Exporter.hpp>

class CompositeExporter : public Exporter
{
private:
    /* data */
    std::vector<Exporter*> exporters;
public:
    CompositeExporter(std::vector<Exporter*> exporters);
    ~CompositeExporter();

    void output(std::string message) override;
    void SetLogger(Logger* logger) override;
    void SetExporters(std::vector<Exporter*> exporters);
};

#endif /* _COMPOSITEEXPORTER_H_ */
