#include "LedControl.h"

// all notes

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0

LedControl lc = LedControl(12,11,10,1); // create a new LedControl object
const int echoPin = 6; const int trigPin = 7;
const int buttonPin=2;
int speakerPin = 8;
int sensorPin = A0;
int tempo = 132;
int buttonState=0;
int melody[] = {


//melody from: https://github.com/robsoncouto/arduino-songs/blob/master/babyelephantwalk/babyelephantwalk.ino |  Robson Couto, 2019

  NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
  NOTE_FS4,8, NOTE_G4,8, REST,4, REST,2,
  NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
  NOTE_G4,-2, NOTE_A4,8, NOTE_DS4,1,

  NOTE_A4,8,
  NOTE_E4,8, NOTE_C4,8, REST,4, REST,2,
  NOTE_C4,-8, NOTE_E4,16, NOTE_G4,8, NOTE_C5,8, NOTE_E5,8, NOTE_D5,8, NOTE_C5,8, NOTE_A4,8,
  NOTE_FS4,8, NOTE_G4,8, REST,4, REST,4, REST,8, NOTE_G4,8,
  NOTE_D5,4, NOTE_D5,4, NOTE_B4,8, NOTE_G4,8, REST,8, NOTE_G4,8,

  NOTE_C5,4, NOTE_C5,4, NOTE_AS4,16, NOTE_C5,16, NOTE_AS4,16, NOTE_G4,16, NOTE_F4,8, NOTE_DS4,8,
  NOTE_FS4,4, NOTE_FS4,4, NOTE_F4,16, NOTE_G4,16, NOTE_F4,16, NOTE_DS4,16, NOTE_C4,8, NOTE_G4,8,
  NOTE_AS4,8, NOTE_C5,8, REST,4, REST,2,
};
//
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

void setup() {
pinMode(speakerPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(buttonPin, INPUT);
pinMode(trigPin, OUTPUT);
pinMode(sensorPin, INPUT);
Serial.begin(9600);
lc.shutdown(0,false); // Turn matrix on, no power saving
lc.setIntensity(0,8); // Set brightness to a medium value
lc.clearDisplay(0); // Clear the display

}

void loop(){
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(5);
digitalWrite(trigPin, LOW);
delayMicroseconds(5);

// wait for the echo
long duration = pulseIn(echoPin, HIGH);
// convert the time into a distance, the speed of sound is 29 microseconds per centimeter,
//the pulse traveled forth and back, so we divided the distance by 2
int cm = duration / 29 / 2;



Serial.print("Distance: ");Serial.print(cm); Serial.println("cm");
int sensorValue = analogRead(sensorPin); // read sensorpin
Serial.print("Temperature: ");Serial.println(sensorValue); // print to serial monitor

buttonState=digitalRead(buttonPin);
Serial.print("Button state: ");Serial.println(buttonState);
delay(100);

// I am using two if statements. The first if-else statement is for a scenario in which the button is not pressed. The second if-else statement is for the case in which the button is pressed. 

//1. If Else Statemente: if the distance is greater than 50 cm, the LED matrix will show a check.

if (cm >50 && buttonState==LOW){
lc.setRow(0,0,B00000000);
lc.setRow(0,1,B00000001);
lc.setRow(0,2,B00000010);
lc.setRow(0,3,B01000100);
lc.setRow(0,4,B00101000);
lc.setRow(0,5,B00010000);
lc.setRow(0,6,B00000000);
lc.setRow(0,7,B00000000);
}
// if the distance is below 50cm, the LED matrix will show a stop sign.
else if (cm<50 && buttonState==LOW) {
lc.setRow(0,0,B00111100);
lc.setRow(0,1,B01000010);
lc.setRow(0,2,B10100001);
lc.setRow(0,3,B10010001);
lc.setRow(0,4,B10001001);
lc.setRow(0,5,B10000101);
lc.setRow(0,6,B01000010);
lc.setRow(0,7,B00111100);
delay(500);
// in addition to the stop sign, it will also show " C-19" to remind ppl of the coronavrius(it will acutally take turns displaying the symbols)
lc.setRow(0,0,B00000000);
lc.setRow(0,1,B00000000);
lc.setRow(0,2,B01101011);
lc.setRow(0,3,B10001011);
lc.setRow(0,4,B10001001);
lc.setRow(0,5,B01101001);
lc.setRow(0,6,B00000000);
lc.setRow(0,7,B00000000);
delay(500);
// Further, it will also produce a sound if the distance is to small
tone (speakerPin, 300);
delay(500);
noTone(speakerPin);
delay(500);

//2. If-else statement: If the user pushes the button, he will be able to check his body temperature. If the value exceeds a threshold (meaning that she might has fever/a cold), the LED matrix will remind the user to see a doctor and will play a melody.
}
if (buttonState== HIGH){
if (sensorValue>540){
lc.setRow(0,0,B11000000);
lc.setRow(0,1,B10100000);
lc.setRow(0,2,B11000000);
lc.setRow(0,3,B00111000);
lc.setRow(0,4,B00101000);
lc.setRow(0,5,B00111111);
lc.setRow(0,6,B00000100);
lc.setRow(0,7,B00000111);
delay(500);
// Further, it will also produce a sound if the distance is to small
//tone (speakerPin, 300);
//delay(500);

// If the button is pressed and the sensor value is over 540 it will play a melody

//noTone(speakerPin);
    for (int thisNote = 0; thisNote < notes * 0.8; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(speakerPin, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(speakerPin);
  }
}

else {
lc.setRow(0,0,B00111100);
lc.setRow(0,1,B01000010);
lc.setRow(0,2,B10100101);
lc.setRow(0,3,B10000001);
lc.setRow(0,4,B10100101);
lc.setRow(0,5,B10011001);
lc.setRow(0,6,B01000010);
lc.setRow(0,7,B00111100);
}

}delay(1000);}
 
