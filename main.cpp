#include <cstdlib>
#include <iostream>
#include <cstring>
#include "Logger.hpp"
#include <boost/filesystem.hpp>

int main()
{
    Logger* log = new Logger();
    log->Timestamp();
    log->SetDir("/Users/bryan/Log");
    log->CheckFiles(1,10);
    log->TrackInit();
    log->LogInit();
    std::cout << "Test" << std::endl;
    return 0;
}
