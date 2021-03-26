#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address to 0x27 in PCF8574 by NXP and Set to 0x3F in PCF8574A by Ti
LiquidCrystal_I2C lcd(0x27, 16, 2);

byte Play[] = {
  B10000,
  B11000,
  B11100,
  B11110,
  B11110,
  B11100,
  B11000,
  B10000
};

byte Pause[] = {
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011,
  B11011
};

String data[] = {
 "Believer", "Despacito", "Faded", "Alone", "Shape of You"
};
String currentPlaying;
String currentSelected;

int currentOption = 0;
int len = sizeof(data)/sizeof(data[0]);
int buttonValForward = 0;
int buttonValBackward = 0;
int buttonValOK = 0;
int ButtonForward = 3;
int ButtonBackward = 4;
int ButtonOK = 5;

void setup() {
  pinMode(ButtonForward, INPUT);
  pinMode(ButtonBackward, INPUT);
  pinMode(ButtonOK, INPUT);
  //lcd.begin();
  lcd.createChar(0, Play);
  lcd.createChar(1, Pause);
  lcd.home();
  Serial.begin(9600);
}

void loop() {
  lcd.clear();
  currentSelected = data[currentOption];
  
  buttonValForward = digitalRead(ButtonForward);
  buttonValBackward = digitalRead(ButtonBackward);
  buttonValOK = digitalRead(ButtonOK);
  
  lcd.print("     MUSIC3     ");
  lcd.setCursor(0,1);
  if (currentSelected == currentPlaying){
    lcd.write(1);
  }else{
    lcd.write(byte(0));
  }
  lcd.print(data[currentOption]);
  if(buttonValForward != 0){
    if(currentOption >= len-1){
      currentOption = 0;
    }else{
      currentOption += 1;
    }
  }

  if(buttonValBackward != 0){
    if(currentOption <= 0){
      currentOption = len-1;
    }else{
      currentOption -= 1;
    }
  }

  if(buttonValOK != 0){

    if(currentSelected == currentPlaying){
      currentPlaying = "";
    }else{
      currentPlaying = data[currentOption];  
    }
    Serial.println(currentPlaying);
  }
  
  delay(225); 
}
