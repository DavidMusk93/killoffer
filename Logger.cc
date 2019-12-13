#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "Logger.h"

namespace sun
{

class Vararg
{
 public:
  ~Vararg() { va_end(list_); }

  va_list& GetList() { return list_; }

 private:
  va_list list_;
};

Logger::Logger() { buf_[kBufferSize] = 0; }

void Logger::Info(const char *fmt, ...)
{
  // int n;
  Vararg va;
  va_start(va.GetList(), fmt);
  (void)vsnprintf(buf_, kBufferSize, fmt, va.GetList());
  // // Append new line by default
  // if (n >= kBufferSize)
  //   buf_[kBufferSize - 1] = '\n';
  // else
  //   buf_[n] = '\n';
  puts(buf_);
}

// Static variable should be initialized after Ctor
Logger Logger::instance = Logger();

Logger& Logger::GetInstance() { return instance; }

}
