#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define SERIAL_R 15500


#define B 3950 // B-коэффициент
#define SERIAL_R 39000 // сопротивление последовательного резистора, 102 кОм
#define THERMISTOR_R 39000 // номинальное сопротивления термистора, 100 кОм
#define NOMINAL_T 25 // номинальная температура (при которой TR = 100 кОм)

const byte tempPin = A0;


const byte interruptPin = 2;
int count = 0;
// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x3f, 16, 2);

void setup()
{
  Serial.begin( 115200 );
	// initialize the LCD
	lcd.begin();

	// Turn on the blacklight and print a message.
	lcd.backlight();
	lcd.print("Hello, world!");
 //pinMode(interruptPin, INPUT);
  ///attachInterrupt(0, blink, RISING);
  attachInterrupt(0, blink, RISING);
  pinMode( tempPin, INPUT );
}

void loop()
{
   int t = analogRead( tempPin );
    float tr = 1023.0 / t - 1;
    tr = SERIAL_R / tr;
    Serial.print("R=");
    Serial.print(tr);
    Serial.print(", t=");

    float steinhart;
    steinhart = tr / THERMISTOR_R; // (R/Ro)
    steinhart = log(steinhart); // ln(R/Ro)
    steinhart /= B; // 1/B * ln(R/Ro)
    steinhart += 1.0 / (NOMINAL_T + 273.15); // + (1/To)
    steinhart = 1.0 / steinhart; // Invert
    steinhart -= 273.15; 
    Serial.println(steinhart);
    
  
	lcd.clear();
  lcd.print("W = ");
  lcd.print(count);
  lcd.setCursor(0,1);
  lcd.print("T = ");
  lcd.print(steinhart);
  //lcd.print(T);
  delay(500);
}

void blink() {
  count++;
}
