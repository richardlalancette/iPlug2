#include "StdioLogSystem.h"

// Currently we create the file on first real output, and only close it on shutdown

#include <stdarg.h>
#include <assert.h>

#include "IPlugLogger.h"

void StdioLogSystem::LogError(const char * format, ...)
{
  va_list args;
  va_start(args, format);
  LogInternal(format, args);
}

void StdioLogSystem::LogWarning(const char * format, ...)
{
  va_list args;
  va_start(args, format);
  LogInternal(format, args);
}

void StdioLogSystem::LogInfo(const char * format, ...)
{
  va_list args;
  va_start(args, format);
  LogInternal(format, args);
}
void StdioLogSystem::LogInternal(const char * format, va_list args)
{
  int result = vsnprintf(mBuff, LOGSYSTEM_MAX_BUFFER-1, format, args);
  // Make sure there's a limit to the amount of rubbish we can output
  mBuff[LOGSYSTEM_MAX_BUFFER-1] = '\0';

  DBGMSG("RTCPP: %s\n", mBuff);
}

