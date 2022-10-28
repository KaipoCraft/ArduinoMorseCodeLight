/* 
 * Purpose:
 *  Build code to translate morse code in light into English (or control something else on command)
 *  
 * Required hardware
 *  Arduino
 *  photoresistor
 *  morse code light source
 *  
 *  created October 27, 2022
 *  by Neill Shikada
*/

// include chrono to track length of time of incoming flashes
#include <Chrono.h>
// include EasyMorse for translation of the message into English
#include <EasyMorse.h>

/*****************************************************/
/*          Set variables for the sensor             */
/*****************************************************/

// variable to indicate the high value of light
int sensorHigh = 900;
// variable to indicate the low value of light
int sensorLow = 800;
// variable to hold the values of the photoresistor
int sensorValue;

// variable for the gap between signals
const int gap = 100;
// Set the pin for the photo resistor
const int photoPin = A0;
// set the length of light to detect and gap size
const int UNIT_LENGTH = 100;
const int BUFFER_SIZE = 5;

// boolean to see if light is on (default = false)
bool lightState = false;
bool prevLightState = false;

// create an instance of chrono to track the time
Chrono chrono;
// create an instance of easy morse to translate the code
EasyMorse morse;


/*****************************************************/
/*              Morse Decoder Class                  */
/*****************************************************/
/* Translates the incoming code to English           */
class MorseDecoder {
};

/*****************************************************/
/*             Dynamic Scaling Class                 */
/*****************************************************/
/* Scales the high and low inputs from the photo     *
 * resistor for different environments               */
class DynamicScaling {
};

/*****************************************************/
/*             Morse Detection Class                 */
/*****************************************************/
/* In charge of detecting incoming signals           */
class MorseDetector {
  // need to check if light state changes
  // need to know if it was long or short
  // 3 results : dot, dash, gap
  
  public:
    String detect() {
      
      if (lightState != prevLightState) {
//         Serial.print(chrono.elapsed());
//         Serial.println(" ms");
          if (chrono.elapsed() > gap*2) {
            chrono.restart();
            morse.push(2);
            Serial.print("dah");
            return "dah";
          } else if (chrono.elapsed() > gap) {
            chrono.restart();
            morse.push(1);
            Serial.print("dit");
            return "dit";
          } else {
            chrono.restart();
            Serial.println(morse.getCharAscii());
            morse.clear();
            return " ";
          };
          chrono.restart();
      } else return "";
    };
};

/*****************************************************/
/*                Setup Function                     */
/*****************************************************/
void setup() {
  // set the baud rate
  Serial.begin(9600);
}

/*****************************************************/
/*                Loop Function                     */
/*****************************************************/
void loop() {
  MorseDetector md;
  // TODO figure out how to know when to stop and translate. Gap?
  md.detect();
  prevLightState = lightState;
  
  
  // reads the photoresistor data and assigns it to sensorValue
  sensorValue = analogRead(photoPin);

  if (sensorValue > sensorHigh) {
    lightState = true;
  } else if (sensorValue < sensorLow) {
    lightState = false;
  }
  
//  Serial.println(sensorValue);
}
