// ****************** LIBRARY SECTION ************************************ //
// #include "pitches.h"

// ***************** USER CONFIG SECTION ********************************* //
#define PIN_OUTPUT_LED 13
#define PIN_OUTPUT_BUZZER 8
#define PIN_INPUT_SENSOR 2

// **************************************************************************************************** //
// **************************************  GENERAL VARIABLES  ***************************************** //
// **************************************************************************************************** //

int motionState = LOW;          // we start, assuming no motion detected
int sensorVal = 0;              // variable for reading the pin status
int freq = 2000;

// notes in the melody:
// int melody[] = {
//     NOTE_C4, NOTE_G3, NOTE_G3, NOTE_GS3, NOTE_G3, 0, NOTE_B3, NOTE_C4
// };

// note durations: 4 = quarter note, 8 = eighth note, etc.:
// int noteDurations[] = {
//     4, 8, 8, 4, 4, 4, 4, 4
// };

// Timers
unsigned long previousMillis = 0;        // will store last time action taken

// ==================================================================================================== //
// =========================================  FUNCTIONS: SETUP  ======================================= //
// ==================================================================================================== //

// ARDUINO: the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600); // For Debugging
  Serial.println("=== setup()");

  pinMode(PIN_OUTPUT_LED, OUTPUT);      // declare LED as output
  pinMode(PIN_OUTPUT_BUZZER, OUTPUT);   // declare LED as output
  pinMode(PIN_INPUT_SENSOR, INPUT);     // declare sensor as input
}

// ==================================================================================================== //
// ==========================================  FUNCTIONS: LOOP  ======================================= //
// ==================================================================================================== //

// ARDUINO: the loop function runs over and over again forever
void loop() {
  // Serial.println("=== loop()");
  // if analog input pin 0 is unconnected, random analog
  // noise will cause the call to randomSeed() to generate
  // different seed numbers each time the sketch runs.
  // randomSeed() will then shuffle the random function.
  // randomSeed(analogRead(0));

    readInput();

    if(sensorVal == HIGH && motionState == LOW) {
        motionState = HIGH;
        writeOutput(1);
        // playMelody();
    } else if(sensorVal == LOW && motionState == HIGH) {
        motionState = LOW;
        writeOutput(0);
    }
}


// ---------------------------------------------------------------------------------------------------- //
// ======================================== Helper Functions ========================================== //
// ---------------------------------------------------------------------------------------------------- //

void readInput() {
    sensorVal = digitalRead(PIN_INPUT_SENSOR);
}

void writeOutput(int n) {
    if(n == 0) {
        digitalWrite(PIN_OUTPUT_LED, LOW);
        Serial.println("Motion ended!");
        noTone(PIN_OUTPUT_BUZZER);
    } else {
        digitalWrite(PIN_OUTPUT_LED, HIGH);
        Serial.println("Motion detected!");
        tone(PIN_OUTPUT_BUZZER, freq);
    }
}

// void playMelody() {
//     // iterate over the notes of the melody:
//     for (int thisNote = 0; thisNote < 8; thisNote++) {
//         // to calculate the note duration, take one second
//         // divided by the note type.
//         //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//         int noteDuration = 1000/noteDurations[thisNote];
//         tone(8, melody[thisNote], noteDuration);
    
//         //pause for the note's duration plus 30 ms:
//         delay(noteDuration +30);
//     }
// }

/**
 * @brief Checks if the amount of time has passed
 *
 * @param delay - Amount of time to pass to return true
 * @param previousMillis - Updates a new value after true
 * @return true
 * @return false
 */
bool isTime(int delay, unsigned long &previousMillis) {
  unsigned long currentMillis = millis();
  // TODO: handle wrap?
  if (currentMillis - previousMillis > delay) {
    previousMillis = currentMillis;
    return true;
  }
  return false;
}

// ---------------------------------------------------------------------------------------------------- //
// ---------------------------------------------------------------------------------------------------- //
