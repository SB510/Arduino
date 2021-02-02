 #include <SR04.h>
//#include "IRremoteNew.h"
#include <pitches.h>
SR04 ultraSonic = SR04(12, 11); // Sets up the UltraSonic using 12 for ECHO and 11 for TRIG
long dist;
int receiver = 7; // Signal Pin of IR receiver to Arduino Digital Pin 11
#include <LiquidCrystal.h>
LiquidCrystal lcd(1, 2, 3, 7, 8, 9); // This creates an LCD object to use in

//for the lcd 9=13, 8=9, 7=8, 6=7, 2=1, 3=3
/*-----( Declare objects )-----
Both of these are coming from the library that we included up above.*/
//IRrecv irrecv(receiver);     // create instance of 'irrecv'
//decode_results results;      // create instance of 'decode_results'

const int redPin = 6;
const int greenPin= 5;
const int bluePin= 4;
const int buzzerPin=10;
const int calibrationButton = 13;

int redValue = 6;
int blueValue = 5;
int greenValue = 4;
int Cdist = 100;
int reply;
int songSize = 1; //Stores the number of items in the melody.
int melody[] = {NOTE_C4}; //Stores the notes for the first melody. (The "0" is a rest)
int duration[] = {20}; // Stores the length of each note in the first melody

void setup() {
  // put your setup code here, to run once:
  //irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);
  lcd.begin(16,2); // Our LCD has 16 columns and 2 rows
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(redPin, OUTPUT);
  lcd.print("hi");
  delay(1000);
  lcd.clear();
  pinMode(calibrationButton, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  dist = ultraSonic.Distance();
  Serial.println(dist);
  if(digitalRead(calibrationButton)==HIGH){
    Serial.println(ultraSonic.Distance());
    Cdist = ultraSonic.Distance();
  }
  if(dist < Cdist){
    lcd.print("");
    redValue=255;
    blueValue=0;
    greenValue=0;
    analogWrite(redPin, redValue);
    analogWrite(bluePin, blueValue);
    analogWrite(greenPin, greenValue);
    for(int i = 0; i < songSize; i++){
      int d = 10000/duration[i];
       tone(buzzerPin, melody[i], d);
      int pause = d * 1.30;
      delay(pause);
      noTone(buzzerPin);
   
   switch(reply){
    case 0:
      lcd.print("Please I want to");
      lcd.setCursor(0,1); // 1st column, 1st row
      lcd.print("live!");
      lcd.setCursor(0,0); // 1st column, 1st row
      break;
   case 1:
      lcd.print("SOCIAL DISTANCE!");
      break;
   case 2:
      lcd.print("uh... Pandemic!");
      break;
   case 3:
      lcd.print("Please stay back");
      break;
   }
    }
  }
  else{
    reply = random(4);
    lcd.clear();
    redValue=0;
    blueValue=0;
    greenValue=255;
    analogWrite(redPin, redValue);
    analogWrite(bluePin, blueValue);
    analogWrite(greenPin, greenValue);
  }
}
