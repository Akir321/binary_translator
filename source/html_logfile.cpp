#include <stdio.h>
#include <ctime>
#include <sys/time.h>
#include <stdlib.h>
#include <assert.h>

#include "html_logfile.h"

const char *programName     = "Proc";
const int programNameLength = 4;
const int logFileNameLength = 64;

static FILE *fLogOpen(void);
static char *createLogFileName(const tm *openTimeSeconds, const int openTimeMiliseconds);
static void fLogClose();


FILE *LogFile = fLogOpen();

static FILE *fLogOpen()
{
    atexit(fLogClose);

    timeval openTime = {};
    time_t  openTimeSec = {};
    tm     *openTimeSeconds = NULL;
    
    if (gettimeofday(&openTime, NULL) == -1)
    {
        printf("couldn't get time for logfile name\n"); 
        return NULL;
    }
    
    openTimeSec = openTime.tv_sec;
    openTimeSeconds = localtime(&openTimeSec);

    char *name = createLogFileName(openTimeSeconds, (int) openTime.tv_usec / CLOCKS_PER_SEC);

    FILE *log = fopen(name, "w");
    if (!log) { printf("couldn't open logfile\n"); return NULL; }

    printf("logfile successfully opened: %s\n", name);
    fprintf(log, "<pre>\nI'm logfile created on %s\n", asctime(openTimeSeconds));
    fflush(log);
    free(name);

    return log;
}

static char *createLogFileName(const tm *openTimeSeconds, const int openTimeMiliseconds)
{
    assert(openTimeSeconds);
    
    char *logFileName = (char *)calloc(logFileNameLength + programNameLength, sizeof(char));
    if (!logFileName) return NULL;

    sprintf(logFileName, "log/%s_%d.%d.%d_%d.%d.%d.%d_log.html",
            programName,
            openTimeSeconds->tm_year + 1900, openTimeSeconds->tm_mon + 1, openTimeSeconds->tm_mday,
            openTimeSeconds->tm_hour, openTimeSeconds->tm_min, openTimeSeconds->tm_sec,
            openTimeMiliseconds);

    return logFileName;
}

static void fLogClose()
{
    if (LogFile) 
    {
        fclose(LogFile);

        printf("logfile successfully closed\n");
    }
    else
    {
        printf("logfile hasn't been opened\n");
    }
}
