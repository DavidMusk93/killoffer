#pragma once

namespace sun
{

class Logger {
 public:
  void Debug(const char *fmt, ...);
  void Info(const char *fmt, ...);
  void Error(const char *fmt, ...);

  static Logger& GetInstance();

 private:
  Logger();

  char buf_[1024];

  static Logger instance;
  static constexpr int kBufferSize = sizeof(buf_) - 1;
};

}

#define Log(fmt, ...) sun::Logger::GetInstance().Info(fmt, ##__VA_ARGS__)
