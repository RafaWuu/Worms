//
// Created by xguss on 04/11/23.
//

#include "common_log.h"

#include <cstdarg>
#include <iostream>
#include <string>

Log::Log(const std::string& file_name): file(file_name), msg() {}

void Log::write(const char* fmt, ...) {
    std::unique_lock<std::mutex> lck(mtx);
    va_list args;
    va_start(args, fmt);

    vsnprintf(msg, sizeof(msg), fmt, args);
    va_end(args);

    auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    if (file.is_open()) {
        file << ctime(&time) << ": Mensaje: " << msg << std::endl;
    }
}

Log::~Log() { file.close(); }
