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

 void inputData (int fd ,char sizeChar[], char data[]){
int size =0;
    try {
        size = std::stoi(sizeChar);
     }
    catch (std::invalid_argument &e){
        std::cout<<e.what();
        return;
    }
    catch(std::out_of_range &e){
        std::cout<<e.what();
        return;
    }

    if(size <= 0){
        std::cout<<"Size equal or less zero"<<std::endl;
        return;
    } else if (size != strlen(data)) {
        std::cout<<std::endl<<"Size and Data length are not equal !\n";
     } else{
         if (write(fd, data, size) != size) {
             err_sys("write buf1 error");
         }
     }
 }

void lseekUpdate(int fd,char sizeChar[]){
    int size =0;
    try {
        size = std::stoi(sizeChar);
    }
    catch (std::invalid_argument &e){
        std::cout<<e.what();
    }
    catch(std::out_of_range &e){
        std::cout<<e.what();
    }
    if (lseek(fd, size, SEEK_SET) == -1) {
        err_sys("lseek error");
    }
}


int main(int argc, char** argv){
    if(argc < 3){
        std::cout<<"less than two arguments"<<std::endl;
        exit(0);
    }

    const std::string DATA_INPUT = "-d";
    const std::string LSEEK_UPDATE = "-l";

    int fd;
    if ((fd = creat("file.txt", FILE_MODE)) < 0) {
        err_sys("creat error");
    }


    int count = 0;

    while(count<argc){
        if (std::string(argv[count]) == DATA_INPUT){
            if(count+2<=argc) {
                if (std::string(argv[count + 1]) == "-l" || std::string(argv[count + 2]) == "-l") {
                    std::cout << "Incorrect arguments" << std::endl;
                    break;
                } else {
                    inputData(fd, argv[count + 1], argv[count + 2]);
                    count += 3;
                }
            }
            else {
                std::cout<<"Potential arguments for dataInput out of range"<<std::endl;
                break;
            }
        } else if(std::string(argv[count])==LSEEK_UPDATE){
            if(count+2<argc) {
                if (std::string(argv[count + 1]) == "-d") {
                    std::cout << "Incorrect arguments" << std::endl;
                    break;
                } else {
                    lseekUpdate(fd, argv[count + 1]);
                    count += 2;
                }
            }
            else{
                std::cout<<"Potential arguments for lseek out of range"<<std::endl;
                break;
            }
        } else count++;
    }
     exit(0);
}