#include "apue.h"
#include <fcntl.h>
#include <cstdarg>
#include <errno.h>

#define    MAXLINE    4096

static void err_doit(int errnoflag, int error, const char* fmt, va_list ap)
{
    char buf[MAXLINE];

    vsnprintf(buf, MAXLINE - 1, fmt, ap);
    if (errnoflag)
        snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s",
                 strerror(error));
    strcat(buf, "\n");
    fflush(stdout);        /* in case stdout and stderr are the same */
    fputs(buf, stderr);
    fflush(nullptr);        /* flushes all stdio output streams */
}

void err_sys(const char* fmt, ...)
{
    va_list ap;

    va_start(ap, fmt);
    err_doit(1, errno, fmt, ap);
    va_end(ap);
    exit(1);
}


char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
int main()
{
    int fd;
    if ((fd = creat("file.txt", FILE_MODE)) < 0) {
        err_sys("creat error");
    }
    if (write(fd, buf1, 10) != 10) {
        err_sys("write buf1 error");
    }
/* теперь текущая позиция = 10 */
    if (lseek(fd, 500000, SEEK_SET) == -1) {
        err_sys("lseek error");
    }
/* теперь текущая позиция = 500000 */
    if (write(fd, buf2, 10) != 10) {
        err_sys("write buf2 error ");
    }
/* теперь текущая позиция = 500000 */

     exit(0);
}