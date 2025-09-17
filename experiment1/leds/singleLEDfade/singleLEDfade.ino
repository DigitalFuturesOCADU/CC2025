/*
Control the fading rate of 1 LED using a custom function
**This LED must be connected to a PWM pin (marked with ~)
**PWM pins on Arduino Nano 33 IoT: D2, D3, D5, D6, D9, D10, D11, D12

You can control:
- Minimum brightness (led_minBrightness 0-255)
- Maximum brightness (led_maxBrightness 0-255) 
- Speed of fading (led_oscillationTime in milliseconds)
*/

int led_Pin = 3;
int led_minBrightness = 0;    // Minimum brightness for oscillating LED (0-255)
int led_maxBrightness = 255;  // Maximum brightness for oscillating LED (0-255)
int led_oscillationTime = 1000; // Time for one complete oscillation (milliseconds)

void setup() 
{
  // Initialize LED pin as output
  pinMode(led_Pin, OUTPUT);
}

void loop() 
{
  // Control the oscillating LED
  int led_brightness = oscillate(led_minBrightness, led_maxBrightness, led_oscillationTime);
  analogWrite(led_Pin, led_brightness);
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