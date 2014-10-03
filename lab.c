#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/shm.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{

    int segmento1, *pid1, *pid2, segmento2, i;

    segmento1 = shmget (IPC_PRIVATE,sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);
    segmento2 = shmget (IPC_PRIVATE,sizeof(int), IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR);

    *pid1 = (int*) shmat (segmento1, 0, 0);
    *pid2 = (int*) shmat (segmento2, 0, 0);

    if(fork())
    {
        if(fork())
        {
            kill(*pid1,SIGINT);
            kill(*pid2,SIGINT);
            for(i=0;i<1;i++)
            {
                kill(*pid1,SIGCONT);
                kill(*pid2,SIGINT);
                sleep(1);
                kill(*pid1,SIGINT);
                kill(*pid2,SIGCONT);
                sleep(1);
            }
            kill(*pid1,SIGKILL);
            kill(*pid2,SIGKILL);
        }        
        else 
        {
            static char *argv1[]={NULL};
                   *pid1=execv("loop1",argv1);
        }
    }
    else    
    {
        static char *argv2[]={NULL};
            *pid2=execv("loop2",argv2);
    }
    return(0);
    shmdt (pid1);
    shmdt (pid2);
    shmctl (segmento1, IPC_RMID, 0);    
    shmctl (segmento2, IPC_RMID, 0);
}