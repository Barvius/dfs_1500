#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;


const byte interruptPin = 2;
int count = 0;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup()
{
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
 //pinMode(interruptPin, INPUT);
  attachInterrupt(0, blink, RISING);
}

void loop()
{

Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  T = (T * 9.0)/ 5.0 ; 

  
	lcd.clear();
  lcd.print("W = ");
  lcd.print(count);
  lcd.print("T = ");
  lcd.print(T);
  delay(100);
}

void blink() {
  count++;
}
