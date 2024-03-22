#pragma once

#include <iostream>


enum logLevel {
  ERROR,
  WARNING,
  DEBUG,
  INFO
};


#ifdef __DEBUG__
extern logLevel LOGLEVEL;

void log(int logValue, std::string mensaje);

#define LOG(level,msg) log(level,msg)
#else
#define LOG(level,msg) 
#endif
