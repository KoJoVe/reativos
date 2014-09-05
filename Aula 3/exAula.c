#include <stdio.h>
#include <signal.h>
#include <stdlib.h> 
#define EVER ;; 

void intHandler(int al); 
void quitHandler(int al); 

int main (void) {

    void (*p)(int); // ponteiro para função que recebe int como // parâmetro
    p = signal(SIGINT, intHandler);
    printf("Endereco do manipulador anterior %p\n", p);
    p = signal(SIGQUIT, quitHandler);
    printf("Endereco do manipulador anterior %p\n", p);
    puts ("Ctrl-C desabilitado. Use Ctrl-\\ para terminar");
    for(EVER);

}

void intHandler(int al) {
    printf("Você pressionou Ctrl-C (%d)", al);
}

void quitHandler(int al) {
    puts ("Terminando o processo...");
    exit (0);
}