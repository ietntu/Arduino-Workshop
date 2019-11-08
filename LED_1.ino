/*
   Blink
   Turns on an LED on for one second, then off for one second, repeatedly.
*/

// the setup function runs once when you press reset or power the board

void setup() {  // initialize digital pin 11 as an output.
   pinMode(11, OUTPUT);
}

// the loop function runs over and over again forever

void loop() {
   digitalWrite(11, HIGH); // turn the LED on (HIGH is the voltage level)
   delay(1000); // wait for a second
   digitalWrite(11, LOW); // turn the LED off by making the voltage LOW
   delay(1000); // wait for a second
}
