#include "apue.h"
#include <fcntl.h>
#include <cstdarg>
#include <errno.h>
#include <cstring>
#include <iostream>

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

 void inputData (int fd ,int size, char data[]){
     if (size != strlen(data)) {
        std::cout<<"Size and Data length are not equal !\n";
     } else{
         if (write(fd, data, size) != size) {
             err_sys("write buf1 error");
         }
     }
 }

void lseekUpdate(int fd,int size){
    if (lseek(fd, size, SEEK_SET) == -1) {
        err_sys("lseek error");
    }
}


int main(int argc, char** argv){

    const std::string DATA_INPUT = "-d";
    const std::string LSEEK_UPDATE = "-l";

    int fd;
    if ((fd = creat("file.txt", FILE_MODE)) < 0) {
        err_sys("creat error");
    }

    for(int i=0;i<argc ;i++){
       puts(argv[i]);
    }

    int count = 0;
    while(count<argc){
        if (std::string(argv[count]) == DATA_INPUT){
            inputData(fd,std::stoi(argv[count+1]),argv[count+2]);
            count+=3;
        } else if(std::string(argv[count])==LSEEK_UPDATE){
            lseekUpdate(fd,std::stoi(argv[count+1]));
            count+=2;
        } else count++;
    }
     exit(0);
}