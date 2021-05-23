#include "pch.h"

#include "helpers.h"
#include "module_logger.h"

ModuleLogger::ModuleLogger()
    : std::ostream(this)
{
    this->floatingTextEnabled = false;
    this->floatingTextColor = 0;
    this->stream = std::stringstream();
}

void ModuleLogger::floatingText(__int64 color)
{
    this->floatingTextEnabled = true;
    this->floatingTextColor = color;
}

int ModuleLogger::overflow(int c)
{
    this->log(c);
    return 0;
}

void ModuleLogger::log(char c)
{
    // Continue pushing characters into the stream until we reach EOL
    if (c != '\n')
    {
        this->stream << c;
        return;
    }

    // Reached the end of this line, perform the actual logging
    std::cout << "[" << this->module_name << "] " << this->stream.str() << std::endl;

    if (this->floatingTextEnabled)
    {
        ShowFloatingText(this->stream.str().c_str(), CLEPBEMBHAJ__Enum::Notification, this->floatingTextColor);
    }

    // Reset for next log
    this->floatingTextEnabled = false;
    stream.str("");
    stream.clear();
}
