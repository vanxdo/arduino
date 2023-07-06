#include <LiquidCrystal.h>
#include <Wire.h>

#define piezo 9
const int rs = 12, en = 11, d4 = 2, d5 = 3, d6 = 4, d7 = 5; // declaring LCD pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
    pinMode (piezo, OUTPUT);  // declaring peripheral I/O ports
    pinMode (0, INPUT);
    Serial.begin(9600);
    lcd.begin(16, 2); // initiallizing 16x2 LCD module 
    lcd.print("Sensor warming.."); // Allowing heating current to warm the sensor
    delay(10000);
    lcd.clear();  // Clear LCD screen for test results
}

 
void loop() {
  float SensorValue = analogRead(0);
  float Breath = SensorValue / 1024;  
  float ratio = .21;   // conversion of presence of alcohol per liter in blood
  float BAC = Breath * ratio; 

 
  Serial.println(SensorValue); // monitoring values for testing & debugging
  Serial.println(Breath,3); // precision decimal points
  Serial.println(BAC,3); // precision decimal points
    
      if (BAC >.079) // Drunken limit 
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("BAC = ");
       lcd.print(BAC); // extra spaces are intentional for clearing row of unnecessary characters
       lcd.print("%             ");
        lcd.setCursor(0,1);
        lcd.print("DO NOT DRIVE    ");
        digitalWrite(9, HIGH);
        delay(250);
        digitalWrite(9, HIGH);
        delay(250);
        digitalWrite(9, HIGH);
      }
      
            else if ((BAC > .02) && (BAC < .079))       // threshold for detected drunkeness
      { 
    lcd.clear();
    lcd.setCursor(0,0); // first line measurements
    lcd.print("BAC = ");
        lcd.print(BAC); // extra spaces are intentional for clearing row of unnecessary characters
        lcd.print("%     ");
         lcd.setCursor(0,1);
        lcd.print("DRINK WATER     "); 
        
      }
        
      else {                      // Below the limit
        lcd.clear();
    lcd.setCursor(0,0); // first line measurements
    lcd.print("BAC = 0.00%     ");
    lcd.setCursor(0,1);
    lcd.print("NOT DETECTED    "); // extra spaces are intentional for clearing row of unnecessary characters
}
}
      
