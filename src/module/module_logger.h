#pragma once

#include <sstream>

// https://stackoverflow.com/a/19933011
class ModuleLogger : private std::streambuf, public std::ostream
{
public:
    ModuleLogger();
    bool floatingText;
    __int64 color;

protected:
    int overflow(int c) override;
    void log(char c);
};
