//Tarefa 2 de sistemas reativos
//Programa que controla a velocidade do pisca pisca de um LED atraves de dois botoes.
//Um botao serve para aumentar a frequencia com que a luz pisca e outro serve para diminuir.
//O botao so faz efeito a cada pressionada. Segurar o botao so ira modificar o tempo uma vez.
//Apertar os dois botoes simuntaneamente (entre um intervalo predefinido), congela o programa.

#define LED_PIN 13
#define BUT1_PIN 3
#define BUT2_PIN 4
#define PRESS_INTERVAL 50 //Intervalo de tempo entre a ativacao dos dois botoes para desligar o programa.
#define INTERVAL_INCREMENT 20 //Quantidade de tempo a ser modificada ao pressionar de um botao.

int interval = 100; //Intervalo (milisegundos) para o LED mudar seu estado.

int state = 1; //Estado inicial do LED (1 para ligado, 0 para desligado).
unsigned long old;
unsigned long pressTime;
bool b1p = false; //Variaveis para identificacao de quais botoes estao sendo pressionados.
bool b2p = false;

void setup() {
  
  old = millis();
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT1_PIN, INPUT);
  pinMode(BUT2_PIN, INPUT);
  digitalWrite(LED_PIN, state);

}

void loop() {
  
  unsigned long now = millis();
  int but1 = digitalRead(BUT1_PIN);
  int but2 = digitalRead(BUT2_PIN);
  
  if(now >= old+interval) { //Realiza a modificacao do estado do LED de acordo com o intervalo atual.
    old = now;
    state = !state;
    digitalWrite(LED_PIN, state);
  }

  if(but1) { //Botao 1
    if(!b1p) { //Verifica se o botao ja esta pressionado.
        interval += INTERVAL_INCREMENT;
      b1p = true;
      if(!but2) //Verifica se o outro botao ja esta pressionado.
        pressTime = now; //Registra o momento em que o botao foi pressionado.
    } else { //Caso o botao esteja pressionado, ao pressionar o outro dentro do intervalo de tempo definido o programa para.
      if(now <= pressTime+PRESS_INTERVAL&&but2) 
        while(1);
    }
  } else {
    b1p = false;
  }

  if(but2) {
    if(!b2p) {
      if(interval>INTERVAL_INCREMENT*2)
        interval -= INTERVAL_INCREMENT;
      b2p = true;
      if(!but1)
        pressTime = now;
    } else {
      if(now <= pressTime+PRESS_INTERVAL&&but1) 
        while(1);
    }
  } else {
    b2p = false;
  }
  
}