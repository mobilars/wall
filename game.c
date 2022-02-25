#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <wiringPi.h>

#include <bcm2835.h>

#include "tm1638.h"

#define Y_LED 7
#define B_LED 0
#define W_LED 1
#define R_LED 2
#define G_LED 6

#define Y_BTN 21
#define B_BTN 22
#define W_BTN 26
#define R_BTN 23
#define G_BTN 27

#define BUZZ 5

int init();
void buzz();
void led(int which, int value);
int handleButtons();
void resetLeds();
void flash(int times);
int waitForButton(int which);

tm1638_p t;
int lastButton = 0;

/*
4 5 3 
2   1
*/

char progs[8][6]= {
	{1,3,5,4,2,4},
	{1,2,1,2,1,2},
	{1,3,4,2,4,3},
	{1,3,5,4,5,3},
	{2,4,5,4,5,2},
	{2,5,1,4,2,1},
	{1,2,4,5,2,1},
	{1,2,4,2,4,1}
};

char text[10];

int main(int argc, char *argv[])
{
  
	init();
  
	flash(2);
	
	tm1638_set_7seg_text(t, "SELECT", 0x00);
	
	while (1) {
	
		tm1638_set_8leds(t, 0xFF, 0xFF);
		buzz();
		buzz();
		buzz();
		buzz();
	
		int program = 1; //handleButtons();
		while (program == 0) {
			program = handleButtons();
			delay(10);
		}
		
		uint8_t x = tm1638_read_8buttons(t);
		while (x != 0) {
			x = tm1638_read_8buttons(t);
		}
		
		time_t start = time(NULL);
		struct tm *tm = localtime(&start);
			
		printf("Program selected: %i\r\n", program);
		snprintf(text, 9, "START %d", 9-program);
		tm1638_set_7seg_text(t, text, 0x00);
		buzz();
		buzz();
		
		resetLeds();
		
		int count = 0;
		for (count = 0; count < 6; count++) {
			tm1638_set_8leds(t, 0, 1 << count);
			led(progs[program-1][count],1);
			int pressed = waitForButton(progs[program-1][count]);
			if (pressed == 0) { count = 8; break; }
			buzz();
			
			time_t now    = time(NULL);
			struct tm *tm = localtime(&now);
			double passed = difftime(now, start);
			
			snprintf(text, 9, "%d SEC", (int)passed);
			tm1638_set_7seg_text(t, text, 0x00);
			
			led(progs[program-1][count],0);
		}
	
	}
  
  /*
  while(1)
    {
		handleButtons();
		delay(10);
    }
	*/
	
  tm1638_free(&t);

  return 0;
}

int handleButtons()
{
	uint8_t x = tm1638_read_8buttons(t);
	if (x == lastButton) { return 0; }
	lastButton = x;
	
	if (x > 0) {
		//tm1638_set_8leds(t, 0, x);
		char text[10];
		//snprintf(text, 9, "%d ", x);
		//tm1638_set_7seg_text(t, text, 0x00);
	}
	
	switch (x) {
	
	case 1: 
		return 1;
		
	case 2: 
		return 2;
		
	case 4: 
		return 3;
		
	case 8: 
		return 4;
		
	case 16: 
		return 5;
		
	case 32: 
		return 6;
		
	case 64: 
		return 7;
		
	case 128: 
		return 8;
		
	default:
		return 0;
	}

}

void resetLeds() {
	led(1,0);
	led(2,0);
	led(3,0);
	led(4,0);
	led(5,0);
}

void flash(int times) {

	int i = 0;

	for (i = 0; i < times; i++) {
		led(1,1);
		led(2,1);
		led(3,1);
		led(4,1);
		led(5,1);
		delay(50);
		led(1,0);
		led(2,0);
		led(3,0);
		led(4,0);
		led(5,0);
		delay(50);
	}
}

int waitFor(int button) {
	int b = digitalRead (button);
	while (b == 0) {
		b = digitalRead (button);
		uint8_t x = tm1638_read_8buttons(t);
		if (x > 0) { 
			return 0;
		}
	}
	return b;
}

int waitForButton(int which) {

	switch(which) {

		case 1 :
			return waitFor(Y_BTN);
			break;
		  
		case 2 :
			return waitFor(B_BTN);
			break;
		  
		case 3 :
			return waitFor(W_BTN);
			break;
		  
		case 4 :
			return waitFor(R_BTN);
			break;
		  
		case 5 :
			return waitFor(G_BTN);
			break;
		  
		default : 
			return 0;
		}
}


void led(int which, int value) {

switch(which) {

   case 1 :
	  digitalWrite(Y_LED, value);
      break; 
	
   case 2 :
	  digitalWrite(B_LED, value);
      break; 
	
   case 3 :
	  digitalWrite(W_LED, value);
      break; 
	
   case 4 :
	  digitalWrite(R_LED, value);
      break; 
	
   case 5 :
	  digitalWrite(G_LED, value);
      break; 
	
   default : 
   ;
}

}

void buzz() {
	int i = 0;
	for (i = 0; i < 50; i++) {
		digitalWrite(BUZZ, 0);
		delay(1);
		digitalWrite(BUZZ, 1);
		delay(1);
	}
}

int init()
{

	if (!bcm2835_init())
    {
		printf("Unable to initialize BCM library\n");
		return -1;
    }

	t = tm1638_alloc(20,19,21);
	if (!t) {
		printf("Unable to allocate TM1638\n");
		return -2;
    }
	
	wiringPiSetup () ;
	
	pinMode(BUZZ,OUTPUT);
	
	pinMode(Y_LED, OUTPUT);
	pinMode(B_LED, OUTPUT);
	pinMode(W_LED, OUTPUT);
	pinMode(R_LED, OUTPUT);
	pinMode(G_LED, OUTPUT);

	pinMode(Y_BTN, INPUT);
	pinMode(B_BTN, INPUT);
	pinMode(W_BTN, INPUT);
	pinMode(R_BTN, INPUT);
	pinMode(G_BTN, INPUT);

	pullUpDnControl (Y_BTN, PUD_DOWN);
	pullUpDnControl (B_BTN, PUD_DOWN);
	pullUpDnControl (W_BTN, PUD_DOWN);
	pullUpDnControl (R_BTN, PUD_DOWN);
	pullUpDnControl (G_BTN, PUD_DOWN);
  
}
