/*
debounce button function originally came from 
Exploring Arduino, Second Edition
Code Listing 2-5: Debounced Button Toggling
https://www.exploringarduino.com/content2/ch2
Copyright 2019 Jeremy Blum ( https://www.jeremyblum.com )
Licensed under MIT ( https://github.com/sciguy14/Exploring-Arduino-2nd-Edition/blob/master/LICENSE.md )

However, I've altered the debounce() function so it can be used with 
multiple buttons.  I also provide an example using two buttons and two LEDs.
@raddevus http://raddev.us
*/

const int YELLOW=9;             // The LED is connected to pin 9
const int YELLOW_BUTTON=5;          // The Button is connected to pin 2
boolean yellowLast = LOW;    // Variable containing the previous button state
boolean yellowCurrent = LOW;
const int GREEN=2;    
const int GREEN_BUTTON=3;
boolean greenLast = LOW;
boolean greenCurrent = LOW; // Variable containing the current button state
bool greenLedOn = false;       // The present state of the LED (on/off)
bool yellowLedOn = false;       // The present state of the LED (on/off)

void setup()
{
  pinMode (YELLOW, OUTPUT);     // Set the LED pin as an output
  pinMode (YELLOW_BUTTON, INPUT);   // Set button as input (not required)
  pinMode(GREEN, OUTPUT);
  pinMode(GREEN_BUTTON, INPUT);
}

/*
* Debouncing Function
* Pass it the previous button state,
* and get back the current debounced button state.
*/
boolean debounce(boolean last,int BUTTON)
{
  boolean current = digitalRead(BUTTON);       // Read the button state
  if (last != current)                         // If it's different…
  {
    delay(5);                                  // Wait 5ms
    current = digitalRead(BUTTON);             // Read it again
  }
  return current;                              // Return the current value
}

void loop()
{
  checkButton(GREEN, GREEN_BUTTON, greenLast, greenCurrent,greenLedOn);
  checkButton(YELLOW, YELLOW_BUTTON, yellowLast,yellowCurrent,yellowLedOn);
}

void checkButton(int LED, int BUTTON,  bool &last,bool &current, bool &ledOn ){
  current = debounce(last, BUTTON);              // Read debounced state
  if (last == LOW && current == HIGH)    // If it was pressed…
  {
    ledOn = !ledOn;                                  // Toggle the LED value
  }
  last = current;                        // Reset button value
  
  digitalWrite(LED, ledOn);                          // Change the LED state
}
