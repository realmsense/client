#include "pch.h"
#include "module_logger.h"

#include <sstream>

ModuleLogger::ModuleLogger()
    : std::ostream(this)
{
    this->floatingText = false;
    this->color = 0;
}

int ModuleLogger::overflow(int c)
{
    this->log(c);
    return 0;
}

void ModuleLogger::log(char c)
{
    static std::stringstream stream;
    if (c != '\n')
    {
        stream << c;
    }
    else
    {
        std::cout << stream.str() << std::endl;

        if (this->floatingText && g_pPlayer)
        {
            ShowFloatingText(stream.str().c_str(), FloatingText(0), this->color);
        }

        stream.str("");
        stream.clear();
    }
}

