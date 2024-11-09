#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

typedef enum {
    LOG_DEBUG,
    LOG_INFO,
    LOG_WARN,
    LOG_ERROR
} LogLevel;

static LogLevel CURRENT_LOG_LEVEL = LOG_DEBUG;
static const char* LOG_LEVEL_STRINGS[] = { "DEBUG", "INFO ", "WARN ", "ERROR" };
static void (*logCallback)(LogLevel, const char*) = NULL;
static FILE* logFile = NULL;
size_t maxLogFileSize = 0;

// Flags
static bool runCbOnce = 0;
static bool colorPrinting = 0;
// End flags

void setLogLevel(LogLevel level) { CURRENT_LOG_LEVEL = level; }
const char* getLogLevelStr(LogLevel level) { return LOG_LEVEL_STRINGS[level]; }
const LogLevel getLogLevel() { return CURRENT_LOG_LEVEL; }
void setLogCallback(void (*callback)(LogLevel, const char*), bool flag) { logCallback = callback; runCbOnce = flag; }
void unsetLogCallback() { logCallback = NULL; runCbOnce = false; }
void setColorPrinting(bool flag) { colorPrinting = flag; }

// Color support
#ifdef WIN32
    #include <windows.h>
    HANDLE hConsole = NULL;
    #define COLOR_RESET ""
    #define COLOR_DEBUG FOREGROUND_BLUE
    #define COLOR_INFO FOREGROUND_GREEN
    #define COLOR_WARN FOREGROUND_RED | FOREGROUND_GREEN
    #define COLOR_ERROR FOREGROUND_RED
    void setConsoleColor(WORD color)
    {
        if (hConsole == NULL) hConsole = GetStdHandle(STD_ERROR_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }
#elif defined (linux)
    #define COLOR_RESET "\033[0m"
    #define COLOR_DEBUG "\033[34m" // Blue
    #define COLOR_INFO "\033[32m"  // Green
    #define COLOR_WARN "\033[33m"  // Yellow
    #define COLOR_ERROR "\033[31m" // Red
    void setConsoleColor(const char *color) { fprintf(stderr, "%s", color); }
#endif
// End color support

// Log file support
void setLogFile(const char* filename, size_t maxSize)
{
    if (logFile) fclose(logFile);

    logFile = fopen(filename, "a");
    maxLogFileSize = maxSize;
}
// End log file support

void checkLogFileSize()
{
    if (logFile && maxLogFileSize > 0)
    {
        fseek(logFile, 0, SEEK_END);
        size_t fileSize = ftell(logFile);
        // start fresh if full
        if (fileSize >= maxLogFileSize) { freopen(NULL, "w", logFile); }
    }
}

void logMessage(LogLevel level, const char* file, int line, const char* fmt, ...) {
    if (level < CURRENT_LOG_LEVEL) return;

    time_t currentTime = time(NULL);
    struct tm* timeInfo = localtime(&currentTime);
    char timeString[20];
    strftime(timeString, sizeof timeString, "%Y-%m-%d %H:%M:%S", timeInfo);

    char message[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(message, sizeof message, fmt, args);
    va_end(args);

    if (logCallback)
    { 
        logCallback(level, message);
        if (runCbOnce) unsetLogCallback();
    }

    if(colorPrinting)
    {
    #ifdef WIN32
        setConsoleColor(level == LOG_DEBUG ? COLOR_DEBUG :
                        level == LOG_INFO ? COLOR_INFO :
                        level == LOG_WARN ? COLOR_WARN :
                        COLOR_ERROR);
    #elif defined (linux)
        setConsoleColor(level == LOG_DEBUG ? COLOR_DEBUG :
                        level == LOG_INFO ? COLOR_INFO :
                        level == LOG_WARN ? COLOR_WARN :
                        COLOR_ERROR);
    #endif
    }
    fprintf(stderr, "[%s] %s [%s:%d] %s\n", timeString, getLogLevelStr(level), file, line, message);
    
    if(colorPrinting) setConsoleColor(COLOR_RESET);

    if (logFile)
    {
        checkLogFileSize();
        fprintf(logFile, "[%s] %s [%s:%d] %s\n", timeString, getLogLevelStr(level), file, line, message);
        fflush(logFile);
    }
}

#define logDebug(fmt, ...) logMessage(LOG_DEBUG, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define logInfo(fmt, ...)  logMessage(LOG_INFO, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define logWarn(fmt, ...)  logMessage(LOG_WARN, __FILE__, __LINE__, fmt, ##__VA_ARGS__)
#define logError(fmt, ...) logMessage(LOG_ERROR, __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#endif /* LOGGER_H */