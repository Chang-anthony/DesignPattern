#include <Log.hpp>


Log::Log(std::string name, Level level, Layout* layout, Exporter* exporter): Logger(name, level, layout, exporter)
{
}

Log::Log(Log* parent, std::string name, Level level, Layout* layout, Exporter* exporter): Logger(name, level, layout, exporter)
{
    parent->child.push_back(this);
}

std::vector<Logger*> Log::GetChild()
{
    return child;
}

void Log::SetChild(std::vector<Logger*> child)
{
    this->child = child;
}

Logger* Log::GetLog(std::string name)
{
    if (this->name == name ){
        return this;
    }

    for (auto log : child) {
        if (log->GetName() == name) {
            return log;
        }
    }
    return nullptr;
}

Log::~Log()
{
}
