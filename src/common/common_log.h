//
// Created by xguss on 04/11/23.
//

#ifndef WORMS_COMMON_LOG_H
#define WORMS_COMMON_LOG_H

#include <fstream>
#include <mutex>
#include <string>


// Okay, capaz era preferible utilizar `syslog` (man syslog)
// tiene algunos beneficios, como automaticamente poner fecha y hora
// niveles de log (WARNING, DEBUG, ERROR, etc)
class Log {
private:
    std::mutex mtx;
    std::ofstream file;
    char msg[256];

public:
    explicit Log(const std::string& file_name);
    ~Log();
    void write(const char* fmt, ...);
};
#endif  // WORMS_COMMON_LOG_H
