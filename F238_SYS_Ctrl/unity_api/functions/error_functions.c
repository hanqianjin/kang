#include <stdio.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "error_functions.h"

FILE *driver_logfd = NULL;
int openLog(void)
{
	if((access("drivers.log",F_OK))!=-1) 
	{
		system("mv drivers.log drivers_bak.log");
	}
	driver_logfd = fopen("drivers.log", "a");
	if (driver_logfd == NULL) {
		printf("err open drivers.log\n");
		driver_logfd = stderr;
	}
	return 0;
}

static void
outputError(DiBoolean useErr, int err, DiBoolean flushStdout,
        const char *format, va_list ap)
{
#define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];

    vsnprintf(userMsg, BUF_SIZE, format, ap);

    if (useErr)
        snprintf(errText, BUF_SIZE, " [%s]",strerror(err));
    else
        snprintf(errText, BUF_SIZE, ":");

    snprintf(buf, BUF_SIZE, "%s %s\n",errText, userMsg);

    if (flushStdout)
        fflush(driver_logfd);       /* Flush any pending driver_logfd */
    fputs(buf, driver_logfd);
    fflush(driver_logfd);           /* In case driver_logfd is not line-buffered */
}

DiInt32
errSys_in(const char *format, ...)
{
    va_list argList;
    int savedErrno;

	if (driver_logfd == NULL) driver_logfd = stderr;

    savedErrno = errno;       /* In case we change it here */

    va_start(argList, format);
    outputError(DI_TRUE, errno, DI_TRUE, format, argList);
    va_end(argList);

    errno = savedErrno;
	
	return -1;
}

DiInt32
errUser_in(const char *format, ...)
{
    va_list argList;

	if (driver_logfd == NULL) driver_logfd = stderr;
    fflush(driver_logfd);           /* Flush any pending driver_logfd */

    va_start(argList, format);
    vfprintf(driver_logfd, format, argList);
    va_end(argList);

    fflush(driver_logfd);           /* In case driver_logfd is not line-buffered */

	return -1;
}

DiInt32
debug_in(const char *format, ...)
{
    va_list argList;

	if (driver_logfd == NULL) driver_logfd = stdout;
    fflush(driver_logfd);           /* Flush any pending driver_logfd */

    va_start(argList, format);
    vfprintf(driver_logfd, format, argList);
    va_end(argList);

    fflush(driver_logfd);           /* In case driver_logfd is not line-buffered */

	return -1;
}

