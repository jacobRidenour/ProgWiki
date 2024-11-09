#include <stdio.h>

#include "Logger.h"

// Ideas and inspiration from this simple library:
// https://github.com/rxi/log.c
// The above is no longer maintained, but this fork is:
// https://github.com/an-dr/microlog
// (also has C++ support)

void logCb(LogLevel level, const char* message)
{
    static int called = 1;
    printf("\t- [%s] callback tripped ", getLogLevelStr(level));
    if (called == 1) printf("%d time\n", called++);
    else printf("%d times\n", called++);
}


void oneTimeLogCb(LogLevel level, const char* message)
{
    printf("\tyou will get 7 logs of good luck upon reading this :)\n");
}

int main() {
    // check log level functionality
    setLogLevel(LOG_INFO);
    logDebug("This debug message will not appear.");
    logInfo("Information you should know!");

    // test callback: only run it once
    setLogCallback(oneTimeLogCb, true);

    // Log file -> "app.log", max size of 10 KiB
    setLogFile("app.log", 1024 * 10); 
    logWarn("CPU usage over 90%% for the last 12 hours");

    // test callback: run repeatedly
    setLogCallback(logCb, false);
    // test color printing
    setColorPrinting(true);

    logInfo("Go go go!");
    logWarn("Slow down");
    logError("segmentation fault");

    return 0;
}
