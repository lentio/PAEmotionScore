#include "pch.h"
#include "log.h"
#include "stdarg.h"

#ifdef __ANDROID__
#include "android/log.h"

const char* LOG_TAG_ERROR = "EMOTION_ERROR";
const char* LOG_TAG_INFOR = "EMOTION_INFOR";

void LogInfo( const char* fmt, ... )
{
    va_list args;
    va_start (args, fmt);
    __android_log_vprint(ANDROID_LOG_INFO, LOG_TAG_INFOR, fmt, args);
    va_end (args);
}

void LogError( const char* fmt, ... )
{
    va_list args;
    va_start (args, fmt);
    __android_log_vprint(ANDROID_LOG_ERROR, LOG_TAG_ERROR, fmt, args);
    va_end (args);
}
#elif defined(WIN32)

#include <windows.h>
void LogInfo(const char* fmt, ...) {
    char buf[2048] = "[INFOR]";

    va_list args;
    va_start(args, fmt);
    vsprintf(buf + strlen(buf), fmt, args);
    va_end(args);

    OutputDebugStringA(buf);
}

void LogError(const char* fmt, ...) {
    char buf[2048] = "[ERROR]";

    va_list args;
    va_start(args, fmt);
    vsprintf(buf+strlen(buf), fmt, args);
    va_end(args);

    OutputDebugStringA(buf);
}
#else

void LogInfo(const char* fmt, ...) {
    char buf[2048] = "[INFOR]";
    
    va_list args;
    va_start(args, fmt);
    vsprintf(buf + strlen(buf), fmt, args);
    va_end(args);
    
    //NSString *output = [NSString stringWithUTF8String:buf];
    //NSLog(@"%s", buf);
}

void LogError(const char* fmt, ...) {
    char buf[2048] = "[ERROR]";
    
    va_list args;
    va_start(args, fmt);
    vsprintf(buf+strlen(buf), fmt, args);
    va_end(args);
    
    //NSString *output = [NSString stringWithUTF8String:buf];
    //NSLog(@"%s", buf);
}
#endif/*_WIN32*/
