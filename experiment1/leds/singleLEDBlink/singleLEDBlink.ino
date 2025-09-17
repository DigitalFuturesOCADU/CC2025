/*
Control the blink rate of 1 LED using a custom function
You can control:
- Speed of the blinking (led_BlinkTime in milliseconds)
- Whether it starts as ON/OFF (led_BlinkBeginState)
*/

int led_Pin = 2;
int led_BlinkTime = 500;      // Time for one complete blink cycle (milliseconds)
bool led_BlinkBeginState = false; // Initial state for blinking LED (true = on, false = off)

void setup() 
{
  // Initialize LED pin as output
  pinMode(led_Pin, OUTPUT);
}

void loop() 
{
  // Control the blinking LED
  bool ledState = blink(led_BlinkTime, led_BlinkBeginState);
  digitalWrite(led_Pin, ledState);
}

// Function to determine LED state for blinking
// Uses timing logic to control the behaviour
// blinkTime = how fast it is blinking (milliseconds)
// beginState = determines whether its starting state is ON or OFF
bool blink(int blinkTime, bool beginState) {
  // Calculate current position in blink cycle
  unsigned long currentTime = millis() % blinkTime;
  
  // Determine if we're in the first or second half of the cycle
  bool isFirstHalf;
  if(currentTime < (blinkTime / 2))
  {
    isFirstHalf = true;
  }
  else {
    isFirstHalf = false;
  }
 
  // If beginState is true, LED is on in first half; if false, it's on in second half
  return beginState ? isFirstHalf : !isFirstHalf;
}