#include "event_driven.c"

#define LED_PIN 13
#define BUT_PIN  2

void button_changed (int pin, int v) {
    digitalWrite(LED_PIN, v);
}

void initialize () {
	pinMode(LED_PIN, OUTPUT);
    button_listen(BUT_PIN);
}