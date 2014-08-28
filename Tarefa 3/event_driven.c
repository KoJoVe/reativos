/* Funcoes de registro: */

#define TIMERS 2
#define BUTTONS 2

int button[BUTTONS] = { 0 };
int buttonState[BUTTONS] = { 0 };
unsigned long time[TIMERS] = { 0 };
unsigned long times[TIMERS] = { 0 };

void button1_listen (int pin) {
   pinMode(pin,INPUT);
   button[0] = pin;
}

void button2_listen (int pin) {
   pinMode(pin,INPUT);
   button[1] = pin;
}

void timer1_set (int ms) {
   times[0] = ms;  
   time[0] = millis();
}

void timer2_set (int ms) {
   times[1] = ms;
   time[1] = millis(); 
}

/* Callbacks */

void button1_changed (int pin, int v);
void button2_changed (int pin, int v);
void timer1_expired (void);   
void timer2_expired (void);

/* Programa principal: */

void setup () {

    initialize(); 

}

void loop () {

	int i;
    
    for(i=0;i<BUTTONS;i++) {

    	if(button[i]!=0) {
    		
    		int x = digitalRead(button[i]);

    		if(x!=buttonState[i]) {
    			
    			buttonState[i]=x;

    			switch(i) {

    				case 0:
    					button1_changed(button[i],buttonState[i]);
    					break;
    				case 1:
    					button2_changed(button[i],buttonState[i]);
    					break;

    			}
    		}
    	}
    }
    
    unsigned long now = millis();
    
    for(i=0;i<TIMERS;i++) {
    	
    	if(times[i]>0) {
    		
    		if(now >= time[i]+times[i]) { 
    	  		
    	  		times[i] = 0;
    	  		
    	  		switch (i) {
    	  		
    	  			case 0:
    	  				timer1_expired();
    	  				break;
    	  			case 1:
    	  				timer2_expired();
    	  				break;

    	  		}
	   		}
    	} 
    }
}

