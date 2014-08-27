/* Funções de registro: */

void button_listen (int pin) {
   <...>                    // “pin” passado deve gerar notificações
}

void timer_set (int ms) {
   <...>                    // timer deve expirar após “ms” milisegundos
}

/* Callbacks */

void button_changed (int pin, int v);  // notifica que “pin” mudou para “v”
void timer_expired (void);             // notifica que o timer expirou

/* Programa principal: */

void setup () {
    <...>                   // inicialização da API
    init();                 // inicialização do usuário
}

void loop () {
    <...>                   // detecta novos eventos
    button_changed(...);    // notifica o usuário
    <...>                   // detecta novos eventos
    timer_expired(...);     // notifica o usuário
}