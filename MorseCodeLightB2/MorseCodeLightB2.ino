/* 
 * Purpose:
 *  Build code to translate morse code light flashes into English
 *  
 * Required hardware
 *  Arduino
 *  photoresistor
 *  morse code light source
 *  
 *  created October 27, 2022
 *  by Neill Shikada & Dennis :)
*/

// include chrono to track length of time of incoming flashes
#include <Chrono.h>

/*****************************************************/
/*          Set variables for the sensor             */
/*****************************************************/

/* variable to set the dit unit lengths
 *  Morse code is defined by the length of dits
 dit = 1 unit; dah = 3 units; word-space = 7 units */
const int DIT_LENGTH = 100;   // defined in milliseconds
const int DAH_LENGTH = DIT_LENGTH*3;
const int INTER_WORD_LENGTH = DIT_LENGTH*7;
const int INTER_CHAR_LENGTH = DIT_LENGTH*3;
const int INTRA_CHAR_LENGTH = DIT_LENGTH;
/* variable to control how sensitive the sensor is to morse */
const int BUFFER = DIT_LENGTH/2;

/* variable to indicate the high value of light */
int sensorHigh = 901;
/* variable to indicate the low value of light */
int sensorLow = 900;
/* threshold for the sensor to register a flash */
int sensorThreshold = 900;
/* variable to hold the values of the photoresistor */
int sensorValue;

/* Set the pin for the photo resistor */
const int photoPin = A0;

/* boolean to see if light is on (default = false) */
bool lightState = false;
bool prevLightState = false;

/* String variables to hold the morse code and corresponding message in Ascii */
String message = "";
String morse = "";

/* create an instance of chrono to track the time */
Chrono timer;

/* set LED output pins for testing */
int OUTPUT_PIN1 = 13;
int OUTPUT_PIN2 = 14;
int OUTPUT_PIN3 = 15;


/*****************************************************/
/*              Morse Library Class                  */
/*****************************************************/
/* Reference for the morse translation               */
class MorseLibrary {

  /* array of all the letters and numbers to use with the code */
  char AsciiLibrary[36] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
    'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', 
    '5', '6', '7', '8', '9', '0'
  };
  /* corresponding array of morse codes that match the order of the AsciiLibrary */
  String MorseLibrary[36] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", 
    "....", "..", ".---", "-.-", ".-..", "----", "-.", 
    "---", ".--.", "--.-", ".-.", "...", "-", "..-", 
    "...-", ".--", "-..-", "-.--", "--..", ".----", 
    "..---", "...--", "....-", ".....", "-....", 
    "--...", "---..", "----.", "-----"
  };
    
  public:
    /* translate takes an input string of dots, dashes, and spaces and converts them into Ascii */
    char translate(String code) {
      // Serial.print(code);
      for (int i = 0; i < sizeof(MorseLibrary); i++) {
        if (code == MorseLibrary[i]) {
          return AsciiLibrary[i];
          break;
        } else {
//          Serial.print("Null");
        }
      }
      return '!';
    };
};

/*****************************************************/
/*              Morse Decoder Class                  */
/*****************************************************/
/* Translates the incoming code to English           */
class MorseDecoder {
  MorseLibrary ml;
  
  public:
    /* readLight checks the incoming light patterns to determine if it's a dit or dah, otherwise it'll print "!" */
    void readLight() {
      
      // checks the length of time to see if it roughly matches the dits, dahs, etc.
      if (timer.elapsed() > DAH_LENGTH - BUFFER && timer.elapsed() < DAH_LENGTH + BUFFER) {
        morse += "-";                         // adds a "-" to the morse code string
        timer.restart();
      } else if (timer.elapsed() > DIT_LENGTH - BUFFER && timer.elapsed() < DIT_LENGTH + BUFFER) {
        morse += ".";                         // adds a "." to the morse code string
        timer.restart();
      } else {
//        Serial.println("null");
//        Serial.println(t);
      }

//      timer.restart();
    }

    /* readDark checks the timing between light patterns to determine if it's an inter character, intra character, or inter word break, otherwise it prints "!" */
    void readDark() {

      // checks the length of time to see if it roughly matches the dits, dahs, etc.
      if (timer.elapsed() > INTER_WORD_LENGTH - BUFFER && timer.elapsed() < INTER_WORD_LENGTH + BUFFER) {
        
        nextWord();                           // runs the function to process the full word into Ascii
        timer.restart();
        
      } else if (timer.elapsed() > INTRA_CHAR_LENGTH - BUFFER && timer.elapsed() < INTRA_CHAR_LENGTH + BUFFER) {
        
        timer.restart();
      
      } else if (timer.elapsed() > INTER_CHAR_LENGTH - BUFFER && timer.elapsed() < INTER_CHAR_LENGTH + BUFFER) {
        
        message += ml.translate(morse);       // add the latest morse code character to the word
        Serial.print(morse);
        morse = "";                           // clears the morse String to prepare for the next character
        timer.restart();
      
      } else if (timer.elapsed() == INTER_WORD_LENGTH * 1.5) {

        nextWord();
        
      }

    }

    void nextWord() {
      
        digitalWrite(OUTPUT_PIN1, LOW);          // resets the LEDs so they can check again for the incoming word
        digitalWrite(OUTPUT_PIN2, LOW);
        digitalWrite(OUTPUT_PIN3, LOW);
        
        message += ml.translate(morse);       // add the latest morse code character to the word
        message += " ";                       // adds a space after the word so there's a space between this and the next one
        morse = "";                           // clears the morse String to prepare for the next character

        if (message == "BAD ") {                // checks for if the message matches "BAD "
          digitalWrite(OUTPUT_PIN1, HIGH);       // turns on an LED that corresponds to "BAD "
          Serial.println("shit");
        } else if (message == "GOOD ") {     // checks for if the message matches "PA "
          digitalWrite(OUTPUT_PIN2, HIGH);       // turns on an LED that corresponds to "PARIS "
          Serial.println("yay");
        } else if (message == "FAIR ") {         // checks for if the message matches "K "
          digitalWrite(OUTPUT_PIN3, HIGH);       // turns on an LED that corresponds to "K "
          Serial.println("what?");
        }
        
        Serial.print(message);                // prints the message to the serial
        message = "";                         // resets the message to prepare for the next incoming word
        
    }
};

/*****************************************************/
/*             Dynamic Scaling Class                 */
/*****************************************************/
/* Scales the high and low inputs from the photo     *
 * resistor for different environments               */
class DynamicScaling {
};


/*****************************************************/
/*                Setup Function                     */
/*****************************************************/
void setup() {
  // set the baud rate
  Serial.begin(9600);
  // start the listening timer
  timer.restart();
}

/*****************************************************/
/*                 Loop Function                     */
/*****************************************************/
void loop() {

  digitalWrite(OUTPUT_PIN1, HIGH);
  
  MorseDecoder md;
  
  // reads the photoresistor data and assigns it to sensorValue
  sensorValue = analogRead(photoPin);

  /* if the light passes the threshold for being on, set lightState to true
   * if it doesn't, set it to false */
  if (sensorValue > sensorThreshold) {
    lightState = true;
  } else if (sensorValue < sensorThreshold) {
    lightState = false;
  }

  /* if the light changed and just turned on, then read the darkness between characters
   * if the light changed and just turned off, then read the light for characters */
  if (lightState != prevLightState && lightState == true) {
    if (timer.elapsed() > INTER_WORD_LENGTH*2) {
      timer.restart();
    }
    md.readDark();
    timer.restart();
  } else if (lightState != prevLightState && lightState == false) {
    md.readLight();
    timer.restart();
  } else if (timer.elapsed() == INTER_WORD_LENGTH*2) {
    if (message != "") {
      Serial.print("hello");
      md.nextWord();    // if we haven't heard a signal in a bit and have a message, run the function to process the full word into Ascii
    }
    timer.restart();
  }
  
  prevLightState = lightState;
}
