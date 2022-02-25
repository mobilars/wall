#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include <stdbool.h>

#include <bcm2835.h>

#include "tm1638.h"

int main(int argc, char *argv[])
{
  tm1638_p t;

  if (!bcm2835_init())
    {
      printf("Unable to initialize BCM library\n");
      return -1;
    }

  t = tm1638_alloc(20,19,21);
  if (!t)
    {
      printf("Unable to allocate TM1638\n");
      return -2;
    }

  tm1638_set_7seg_text(t, "Buttons!", 0x00);
  
  while(1)
    {
      uint8_t  x = tm1638_read_8buttons(t);
      tm1638_set_8leds(t, 0, x);

      if (x > 0 ) {
          printf("Button pressed: %i\r\n", x);

	  char text[10];
	  snprintf(text, 9, "%d ", x);
	  tm1638_set_7seg_text(t, text, 0x00);

      }

      delay(10);
    }

  tm1638_free(&t);

  return 0;
}
