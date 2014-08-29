#include "event_driven.c"

#define LED_PIN 13
#define BUT_PIN1 2
#define BUT_PIN2 3

bool button1State = false;
bool button2State = false;
bool timeExpired = true;
bool timeBegin = false;
int ledState = 0;
unsigned long interval = 1000;
unsigned long delay = 500;

void stopLED () {
	digitalWrite(LED_PIN,0);
	exit(1);
}

void button1_changed (int pin, int v) {
	if(v==1) {
	    interval -= 100;
		timer1_set(interval);
		button1State = true;
		if(!timeBegin) {
			timeBegin = true;
			timer2_set(delay);
			timeExpired = false;
		}
		if(button2State==true&&timeExpired!=true) {
			stopLED();
		}
	} else {
		button1State = false;
		timeBegin = false;
	}
}

void button2_changed (int pin, int v) {
	if(v==1) {
	    interval += 100;
		timer1_set(interval);
		button2State = true;
		if(!timeBegin) {
			timeBegin = true;
			timer2_set(delay);
			timeExpired = false;
		}
		if(button1State==true&&timeExpired!=true) {
			stopLED();
		}
	} else {
		button2State = false;
		timeBegin = false;
	}
}

void timer1_expired() {
	ledState = !ledState;
	digitalWrite(LED_PIN,ledState);
}

void timer2_expired() {
	timeExpired = true;
}

void initialize () {
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN,ledState);
	timer1_set(interval);
    button1_listen(BUT_PIN1);
	button2_listen(BUT_PIN2);
}

