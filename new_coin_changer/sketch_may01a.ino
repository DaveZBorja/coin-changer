
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h> 
#include <SPI.h>
#include <Servo.h>

int cashIn = 2; //connect blue wire to pin 2, purple to ground
int pulse = 0;
int counter = 0;
int PHP = 0;

int turn = 0;
int pos = 0;
int Acustoms = 0;
int Bcustoms = 0;
int Ccustoms = 0;
int customs = 0;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {3, 4, 5, 6}; 
byte colPins[COLS] = {7, 8, 9, 10}; 

LiquidCrystal_I2C lcd(0x27, 16, 2);
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

Servo servoA;
Servo servoB;
Servo servoC; 

void setup() {

  Serial.begin(115200);
  pinMode(cashIn, INPUT_PULLUP);
  
  Serial.println("Cash machine booted");
  
  lcd.begin(16, 2);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Booted");
  delay(1000);
  
  //Servo
  servoA.attach(11);
  servoB.attach(12);
  servoC.attach(13);
  servoA.write(80); 
  servoB.write(80); 
  servoC.write(80); 
  
  //Splash Screen
  lcd.setCursor(0,0);
  lcd.print("Coin Changer");
  lcd.setCursor(0,1);
  lcd.print("Machine       ");
  delay(500);
  lcd.clear();
}

void loop() {
  lcd.setCursor(0,0);
  lcd.print("Ready!        ");
  pulse = digitalRead(cashIn); 
  
  if (pulse == 0) {
    counter++;
    if(counter > 10){
    lcd.setCursor(0,0);
    lcd.print("Bill Accepted!");
    PHP = PHP + 1;
    lcd.setCursor(0,1);
    lcd.print("P");
    lcd.print(PHP);
    lcd.print(" total");
    delay(1000);
     counter = 0;
    
  }
}

  if(pulse == 1 && counter > 0){
      Serial.println(counter);
      counter = 0;
  }

  }
