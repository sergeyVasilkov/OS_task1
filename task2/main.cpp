#include "apue.h"
#include <cstdarg>
#include <cstdio>
#include <string>

void err_quit(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    exit(EXIT_FAILURE);
}

int main(int argc, char **argv)
{
    if(argc !=2){
        err_quit("arguments < 2 ");
    }

    ssize_t size =0;
    try {
         size = std::stoi(argv[1]);
    }
    catch (std::invalid_argument &e){
        err_quit(e.what());
    }
    catch(std::out_of_range &e){
        err_quit(e.what());
    }

    if(size<0){
        err_quit("buffer size less than 0");
    }

    void* buffer = malloc(size);



    while ((read(0, buffer, size) > 0))
    {
        write (1, buffer, size);
    }
   return 0;
}