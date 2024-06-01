
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h> 
#include <SPI.h>
#include <Servo.h>

int pulses = 0;
int interruptPin = 2;
boolean displayMe = false;
int amount = 0;
int mode;
int rotate;
const byte ROWS = 4;
const byte COLS = 4;
int turn = 0;
int pos = 0;
int Acustoms = 0;
int Bcustoms = 0;
int Ccustoms = 0;
int customs = 0;

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
  Serial.begin(9600);

  //Relay
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  
  //Servo
  servoA.attach(11);
  servoB.attach(12);
  servoC.attach(13);
  servoA.write(80); 
  servoB.write(80); 
  servoC.write(80); 
  
  //Bill Acceptor
  pinMode(interruptPin, INPUT_PULLUP);

  //LCD Screen
  //lcd.begin(20,4);
  lcd.init();
  lcd.backlight();
  
  //Splash Screen
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("Coin Changer");
  lcd.setCursor(0,1);
  lcd.print("Machine       ");
  delay(500);
}

void displays(){
  Acustoms = 0;
  Bcustoms = 0;
  Ccustoms = 0;
  customs = 0;
  rotate = 0;
  mode = 0;
  amount = 0;
  pulses = 0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Please insert");
  lcd.setCursor(0,1);
  lcd.print("paper bill here");
} 


void processing(){
    pulses++;
    amount = pulses / 2;  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bill Inserted");
    lcd.setCursor(0,1);
    lcd.print("Php: ");
    lcd.print(amount);    
}

//-----------------------------------COIN MACHINE-------------------------------------//

void Aselect(){
  int x = 0;
  int y = 0;
  int z = 0;
  rotate = amount / 10;
  rotate = rotate - 1;
  for (turn = 1; turn <= rotate; turn++){
   x = x + 1;
   servoA.write(0); 
   delay(500);
   servoA.write(80); 
   delay(500);
  }
  for (turn = 1; turn <= 1; turn++){
    y = y + 1;
   servoB.write(0); 
   delay(500);
   servoB.write(80); 
   delay(500);
  }
  for (turn = 1; turn <= 3; turn++){
    z = z + 1;
   servoC.write(0); 
   delay(500);
   servoC.write(80); 
   delay(500);
  }
  Serial.print(x);
  Serial.print('-');
  Serial.print(y);
  Serial.print('-');
  Serial.println(z);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Transaction Complete");
  lcd.setCursor(0,2);
  lcd.print("     Thank you!     ");
  delay(300);
  displays();
}

void Bselect(){
  int x = 0;
  int y = 0;
  int z = 0;
  rotate = amount / 5;
  rotate = rotate - 1;
  for (turn = 1; turn <= rotate; turn++){
   y = y + 1;
   servoB.write(0); 
   delay(500);
   servoB.write(80); 
   delay(500);
  }
   for (turn = 1; turn <= 3; turn++){
   z = z + 1;
   servoC.write(0); 
   delay(500);
   servoC.write(80); 
   delay(500);
  }
  Serial.print(0);
  Serial.print('-');
  Serial.print(y);
  Serial.print('-');
  Serial.println(z);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Transaction Complete");
  lcd.setCursor(0,2);
  lcd.print("     Thank you!     ");
  delay(3000);
  displays();
}

void Cselect(){
  int x = 0;
  int y = 0;
  int z = 0;
  rotate = amount / 1;
  rotate = rotate - 2;
  for (turn = 1; turn <= rotate; turn++){
   z = z + 1;
   servoC.write(0); 
   delay(500);
   servoC.write(80); 
   delay(500);
  }
  Serial.print(0);
  Serial.print('-');
  Serial.print(0);
  Serial.print('-');
  Serial.println(z);
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print("Transaction Complete");
  lcd.setCursor(0,2);
  lcd.print("     Thank you!     ");
  delay(3000);
  displays();
}

void Dselect(){
     while(mode == 1){
     char cusSelect = customKeypad.getKey();
     delay(100);
     if(cusSelect){
      switch(cusSelect){
      case '1':   
       Acustoms = Acustoms + 1;
       customs = customs + 10;
       if(customs > amount){
       Acustoms = Acustoms - 1;
       customs = customs - 10;
       }   
      break;
      case '2':
       Bcustoms = Bcustoms + 1;
       customs = customs + 5;
        if(customs > amount){
       Bcustoms = Bcustoms - 1;
       customs = customs - 5;
      }
      break;
      case '3':
       Ccustoms = Ccustoms + 1;
       customs = customs + 1;
       if(customs > amount){
        Ccustoms = Ccustoms - 1;
       customs = customs - 1;
      }
      break;
      }
      if(customs < amount){
          delay(500);
          displaycustom();
      }else{
         displaycustomB();
         lcd.clear();
         lcd.setCursor(0,1);
         lcd.print("  Custom Selected!  ");
         lcd.setCursor(0,2);
         lcd.print("   please wait...   ");
         delay(100);
        for (turn = 1; turn <= Acustoms; turn++){
          servoA.write(0); 
          delay(500);
          servoA.write(80); 
          delay(500);
         }
         for (turn = 1; turn <= Bcustoms; turn++){
          servoB.write(0); 
          delay(500);
          servoB.write(80); 
          delay(500);
         } 
         for (turn = 1; turn <= Ccustoms; turn++){
          servoC.write(0); 
          delay(500);
          servoC.write(80); 
          delay(500);
         }
          lcd.clear();
          lcd.setCursor(0,1);
          lcd.print("Transaction Complete");
          lcd.setCursor(0,2);
          lcd.print("     Thank you!     ");
          Serial.print(Acustoms);
          Serial.print('-');
          Serial.print(Bcustoms);
          Serial.print('-');
          Serial.println(Ccustoms);
          delay(300);
          displays();         
      }
    }
  }
  
}

void displaycustom(){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("    Select mixed    ");
    lcd.setCursor(0,1); 
    lcd.print("    denomination    ");
    lcd.setCursor(0,2); 
    lcd.print("  1=10   2=5   3=1  ");
    lcd.setCursor(0,3); 
    lcd.print("  Total: ");
    lcd.setCursor(9,3); 
    lcd.print(customs);  
    Dselect();
}

void displaycustomB(){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("    Select mixed    ");
    lcd.setCursor(0,1); 
    lcd.print("    denomination    ");
    lcd.setCursor(0,2); 
    lcd.print("  1=10   2=5   3=1  ");
    lcd.setCursor(0,3); 
    lcd.print("  Total: ");
    lcd.setCursor(9,3); 
    lcd.print(customs);  
    delay(100);
}
//-----------------------------------SELECTION-------------------------------------//
void changer(){
     lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("Select option");
     lcd.setCursor(0,1); 
     lcd.print("C-1 B-5 A-10 D-C");
     //lcd.setCursor(0,3); 
     //lcd.print("  B-5     D-CUSTOM");   
   
     while(mode == 1){
     char coinSelect = customKeypad.getKey();
     delay(100);
     if(coinSelect){
      switch(coinSelect){
      case 'A':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Php 10 Selected   ");
      lcd.setCursor(0,1);
      lcd.print("please wait...");
      delay(100);
      Aselect();
      break;
      case 'B':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Php 5 Selected   ");
      lcd.setCursor(0,1);
      lcd.print("please wait...");
      delay(100);
      Bselect();
      break;
      case 'C':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Php 1 Selected   ");
      lcd.setCursor(0,1);
      lcd.print("please wait...");
      delay(100);
      Cselect();
      break;
      case 'D':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Custom Selected   ");
      lcd.setCursor(0,1);
      lcd.print("please wait...");
      delay(100);
      amount = amount - 2;
      displaycustom();
      break;
      }       
     }
   }
}

void loop() {
  /*
  if (Serial.available())
    switch (Serial.read()){
        case 'O':
        digitalWrite(A0,LOW);
        break;
        case 'P': 
        digitalWrite(A0,HIGH);
        break;
    }
    */
  int val = digitalRead(2);
  if (val == HIGH) {
    processing();
  }
  
  else{
    char customKey = customKeypad.getKey();
    if(customKey == '#'){
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Processing bill");
    lcd.setCursor(0,1);
    lcd.print("please wait...");
    mode = 1;
    delay(1500);
    changer();
    }
    }
  }
