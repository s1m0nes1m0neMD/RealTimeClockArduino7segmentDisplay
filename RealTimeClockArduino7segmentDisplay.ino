#include <DS1307RTC.h>
    //http://github.com/JChristensen/DS3232RTC
#include <Time.h>         //http://www.arduino.cc/playground/Code/Time  
#include <Wire.h>         //http://arduino.cc/en/Reference/Wire (included with Arduino IDE)

const int digitPins[14] = {10,9,8,7,6,5,4,3,2,A0,A1,A2,A3,1};                 //4 common anode pins of the display
const int clockPin = 11;    //74HC595 Pin 11 
const int latchPin = 12;    //74HC595 Pin 12
const int dataPin = 13;     //74HC595 Pin 14
const byte digit[10] =      //seven segment digits in bits
{
  B00111111, //0
  B00000110, //1
  B01011011, //2
  B01001111, //3
  B01100110, //4
  B01101101, //5
  B01111101, //6
  B00000111, //7
  B01111111, //8
  B01101111  //9
};
int digitBuffer[14] = {
  0};
int digitScan = 0, flag=0,  soft_scaler = 0;
;
float sayi;float sayi4;
float sayi2;float sayi3;
void setup(){                
  for(int i=0;i<14;i++)
  {
    pinMode(digitPins[i],OUTPUT);
  }
  setSyncProvider(RTC.get);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
}

//writes the temperature on display
void updateDisp(){
  for(byte j=0; j<14; j++)  
    digitalWrite(digitPins[j], LOW);

  digitalWrite(latchPin, LOW);  
  shiftOut(dataPin, clockPin, MSBFIRST, B11111111);
  digitalWrite(latchPin, HIGH);

  delayMicroseconds(2);
  digitalWrite(digitPins[digitScan], HIGH); 

  digitalWrite(latchPin, LOW);  
  if(digitScan==2)
    shiftOut(dataPin, clockPin, MSBFIRST, ~(digit[digitBuffer[digitScan]] | B10000000)); //print the decimal point on the 3rd digit
else   if(digitScan==4)
    shiftOut(dataPin, clockPin, MSBFIRST, ~(digit[digitBuffer[digitScan]] | B10000000));
    else   if(digitScan==6)
    shiftOut(dataPin, clockPin, MSBFIRST, ~(digit[digitBuffer[digitScan]] | B10000000));
    else   if(digitScan==9)
    shiftOut(dataPin, clockPin, MSBFIRST, ~(digit[digitBuffer[digitScan]] | B10000000));
        else   if(digitScan==10)
    shiftOut(dataPin, clockPin, MSBFIRST, ~(digit[digitBuffer[digitScan]] | B10000000));
  else
    shiftOut(dataPin, clockPin, MSBFIRST, ~digit[digitBuffer[digitScan]]);

  digitalWrite(latchPin, HIGH);
  digitScan++;
  if(digitScan>13) digitScan=0; 
}

void loop(){ 
sayi4 =year();
  sayi3 =month()*100+day();
  sayi2 =hour()*100+minute(); sayi =second();
      digitBuffer[13] = int(sayi4)/1000;
  digitBuffer[12] = (int(sayi4)%1000)/100;
  digitBuffer[11] = (int(sayi4)%100)/10;
  digitBuffer[10] = (int(sayi4)%100)%10;
    digitBuffer[9] = int(sayi3)/1000;
  digitBuffer[8] = (int(sayi3)%1000)/100;
  digitBuffer[7] = (int(sayi3)%100)/10;
  digitBuffer[6] = (int(sayi3)%100)%10;
   digitBuffer[5] = int(sayi2)/1000;
  digitBuffer[4] = (int(sayi2)%1000)/100;
  digitBuffer[3] = (int(sayi2)%100)/10;
  digitBuffer[2] = (int(sayi2)%100)%10; 

  digitBuffer[1] = (int(sayi)%100)/10;
  digitBuffer[0] = (int(sayi)%100)%10;
  updateDisp();

}

