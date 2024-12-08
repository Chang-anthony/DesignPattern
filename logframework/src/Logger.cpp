#include <Logger.hpp>
#include <Layout.hpp>
#include <Exporter.hpp>
#include <utils.h>
#include <set>


Logger::Logger(std::string name, Level* level, Layout* layout, std::vector<Exporter*> exporter)
{
    SetExporter(exporter);
    SetLayout(layout);
    SetLevel(level);
    SetName(name);

    layout->SetLogger(this);
    for (auto exp : exporter) {
        exp->SetLogger(this);
    }
}

Logger::Logger(Logger* parent, std::string name, Level* level, Layout* layout, std::vector<Exporter*> exporter)
{
    SetExporter(exporter);
    SetLayout(layout);
    SetLevel(level);
    SetName(name);
    parent->child.push_back(this);
    layout->SetLogger(this);
    for (auto exp : exporter) {
        exp->SetLogger(this);
    }
}

void Logger::SetName(std::string name)
{
    std::set<std::string> names;
    for (auto logger : child) {
        names.insert(logger->name);
    }

    if (names.find(name) != names.end()) {
        throw std::invalid_argument("Name already exists");
    } else {
        this->name = name;
    }
}

void Logger::SetLevel(Level* level)
{
    utils::RequireNonNull(level);
    this->level = level;
}

void Logger::SetLayout(Layout* layout)
{
    utils::RequireNonNull(layout);
    this->layout = layout;
}

void Logger::SetExporter(std::vector<Exporter*> exporter)
{
    utils::SizeShouldBigger(exporter, 1);
    this->exporters = exporter;
}

std::string Logger::GetName()
{
    return name;
}

Level* Logger::GetLevel()
{
    return level;
}

Layout* Logger::GetLayout()
{
    return layout;
}

std::vector<Exporter*> Logger::GetExporter()
{
    return exporters;
}

Logger::~Logger()
{
}