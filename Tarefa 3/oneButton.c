#include "event_driven.c"

#define LED_PIN 13
#define BUT_PIN  2

void button1_changed (int pin, int v) {
    digitalWrite(LED_PIN, v);
}

void initialize () {
	pinMode(LED_PIN, OUTPUT);
    button1_listen(BUT_PIN);
}