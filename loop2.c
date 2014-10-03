#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int i=0;
    while(1)
    {
        printf("Numero da soma: %d\n", i);
        i++;
    }
}