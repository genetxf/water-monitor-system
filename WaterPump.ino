// Echo Pin of Ultrasonic Sensor is A0
// Trigger Pin of Ultrasonic Sensor is A1
// LCD RS pin to digital pin 2
// LCD EN pin to digital pin 3
// LCD D4 pin to digital pin 4
// LCD D5 pin to digital pin 5
// LCD D6 pin to digital pin 6
// LCD D7 pin to digital pin 7
// LCD R/W pin to ground
// LCD VSS pin to ground
// LCD VCC pin to 5V
// ends to +5V and ground
// wiper to LCD VO pin (pin 3)
// Relay pin to digital pin 8
// Buzzer to digital pin 9
// LED Arduino ON (G) to digital pin 10
// LED Motor ON (G) to digital pin 11
// LED Motor OFF (R) to digital pin 12


#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
long duration, inches, motor_status = 0;

void setup()
{
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Automatic  Water");
  lcd.setCursor(0, 1);
  lcd.print("  Pump  System  ");

  tone(9, 1296, 125);
  delay(130);
  tone(9, 1540, 125);
  delay(130);
  tone(9, 2590, 125);
  delay(130);
  tone(9, 2055, 125);
  delay(130);
  tone(9, 2307, 125);
  delay(130);
  tone(9, 3079, 125);
  delay(125);
  noTone(9);
  
  delay(1000);
  lcd.clear();
}

void loop()
{
  digitalWrite(12, HIGH);
  digitalWrite(A1, LOW);
  delayMicroseconds(2);
  digitalWrite(A1, HIGH);
  delayMicroseconds(10);
  digitalWrite(A1, LOW);
  duration = pulseIn(A0, HIGH);
  inches = Inches_Conversion(duration);
  delay(500);
  
  lcd.setCursor(0, 0);
  lcd.print("Tank Status:");
  lcd.setCursor(0, 1);
  lcd.print("Water Level:");
  lcd.setCursor(15, 1);
  lcd.print("%");
  
  // Relay Control

  if (inches < 2 && motor_status == 1)
  {    
    digitalWrite(8, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);

    lcd.setCursor(0, 0);
    lcd.print("Tank Status:");
    lcd.setCursor(0, 1);
    lcd.print("Water Level:");
    lcd.setCursor(12, 0);
    lcd.print("Full");
    lcd.setCursor(12, 1);
    lcd.print("100");
    delay(500);
    
    tone(9, 1296, 850);
    delay(100);
    tone(9, 850, 100);
    delay(800);
    noTone(9);
    
    motor_status = 0;
  }

  else if(inches == 2)
  {
    lcd.setCursor(12, 0);
    lcd.print("High");
    lcd.setCursor(12, 1);
    lcd.print(" 90");
  }

  else if(inches == 3)
  {
    lcd.setCursor(12, 0);
    lcd.print("High");
    lcd.setCursor(12, 1);
    lcd.print(" 80");
  }
  
  else if(inches == 4)
  {
    lcd.setCursor(12, 0);
    lcd.print("High");
    lcd.setCursor(12, 1);
    lcd.print(" 70");
  }

  else if(inches == 5)
  {
    lcd.setCursor(12, 0);
    lcd.print(" Mid");
    lcd.setCursor(12, 1);
    lcd.print(" 60");
  }

  else if(inches == 6)
  {
    lcd.setCursor(12, 0);
    lcd.print(" Mid");
    lcd.setCursor(12, 1);
    lcd.print(" 50");
  }

  else if(inches == 7)
  {
    lcd.setCursor(12, 0);
    lcd.print(" Mid");
    lcd.setCursor(12, 1);
    lcd.print(" 40");
  }
  
  else if(inches == 8)
  {
    lcd.setCursor(12, 0);
    lcd.print(" Low");
    lcd.setCursor(12, 1);
    lcd.print(" 30");
  }

  else if(inches == 9)
  {
    lcd.setCursor(12, 0);
    lcd.print(" Low");
    lcd.setCursor(12, 1);
    lcd.print(" 20");
  }

  else if(inches > 10 && motor_status == 0)
  {
    digitalWrite(8, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
    
    lcd.setCursor(0, 0);
    lcd.print("Tank Status:");
    lcd.setCursor(0, 1);
    lcd.print("Water Level:");
    lcd.setCursor(12, 0);
    lcd.print(" Low");
    lcd.setCursor(12, 1);
    lcd.print(" 10");
    delay(500);

    tone(9, 850, 100);
    delay(100);
    tone(9, 1296, 850);
    delay(800);
    noTone(9);

    motor_status = 1;
  }
}

long Inches_Conversion(long microseconds) {
   return microseconds / 74 / 2;
}
