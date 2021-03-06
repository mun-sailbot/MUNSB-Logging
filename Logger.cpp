#include "Logger.hpp"
#include <string>
#include <boost/filesystem.hpp>


void Logger::Timestamp(){
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );
    timestamp = strftime(buffer, sizeof(buffer),"%Y%m%d_%H%M%S",now);
}

void Logger::SetDir(std::string dir){
    const char * c = dir.c_str();
    sprintf(logdir, "%s", c);
}

void Logger::LogInit() {
    std::ofstream fout;
    sprintf(name, "%s/%s.txt", logdir, buffer);
    fout.open(name, std::ios::out | std::ios::app);
    fout << "Initialized...starting main loop!" << std::endl;
    fout.close();
}

void Logger::TrackInit() {
    sprintf(name, "%s/%s.csv", logdir, buffer);
    std::ofstream tout;
    tout.open (name, std::ios::out | std::ios::app);
    tout << "CourseToPoint,DistanceToPoint,SailState,BoatSpeed,Lat,Lon,GPSHeading,WindDirection,MagHeading" << std::endl;
    tout.close();
}

void Logger::LogStep() {
    std::ofstream fout;
    sprintf(name, "%s/%s.txt", logdir, buffer);
    fout.open(name, std::ios::out | std::ios::app);
    
    fout << "Waypoint: " << std::endl;
    
    fout.close();
}


void Logger::TrackStep() {
    sprintf(name, "%s/%s.csv", logdir, buffer);
    std::ofstream tout;
    tout.open (name, std::ios::out | std::ios::app);
    tout << "YEahhhh" << std::endl;
    tout.close();
}

// Delete all files older than n days or files are larger than m MB
void Logger::CheckFiles(uint8_t n, uint8_t mb) {
    char* buf;
    DIR *dir = opendir(logdir);
    if(!dir) {
        asprintf(&buf,"exec mkdir -p %s", logdir);
        system(buf);
        delete buf;
    }
    long size = 0;
    struct stat t_stat;
    struct dirent *next_file;
    char filepath[256];
    time_t now = time(&now);
    while ( (next_file = readdir(dir)) != NULL )
    {
        sprintf(filepath, "%s/%s", logdir, next_file->d_name);
        stat(filepath, &t_stat);
        size += t_stat.st_size;
        if ((now-t_stat.st_mtime) > (n * 86400)) remove(filepath);
    }
    if (size > (mb*10000000)) {
        while (size > (mb*10000000))
        {
            next_file = readdir(dir);
            sprintf(filepath, "%s/%s", logdir, next_file->d_name);
            stat(filepath, &t_stat);
            remove(filepath);
            size -= t_stat.st_size;
        }
    }
    closedir(dir);
}
