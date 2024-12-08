#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <string>
#include <vector>
#include <Level.hpp>


class Layout;
class Exporter;

class Logger
{
private:
    /* data */
public:
    Logger(std::string name, Level* level, 
            Layout* layout, std::vector<Exporter*> exporter);
    Logger(Logger* parent, std::string name, Level* level, 
            Layout* layout, std::vector<Exporter*> exporter);
    ~Logger();

    //TODO: Implement the log methods
    void trace(std::string message);
    void debug(std::string message);
    void info(std::string message);
    void warn(std::string message);
    void error(std::string message);
    bool CheckThreshold(Level* level);

    //getters
    std::string GetName();
    Level* GetLevel();
    Layout* GetLayout();
    std::vector<Exporter*> GetExporter();

    //setters
    void SetName(std::string name);
    void SetLevel(Level* level);
    void SetLayout(Layout* layout);
    void SetExporter(std::vector<Exporter*> exporter);


protected:
    std::string name;
    Level* level;
    Layout* layout;
    std::vector<Exporter*> exporters;
    std::vector<Logger*> child;
};


#endif /* _LOGGER_H_ */
