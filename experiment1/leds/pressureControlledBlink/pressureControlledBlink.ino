/*
Control LED blink speed using pressure sensor input
Pressure sensor on A0 controls how fast the LED blinks on and off
**This LED can use any digital pin

Pressure sensor controls:
- blink speed (blinkTime changes based on pressure)
- blink pattern stays constant (starts off, toggles every half cycle)
*/

// LED variables
int led_Pin = 2;
bool led_BlinkBeginState = false; // Initial state for blinking LED (true = on, false = off)

// Pressure sensor variables
int pressureSensorPin = A0;
int pressureValue = 0;
int pressureMin = 20;         // Minimum pressure reading
int pressureMax = 800;        // Maximum pressure reading

// Blink timing variables
int minBlinkTime = 100;       // Fastest blink cycle (milliseconds)
int maxBlinkTime = 2000;      // Slowest blink cycle (milliseconds)
int currentBlinkTime = 500;   // Current blink speed

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
  
  // Map pressure to blink speed (higher pressure = faster blinking)
  currentBlinkTime = map(pressureValue, pressureMin, pressureMax, minBlinkTime, maxBlinkTime);
  currentBlinkTime = constrain(currentBlinkTime, minBlinkTime, maxBlinkTime);
  
  // Control the blinking LED using current speed
  bool ledState = blink(currentBlinkTime, led_BlinkBeginState);
  digitalWrite(led_Pin, ledState);
  
  // Debug output
  Serial.print("Pressure: ");
  Serial.print(pressureValue);
  Serial.print(" | Blink Speed: ");
  Serial.print(currentBlinkTime);
  Serial.print("ms | LED State: ");
  Serial.println(ledState ? "ON" : "OFF");
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