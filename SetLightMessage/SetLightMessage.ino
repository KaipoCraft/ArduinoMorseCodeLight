/*
 * Purpose:
 *  Set an LED to flash Morse code according to a set message
 *  
 * Required hardware
 *  Arduino
 *  LED
 * 
 * created October 27, 2022
 * by Neill Shikada
 */

/*****************************************************/
/*              Set Morse code variables             */
/*****************************************************/
// variable to set the dit unit lengths
// Morse code is defined by the length of dits
// dit = 1 unit; dah = 3 units; word-space = 7 units
const int DIT_LENGTH = 100;   // defined in milliseconds
const int DAH_LENGTH = DIT_LENGTH*3;
const int INTER_WORD_LENGTH = DIT_LENGTH*7;
const int INTER_CHAR_LENGTH = DIT_LENGTH*3;
const int INTRA_CHAR_LENGTH = DIT_LENGTH;
// variable to hold the designated LED pin
const int LED_PIN = 13;
const int LED_PIN2 = 8;
String morse;

/*****************************************************/
/*              Morse Library Class                  */
/*****************************************************/
/* Reference for the morse translation               */
class MorseLibrary {
  
  char AsciiLibrary[37] = {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 
    'U', 'V', 'W', 'X', 'Y', 'Z', '1', '2', '3', '4', 
    '5', '6', '7', '8', '9', '0', '/'
  };
  String MorseLibrary[37] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", 
    "....", "..", ".---", "-.-", ".-..", "----", "-.", 
    "---", ".--.", "--.-", ".-.", "...", "-", "..-", 
    "...-", ".--", "-..-", "-.--", "--..", ".----", 
    "..---", "...--", "....-", ".....", "-....", 
    "--...", "---..", "----.", "-----", "/"
  };
    
  public:
    String translate(char letter) {
      for (int i = 0; i < sizeof(AsciiLibrary); i++) {
        if (letter == AsciiLibrary[i]) {
          return MorseLibrary[i];
          break;
        }
      }
      return "!";
    };
};

/*****************************************************/
/*                  Signal Class                     */
/*****************************************************/
/* Sends the message                                 */
class Signal {
  public:
    void sendMessage(String morse) {
      for (int i=0; i < morse.length(); i++) {
        char symbol = morse.charAt(i);
        if (symbol == ".") {
          if (digitalRead(LED_PIN) == LOW) {
            digitalWrite(LED_PIN, HIGH);
            delay(DIT_LENGTH);
          } else {
            digitalWrite(LED_PIN, LOW);
            delay(INTRA_CHAR_LENGTH);
            digitalWrite(LED_PIN, HIGH);
            delay(DIT_LENGTH);
          }
        } else if (symbol == "-") {
          if (digitalRead(LED_PIN) == LOW) {
            digitalWrite(LED_PIN, HIGH);
            delay(DAH_LENGTH);
          } else {
            digitalWrite(LED_PIN, LOW);
            delay(INTRA_CHAR_LENGTH);
            digitalWrite(LED_PIN, HIGH);
            delay(DAH_LENGTH);
          }
        } else if (symbol == " ") {
          digitalWrite(LED_PIN, LOW);
          delay(INTER_CHAR_LENGTH);
        } else {
          digitalWrite(LED_PIN, LOW);
          delay(INTER_WORD_LENGTH);
        }
      }
      
    };
};
  
/*****************************************************/
/*                Setup Function                     */
/*****************************************************/
void setup() {
  // initialize digital LED pin as an output
  pinMode(LED_PIN, OUTPUT);
  
  
}

/*****************************************************/
/*                 Loop Function                     */
/*****************************************************/
void loop() {
//  MorseLibrary ml;
//
//  String message = "PARIS";
//  for(int i = 0; i < message.length(); i++) {
//    
//    char character = message.charAt(i);
//    String morse = ml.translate(character);
//    morse += " ";
////    if (i+1 == message.length()) {
////      morse += "/";
////    }
//    
//    for (int j = 0; j < morse.length(); j ++) {
//      if (morse[j] == '.') {
//        digitalWrite(LED_PIN, HIGH);
//        delay(DIT_LENGTH);
//        digitalWrite(LED_PIN, LOW);
//        delay(INTRA_CHAR_LENGTH);
//      } else if (morse[j] == '-') {
//        digitalWrite(LED_PIN, HIGH);
//        delay(DAH_LENGTH);
//        digitalWrite(LED_PIN, LOW);
//        delay(INTRA_CHAR_LENGTH);
//      } else if (morse[j] == ' ') {
//        digitalWrite(LED_PIN, LOW);
//        delay(INTER_WORD_LENGTH - INTRA_CHAR_LENGTH);
//      } else if (morse[j] == '/') {
////        digitalWrite(LED_PIN, LOW);
////        delay(INTER_WORD_LENGTH - INTRA_CHAR_LENGTH);
//      } else {
//        break;
//      }
//    }
//  }
//  //delay(INTER_WORD_LENGTH - INTER_CHAR_LENGTH - INTRA_CHAR_LENGTH);
////  digitalWrite(LED_PIN, LOW);
////  delay(INTER_WORD_LENGTH - INTER_CHAR_LENGTH - INTRA_CHAR_LENGTH);

  digitalWrite(LED_PIN2, HIGH);
  
  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTER_CHAR_LENGTH);
  
  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTER_CHAR_LENGTH);
  
  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTER_CHAR_LENGTH);

  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTER_CHAR_LENGTH);

  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTER_WORD_LENGTH);

  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTER_WORD_LENGTH);

  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTER_WORD_LENGTH);

  digitalWrite(LED_PIN, HIGH);
  delay(DIT_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTRA_CHAR_LENGTH);
  digitalWrite(LED_PIN, HIGH);
  delay(DAH_LENGTH);
  digitalWrite(LED_PIN, LOW);
  delay(INTER_WORD_LENGTH);
}
