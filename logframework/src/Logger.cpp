#include <Logger.hpp>
#include <Layout.hpp>
#include <Exporter.hpp>
#include <Log.hpp>
#include <utils.h>
#include <set>


Logger::Logger(std::string name, Level level, Layout* layout, Exporter* exporter)
{
    SetExporter(exporter);
    SetLayout(layout);
    SetLevel(level);
    SetName(name);

    layout->SetLogger(this);
    exporter->SetLogger(this);
}

void Logger::trace(std::string message)
{
    if (CheckThreshold(Level::TRACE)) {
        exporter->output(layout->format(message));
    }
}

void Logger::debug(std::string message)
{
    if (CheckThreshold(Level::DEBUG)) {
        exporter->output(layout->format(message));
    }
}

void Logger::info(std::string message)
{
    if (CheckThreshold(Level::INFO)) {
        exporter->output(layout->format(message));
    }
}

void Logger::warn(std::string message)
{
    if (CheckThreshold(Level::WARN)) {
        exporter->output(layout->format(message));
    }
}

void Logger::error(std::string message)
{
    if (CheckThreshold(Level::ERROR)) {
        exporter->output(layout->format(message));
    }
}

bool Logger::CheckThreshold(Level level)
{
    Level loggerLevel = level;
    return loggerLevel >= this->level;
}

void Logger::SetName(std::string name)
{
    std::set<std::string> names;

    if (names.find(name) != names.end()) {
        throw std::invalid_argument("Name already exists");
    } else {
        this->name = name;
    }
}

void Logger::SetLevel(Level level)
{
    this->level = level;
}

void Logger::SetLayout(Layout* layout)
{
    utils::RequireNonNull(layout);
    this->layout = layout;
}

void Logger::SetExporter(Exporter* exporter)
{
    utils::RequireNonNull(exporter);
    this->exporter = exporter;
}

std::string Logger::GetName()
{
    return name;
}

Level Logger::GetLevel()
{
    return level;
}

Layout* Logger::GetLayout()
{
    return layout;
}

Exporter* Logger::GetExporter()
{
    return exporter;
}

Logger::~Logger()
{
}