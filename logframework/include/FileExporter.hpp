#ifndef _FILEEXPORTER_H_
#define _FILEEXPORTER_H_

#include <iostream>
#include <string>
#include <Exporter.hpp>
#include <fstream>

class FileExporter : public Exporter
{
private:
    /* data */
    std::string filename;
    std::ofstream file;
public:
    FileExporter(std::string filename);
    ~FileExporter();

    void output(std::string message) override;
};


#endif /* _FILEEXPORTER_H_ */
