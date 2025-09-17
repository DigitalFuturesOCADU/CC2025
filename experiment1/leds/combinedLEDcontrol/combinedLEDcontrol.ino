/*
Combined example: Control 1 blinking LED and 1 fading LED using custom functions
This shows how you can use both functions together in the same program

Blinking LED (can use any digital pin):
- Speed of blinking (blink_led_BlinkTime in milliseconds)
- Whether it starts as ON/OFF (blink_led_BlinkBeginState)

Fading LED (must use PWM pin marked with ~):
- Minimum brightness (fade_led_minBrightness 0-255)
- Maximum brightness (fade_led_maxBrightness 0-255) 
- Speed of fading (fade_led_oscillationTime in milliseconds)
*/

// Blinking LED variables
int blink_led_Pin = 2;
int blink_led_BlinkTime = 500;      // Time for one complete blink cycle (milliseconds)
bool blink_led_BlinkBeginState = false; // Initial state for blinking LED (true = on, false = off)

// Fading LED variables
int fade_led_Pin = 3;
int fade_led_minBrightness = 0;    // Minimum brightness for oscillating LED (0-255)
int fade_led_maxBrightness = 255;  // Maximum brightness for oscillating LED (0-255)
int fade_led_oscillationTime = 1000; // Time for one complete oscillation (milliseconds)

void setup() 
{
  // Initialize LED pins as outputs
  pinMode(blink_led_Pin, OUTPUT);
  pinMode(fade_led_Pin, OUTPUT);
}

void loop() 
{
  // Control the blinking LED
  bool blinkState = blink(blink_led_BlinkTime, blink_led_BlinkBeginState);
  digitalWrite(blink_led_Pin, blinkState);
  
  // Control the fading LED
  int fadeBrightness = oscillate(fade_led_minBrightness, fade_led_maxBrightness, fade_led_oscillationTime);
  analogWrite(fade_led_Pin, fadeBrightness);
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

// Function to calculate oscillating values
// Uses sine wave mathematics to create smooth fading
// minVal = minimum brightness level
// maxVal = maximum brightness level
// oscillationTime = how long one complete fade cycle takes
int oscillate(int minVal, int maxVal, int oscillationTime) {
  // Calculate current position in oscillation cycle (0.0 to 1.0)
  float cyclePosition = (millis() % oscillationTime) / (float)oscillationTime;
  
  // Calculate sine value (-1 to 1) for current cycle position
  float sineValue = sin(cyclePosition * 2 * PI);

  // Map sine wave (-1 to 1) to desired range (minVal to maxVal)
  // Because the map function only returns integers, the value is multiplied by 1000
  int brightness = map(sineValue * 1000, -1000, 1000, minVal, maxVal);
  
  // Output the value
  return brightness;
}