#define NEXT_LEVEL 30
#define LED_PIN 10
#define BUT_PIN 11
#define MAX 100

int counter=0;
int roundsPassed=0;
int second=0;
int rightRounds=0;

bool pressed = false;
bool roundHelp = true;
bool lost = false;

int ledPins[8] = {2,3,4,5,6,7,8,9};
/* Definicao dos numeros */
int simbolo[11][8] = 	
	{
		{1,1,1,1,1,1,0,0}, /* Zero */
		{0,1,1,0,0,0,0,0}, /* Um */
		{1,1,0,1,1,0,1,0}, /* Dois */
		{1,1,1,1,0,0,1,0}, /* Tres */
		{0,1,1,0,0,1,1,0}, /* Quatro */
		{1,0,1,1,0,1,1,0}, /* Cinco */
		{1,0,1,1,1,1,1,0}, /* Seis */
		{1,1,1,0,0,0,0,0}, /* Sete */
		{1,1,1,1,1,1,1,0}, /* Oito */
		{1,1,1,1,0,1,1,0}, /* Nove */
		{0,0,0,0,0,0,0,0}  /* NULL */
	}; 

int sequence[MAX] = {0};
int pressArray[MAX] = {0};

unsigned long timer=0;
unsigned long interval=1000;
unsigned long loopTime;

void setup()
{
  
	int i=0;

	randomSeed(analogRead(0));
	MINIGAME_pressRightNumber();
	
	timer = millis();
	
	for(i=0;i<8;i++)
	{
		pinMode(ledPins[i],OUTPUT);
		digitalWrite(ledPins[i],0);
	}
	
	pinMode(LED_PIN,OUTPUT);
	pinMode(BUT_PIN,INPUT);

}

void loop() 
{
  
	checkWrongPress();

	loopTime = millis();

	if(loopTime>timer+interval) 
	{

		checkRightPress();
		nextNumber();
		getHelp();
		checkForNextLevel();
		
		timer = millis();
	}

}

void checkForNextLevel()
{
	int i;
	if(rightRounds>6) /* Passa de nível se acertou 6 vezes seguidas */
	{
		showSymbol(simbolo[10]); /* NULL */
		for(i=0;i<5;i++)
		{
			digitalWrite(LED_PIN,HIGH);
			delay(200);
			digitalWrite(LED_PIN,LOW);
			delay(200);
		}
		delay(1000);
		MINIGAME_pressRightNumber(); /* Aqui deve ser feito o sorteio do minigame */
		roundsPassed=0;
		roundHelp=true;
		rightRounds=0;
		counter=0;
		interval-=NEXT_LEVEL;
	}
}

void getHelp() /* Funcao que faz o led acender para avisar que o jogador deve pressionar. Depois de tres acertos a ajuda para */
{
	if(pressArray[counter]==1)
	{
		if(roundHelp) /* Round help diz se o led vai acender para ajudar ou nao */
		{
			digitalWrite(LED_PIN,HIGH);
			roundsPassed += 1;
			if(roundsPassed==3)
			{
				roundHelp = false;
			}
		}
		else
		{
			digitalWrite(LED_PIN,LOW);
		}
	}
	else
	{
		digitalWrite(LED_PIN,LOW);
	}
}

void nextNumber() 
{
	counter++;

	if(counter>=MAX) 
	{
		counter = 0;
	}
	              
	second = !second;
	showSymbol(simbolo[sequence[counter]]);
	digitalWrite(ledPins[7],second); /* Aqui acende e apaga a bolinha do display, para saber se os segundos estao passando */
}

void checkWrongPress() /* Checa se o botao foi pressionado erroneamente */
{
	if(digitalRead(BUT_PIN)) 
	{
		pressed = true;
		if(pressArray[counter]==0)
		{
			loseGame();
		}
	}
}

void checkRightPress() /* Checa se o botao foi pressionado ao passar para o proximo numero */
{
	if(pressArray[counter]==1)
	{
		if(!pressed)
		{
			loseGame();
		}
		else
		{
			pressed = false;
			rightRounds++;
		}
	}
}

void loseGame() 
{
	showSymbol(simbolo[10]);
	while(true)
	{
		digitalWrite(LED_PIN,HIGH);
		delay(500);
		digitalWrite(LED_PIN,LOW);
		delay(500);
	}
}

void MINIGAME_pressRightNumber() /* Minigame padrão */
{
	int n, i, c = randomNumber(0,2); /* Sorteia qual numero deve ser apertado */
	for(i=0;i<MAX;i++) {
		n = randomNumber(0,2); /* Sorteia os numeros da sequencia */
		sequence[i] = n; 
		if(n==c) /* Se o numero for o que deve ser pressionado, iguale o pressArray a 1, mostrando que se deve pressionar nesse instante */
			pressArray[i] = 1;
		else
			pressArray[i] = 0;
	}
	showSymbol(simbolo[sequence[0]]); /* Ja acende o primeiro numero da sequencia */
	nextNumber();
	getHelp();
}

void showSymbol(int* v) 
{
	int i;

	for(i=0;i<8;i++)
	{
  		digitalWrite(ledPins[i],v[i]);
	}

}

int randomNumber(int mi, int ma) 
{
	return mi+random((ma+1)-mi);
}