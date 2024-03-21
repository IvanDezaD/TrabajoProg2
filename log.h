#pragma once

#include <iostream>

using namespace std;

enum logLevel {
  ERROR,
  WARNING,
  DEBUG,
  INFO
};


extern logLevel LOGLEVEL;

void log(int logValue, string mensaje);
