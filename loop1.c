#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int i=1;
    while(1)
    {
        printf("Numero um: %d\n", i);
    }
}