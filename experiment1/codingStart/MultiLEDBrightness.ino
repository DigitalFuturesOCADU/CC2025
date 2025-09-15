// Multi-LED Brightness Control Example - Arduino Sketch
// This example extends the basic constrain/map concept to control multiple LEDs
// Hardware: Pressure sensor on A0, four LEDs on PWM pins 2, 3, 5, and 6

// Pin assignments for PWM LED outputs
int led1 = 2;  // First LED on PWM pin 2
int led2 = 3;  // Second LED on PWM pin 3
int led3 = 5;  // Third LED on PWM pin 5
int led4 = 6;  // Fourth LED on PWM pin 6

// Pressure sensor range (same as previous examples)
int pressureMin = 20;   // Minimum functional pressure value
int pressureMax = 500;  // Maximum functional pressure value

// LED brightness range (PWM values)
int brightnessMin = 0;   // Minimum LED brightness (off)
int brightnessMax = 255; // Maximum LED brightness (full brightness)

void setup() 
{
    // Initialize serial communication for debugging
    Serial.begin(9600);
    
    // Configure all LED pins as outputs
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
    
    // Turn off all LEDs initially
    analogWrite(led1, 0);
    analogWrite(led2, 0);
    analogWrite(led3, 0);
    analogWrite(led4, 0);
}

void loop() 
{
    // Read analog value from pressure sensor on pin A0
    int pressureValue = analogRead(A0);
    
    // Constrain pressure reading to functional range
    // This ensures values outside 20-500 range don't cause unexpected behavior
    int constrainedPressure = constrain(pressureValue, pressureMin, pressureMax);
    
    // Map constrained pressure value to LED brightness range
    // Input range: 20-500, Output range: 0-255
    int ledBrightness = map(constrainedPressure, pressureMin, pressureMax, brightnessMin, brightnessMax);
    
    // Set brightness for all LEDs simultaneously
    // All LEDs will have the same brightness based on pressure input
    analogWrite(led1, ledBrightness);
    analogWrite(led2, ledBrightness);
    analogWrite(led3, ledBrightness);
    analogWrite(led4, ledBrightness);
    
    // Print values to serial monitor for debugging
    Serial.print("Raw Pressure: ");
    Serial.print(pressureValue);
    Serial.print(" | Constrained: ");
    Serial.print(constrainedPressure);
    Serial.print(" | LED Brightness: ");
    Serial.println(ledBrightness);
    
    // Small delay for stability and to avoid overwhelming the serial monitor
    delay(50);
}