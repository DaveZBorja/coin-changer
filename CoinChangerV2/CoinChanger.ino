/*
 * Dear programmer:
 * 
 * When I wrote this code, only god and
 * I knew how it worked.
 * Now, only god knows it!
 * 
 * Therefore, if u are trying to optimize
 * this routine and it fails (most surely),
 * please increase this counter as a
 * Warning for the next person:
 * 
 * total_hours_wasted_here = 96
 * 
 * By: Dave Borja
 */

#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <Wire.h> 
#include <SPI.h>
#include <Servo.h>

int cashIn = 2; //connect blue wire to pin 2, purple to ground
int pulse = 0;
int counter = 0;
int PHP = 0;

boolean displayMe = false;

int mode;
int rotate;

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

  lcd.init();
  lcd.backlight();
  
  //Relay
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  
  //Servo
  servoA.attach(11);
  servoB.attach(12);
  servoC.attach(13);
  servoA.write(0); 
  servoB.write(0); 
  servoC.write(0); 
  

  //Splash Screen
  lcd.home();
  lcd.setCursor(0,0);
  lcd.print("  Coin Changer  ");
  lcd.setCursor(0,1);
  lcd.print("    Machine   ");
  delay(3000);
  displays();
}

void(* resetFunc) (void) = 0;

void loop() {

   
   
    
    pulse = digitalRead(cashIn); 
  
  if (pulse == 0) {
    counter++;
    if(counter > 10){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Bill Accepted!");
    PHP = PHP + 2;
    lcd.setCursor(0,1);
    lcd.print("P");
    lcd.print(PHP);
    lcd.print(" total");
    delay(10);
     counter = 0;
   
    
   }
      
  
  }

   Serial.println(PHP);
  if (PHP == 100){
      
      changer();
    
   }

  if(pulse == 1 && counter > 0){
      Serial.println(counter);
      counter = 0;
  }

}

/*
void processing(){
    pulses++;
    amount = pulses / 2;  
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("   Bill Inserted");
    lcd.setCursor(3,2);
    lcd.print("Php:");
    lcd.setCursor(7,2);
    lcd.print(amount);    
}
*/
void displays(){
  Acustoms = 0;
  Bcustoms = 0;
  Ccustoms = 0;
  customs = 0;
  rotate = 0;
  mode = 0;
  PHP = 0;
  pulse = 0;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Please insert");
  lcd.setCursor(0,1);
  lcd.print("paper bill here");
  
}


//-----------------------------------SELECTION-------------------------------------//
void changer(){
     lcd.clear();
     lcd.setCursor(0,0); 
     lcd.print("Select option");
     lcd.setCursor(0,1); 
     lcd.print("A-10 B-20 C-50 D-C");   
   
     while(1){
     char coinSelect = customKeypad.getKey();
     delay(100);
     if(coinSelect){
      switch(coinSelect){
      case 'C':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Php 50 Selected   ");
      lcd.setCursor(0,1);
      lcd.print("please wait...");
      delay(1000);
      Cselect();
      break;
      case 'B':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Php 20 Selected   ");
      lcd.setCursor(0,1);
      lcd.print("please wait...");
      delay(1000);
      Bselect();
      break;
      case 'A':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Php 10 Selected   ");
      lcd.setCursor(0,1);
      lcd.print("please wait...");
      delay(1000);
      Aselect();
      break;
      case 'D':
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Custom Selected   ");
      lcd.setCursor(0,1);
      lcd.print(" please wait...");
      delay(1000);
      PHP = PHP - 2;
      //displaycustom();
      break;
      }       
     }
   }
}

//-----------------------------------COIN MACHINE-------------------------------------//

void Aselect(){
  int x = 0;
  int y = 0;
  int z = 0;
  rotate = PHP / 10;
  //rotate = rotate - 1;
  for (turn = 1; turn <= rotate; turn++){
   x = x + 1;
   servoA.write(0); 
   delay(500);
   servoA.write(80); 
   delay(500);
  }
  /*
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
  }*/
  Serial.print(x);
  Serial.print('-');
  Serial.print(y);
  Serial.print('-');
  Serial.println(z);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Transac Complete");
  lcd.setCursor(0,1);
  lcd.print("Thank you!     ");
  delay(1000);
  resetFunc();
  displays();
}

void Bselect(){
  int x = 0;
  int y = 0;
  int z = 0;
  rotate = PHP / 20;
  //rotate = rotate - 1;
  for (turn = 1; turn <= rotate; turn++){
   y = y + 1;
   servoB.write(0); 
   delay(500);
   servoB.write(80); 
   delay(500);
  }/*
   for (turn = 1; turn <= 3; turn++){
   z = z + 1;
   servoC.write(0); 
   delay(500);
   servoC.write(80); 
   delay(500);
  }*/
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
  delay(1000);
  resetFunc();
  displays();
}

void Cselect(){
  int x = 0;
  int y = 0;
  int z = 0;
  rotate = PHP / 50;
  //rotate = rotate - 2;
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
  lcd.setCursor(0,0);
  lcd.print("Transaction Complete");
  lcd.setCursor(0,1);
  lcd.print("Thank you!");
  delay(1000);
  resetFunc();
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
       if(customs > PHP){
       Acustoms = Acustoms - 1;
       customs = customs - 10;
       }   
      break;
      case '2':
       Bcustoms = Bcustoms + 1;
       customs = customs + 5;
        if(customs > PHP){
       Bcustoms = Bcustoms - 1;
       customs = customs - 5;
      }
      break;
      case '3':
       Ccustoms = Ccustoms + 1;
       customs = customs + 1;
       if(customs > PHP){
        Ccustoms = Ccustoms - 1;
       customs = customs - 1;
      }
      break;
      }
      if(customs < PHP){
          delay(500);
          displaycustom();
      }else{
         displaycustomB();
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Custom Selected!  ");
         lcd.setCursor(0,1);
         lcd.print("please wait...   ");
         delay(1000);
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
          lcd.setCursor(0,0);
          lcd.print("Transaction Complete");
          lcd.setCursor(0,1);
          lcd.print("     Thank you!     ");
          Serial.print(Acustoms);
          Serial.print('-');
          Serial.print(Bcustoms);
          Serial.print('-');
          Serial.println(Ccustoms);
          delay(1000);
         displays();         
      }
    }
  }
  
}

void displaycustom(){
    lcd.clear();
    lcd.setCursor(0,0); 
    lcd.print("Select mixed    ");
    lcd.setCursor(0,1); 
    lcd.print("denomination    ");
    lcd.setCursor(0,2); 
    lcd.print("1=10   2=5   3=1  ");
    lcd.setCursor(0,3); 
    lcd.print("Total: ");
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
    delay(1000);
}
