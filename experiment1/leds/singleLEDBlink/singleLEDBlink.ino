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
  // Define the boolean variable we will return
  bool ledShouldBeOn = false;
  
  // Calculate current position in blink cycle
  // Using modulo (%) to get remainder when dividing current time by blink time
  // millis() keeps counting up continuously (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11...)
  // millis() % blinkTime creates a repeating pattern (0, 1, 2, 3, 4...497, 498, 499, 0, 1, 2, 3...)
  // This gives us a way to know where we are within each blink cycle
  unsigned long currentTime = millis() % blinkTime;
  
  // Determine LED state based on timing and beginState
  if(currentTime < (blinkTime / 2)) {
    // We're in the first half of the cycle
    ledShouldBeOn = beginState;  // LED matches beginState in first half
  } else {
    // We're in the second half of the cycle  
    ledShouldBeOn = !beginState; // LED is opposite of beginState in second half
  }
  
  return ledShouldBeOn;
}