//Código que permite controlar a velocidade do pisca pisca de um LED utilizando um botão
//para incremento e outro botão para decremento da velocidade. Ao pressionar os dois botões
//simuntaneamente (entre um intervalo preestabelecido), o programa para.

//AINDA NÃO TESTADO NO ARDUINO 

#define LED_PIN 13
#define BUT1_PIN 3
#define BUT2_PIN 4
#define PRESS_INTERVAL 50 //Intervalo para pressionar os dois botões.
#define INTERVAL_INCREMENT 20

int interval = 100;

int state = 1;
unsigned long old;
unsigned long pressTime;
bool b1p = false;
bool b2p = false;

void setup() {
  
  old = millis();
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUT1_PIN, INPUT);
  pinMode(BUT2_PIN, INPUT);
  digitalWrite(LED_PIN, state);
  Serial.begin(9600);

}

void loop() {
  
  unsigned long now = millis();
  int but1 = digitalRead(BUT1_PIN);
  int but2 = digitalRead(BUT2_PIN);
  
  if(now >= old+interval) {
    old = now;
    state = !state;
    digitalWrite(LED_PIN, state);
    Serial.println(state);
    Serial.println(interval);
  }

  if(but1) {
    if(!b1p) {
      interval += INTERVAL_INCREMENT;
      b1p = true;
      if(!but2)  
        pressTime = now;
    } else {
      if(now <= pressTime+PRESS_INTERVAL&&but2) 
        while(1);
    }
  } else {
    b1p = false;
  }

  if(but2) {
    if(!b2p) {
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