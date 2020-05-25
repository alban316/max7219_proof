//THIS IS IT!!! THIS IS THE ONE THAT WORKS!!!!



#include <SPI.h>

#define REG_DECODE (0x09)
#define REG_DIGIT(pos) ((pos) + 1)
#define REG_INTENSITY (0x0A)
#define REG_SCANLIMIT (0x0B)
#define REG_SHUTDOWN (0x0C)
#define REG_DISPLAYTEST (0x0F)

#define ON (0x1)
#define OFF (0x0)



void set_register(byte address, byte value)
{
  digitalWrite(SS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(SS, HIGH);
}


void init_doggydoo()
{
  set_register(REG_DISPLAYTEST, OFF);
  set_register(REG_INTENSITY, 0x8);
  set_register(REG_SHUTDOWN, OFF);
  set_register(REG_SCANLIMIT, 7);
  set_register(REG_DECODE, B00000000);
}



void setup (void) {
  digitalWrite(SS, HIGH);
  SPI.begin();
  SPI.beginTransaction(SPISettings(20000, MSBFIRST, SPI_MODE0));

  init_doggydoo();
}



void loop (void) {
  set_register(REG_SHUTDOWN, OFF);

  for (int i = 0; i < 8; i++)
  {
      if (i % 2 == 0)
        set_register(REG_DIGIT(i), 85);

      else
        set_register(REG_DIGIT(i), 170);


  }

  set_register(REG_SHUTDOWN, ON);

  delay(2000);
}
