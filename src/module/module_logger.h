#pragma once

#include <sstream>

// https://stackoverflow.com/a/19933011
class ModuleLogger : private std::streambuf, public std::ostream
{
public:
    ModuleLogger();
    void floatingText(__int64 color);

    std::string module_name;

protected:
    int overflow(int c) override;
    void log(char c);

private:
    std::stringstream stream;

    bool floatingTextEnabled;
    __int64 floatingTextColor;
};