#pragma once

#include "RuntimeCompiler/ICompilerLogger.h"

#include "IPlugLogger.h"

const size_t LOGSYSTEM_MAX_BUFFER = 4096;

class StdioLogSystem : public ICompilerLogger
{
public:
  virtual void LogError(const char * format, ...)
  {
    va_list args;
    va_start(args, format);
    LogInternal(format, args);
  }
  
  virtual void LogWarning(const char * format, ...)
  {
    va_list args;
    va_start(args, format);
    LogInternal(format, args);
  }

  virtual void LogInfo(const char * format, ...)
  {
    va_list args;
    va_start(args, format);
    LogInternal(format, args);
  }

protected:
  void LogInternal(const char * format, va_list args)
  {
    vsnprintf(mBuff, LOGSYSTEM_MAX_BUFFER-1, format, args);
    // Make sure there's a limit to the amount of rubbish we can output
    mBuff[LOGSYSTEM_MAX_BUFFER-1] = '\0';

    DBGMSG("RTCPP: %s\n", mBuff);
  }

  char mBuff[LOGSYSTEM_MAX_BUFFER];
};
