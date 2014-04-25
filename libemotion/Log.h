#ifndef Log_h__
#define Log_h__

#define LEVEL_CRITICAL  (0x00000001 << 0)
#define LEVEL_ERROR     (0x00000001 << 1)
#define LEVEL_WARN      (0x00000001 << 2)
#define LEVEL_INFOR     (0x00000001 << 3)
#define LEVEL_TRACE     (0x00000001 << 4)
#define LEVEL_DEBUG     (0x00000001 << 5)

void LogInfo(const char* fmt, ...);
void LogError(const char* fmt, ...);

#endif // Log_h__
