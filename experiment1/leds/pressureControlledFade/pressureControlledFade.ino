/*
Control LED fade speed using pressure sensor input
Pressure sensor on A0 controls how fast the LED fades in and out
**This LED must be connected to a PWM pin (marked with ~)
**PWM pins on Arduino Nano 33 IoT: D2, D3, D5, D6, D9, D10, D11, D12

Pressure sensor controls:
- fade speed (oscillationTime changes based on pressure)
- fade range stays constant (0-255 brightness)
*/

// LED variables
int led_Pin = 3;
int led_minBrightness = 0;    // Minimum brightness for oscillating LED (0-255)
int led_maxBrightness = 255;  // Maximum brightness for oscillating LED (0-255)

// Pressure sensor variables
int pressureSensorPin = A0;
int pressureValue = 0;
int pressureMin = 20;         // Minimum pressure reading
int pressureMax = 800;        // Maximum pressure reading

// Fade timing variables
int minOscillationTime = 200; // Fastest fade cycle (milliseconds)
int maxOscillationTime = 2000; // Slowest fade cycle (milliseconds)
int currentOscillationTime = 1000; // Current fade speed

void setup() 
{
  // Initialize serial communication for debugging
  Serial.begin(9600);
  
  // Initialize LED pin as output
  pinMode(led_Pin, OUTPUT);
}

void loop() 
{
  // Read pressure sensor value
  pressureValue = analogRead(pressureSensorPin);
  
  // Map pressure to fade speed (higher pressure = faster fading)
  currentOscillationTime = map(pressureValue, pressureMin, pressureMax, minOscillationTime, maxOscillationTime);
  currentOscillationTime = constrain(currentOscillationTime, minOscillationTime, maxOscillationTime);
  
  // Control the fading LED using current speed
  int led_brightness = oscillate(led_minBrightness, led_maxBrightness, currentOscillationTime);
  analogWrite(led_Pin, led_brightness);
  
  // Debug output
  Serial.print("Pressure: ");
  Serial.print(pressureValue);
  Serial.print(" | Fade Speed: ");
  Serial.print(currentOscillationTime);
  Serial.print("ms | Brightness: ");
  Serial.println(led_brightness);
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