#ifndef _CONSOLEEXPORTER_H_
#define _CONSOLEEXPORTER_H_

#include <iostream>
#include <string>
#include <Exporter.hpp>

class ConsoleExporter : public Exporter
{
private:
    /* data */
public:
    ConsoleExporter(/* args */);
    ~ConsoleExporter();

    void output(std::string message) override;
};

#endif /* _CONSOLEEXPORTER_H_ */
