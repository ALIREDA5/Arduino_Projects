#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

/* Macros */ 
#define buzzer 12 
#define led 13 

#define x A0 
#define y A1 
#define z A2 

#define samples 9
#define maxVal 3 
#define minVal -3 
#define buzTime 2000 

/* Global Variables */

float xsample;
float ysample;
float zsample;
long start;
int buz=0;

void setup()
{
  lcd.init();                      // initialize the lcd 
  Serial.begin(9600); 
  delay(1000);
  lcd.print("EarthQuake ");
  lcd.setCursor(0,1);
  lcd.print("Detector ");
  delay(2000);
  lcd.clear();
  lcd.print("Calibrating.....");
  lcd.setCursor(0,1);
  lcd.print("Please wait...");
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(buzzer, buz);
  digitalWrite(led, buz);

  for(int i=0;i<samples;i++) 
  {
    xsample+=analogRead(x);
    ysample+=analogRead(y);
    zsample+=analogRead(z);
  }

  xsample=xsample/samples; 
  ysample=ysample/samples; 
  zsample=zsample/samples; 

  delay(3000);
  lcd.clear();
  lcd.print("Calibrated");
  delay(1000);
  lcd.clear();
  lcd.print("Device Ready");
  delay(1000);
  lcd.clear();
  lcd.print(" X Y Z ");
}

void loop()
{
  int value1=analogRead(x); 
  int value2=analogRead(y); 
  int value3=analogRead(z); 

  int xValue=xsample-value1; 
  int yValue=ysample-value2; 
  int zValue=zsample-value3; 


  lcd.setCursor(0,1);
  lcd.print(xValue);
  lcd.setCursor(6,1);
  lcd.print(yValue);
  lcd.setCursor(12,1);
  lcd.print(zValue);
  delay(100);

  if(xValue < minVal || xValue > maxVal || yValue < minVal || yValue > maxVal || zValue < minVal || zValue > maxVal)
  {
    if(buz == 0)
      start=millis(); 
      buz=1; 
    }
    else if(buz == 1) 
    {
      lcd.setCursor(0,0);
      lcd.print("Earthquake Alert ");
      if(millis()>= start+buzTime)
      buz=0;
    }
  else
  {
    lcd.clear();
    lcd.print(" X Y Z ");
  }

  digitalWrite(buzzer, buz); 
  digitalWrite(led, buz); 

  Serial.print("x=");
  Serial.println(xValue);
  Serial.print("y=");
  Serial.println(yValue);
  Serial.print("z=");
  Serial.println(zValue);
  Serial.println(" $");
}
