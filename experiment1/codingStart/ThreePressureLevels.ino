// Three Pressure Level Example - Arduino Sketch
// This example expands on the basic two-level pressure sensor to include three distinct pressure ranges
// Hardware: Pressure sensor on A0, three LEDs on digital pins 2, 3, and 4

// Pin assignments for LED outputs
int lowPressureLED = 2;    // Digital pin for low pressure indicator LED
int mediumPressureLED = 3; // Digital pin for medium pressure indicator LED  
int highPressureLED = 4;   // Digital pin for high pressure indicator LED

// Pressure sensor thresholds - dividing 20-500 range into three equal segments
int lowPressureMin = 20;   // Minimum value for low pressure range
int lowPressureMax = 179;  // Maximum value for low pressure range (160 unit range)
int mediumPressureMin = 180; // Minimum value for medium pressure range
int mediumPressureMax = 339; // Maximum value for medium pressure range (160 unit range)
int highPressureMin = 340; // Minimum value for high pressure range
int highPressureMax = 500; // Maximum value for high pressure range (161 unit range)

void setup() 
{
    // Initialize serial communication for debugging
    Serial.begin(9600);
    
    // Configure LED pins as outputs
    pinMode(lowPressureLED, OUTPUT);
    pinMode(mediumPressureLED, OUTPUT);
    pinMode(highPressureLED, OUTPUT);
    
    // Turn off all LEDs initially
    digitalWrite(lowPressureLED, LOW);
    digitalWrite(mediumPressureLED, LOW);
    digitalWrite(highPressureLED, LOW);
}

void loop() 
{
    // Read analog value from pressure sensor on pin A0
    int pressureValue = analogRead(A0);
    
    // Print pressure value to serial monitor for debugging
    Serial.print("Pressure Value: ");
    Serial.println(pressureValue);
    
    // Determine pressure level and control LEDs accordingly
    if (pressureValue >= lowPressureMin && pressureValue <= lowPressureMax)
    {
        // Low pressure detected: turn on low pressure LED, turn off others
        digitalWrite(lowPressureLED, HIGH);
        digitalWrite(mediumPressureLED, LOW);
        digitalWrite(highPressureLED, LOW);
        Serial.println("Status: Low Pressure");
    }
    else if (pressureValue >= mediumPressureMin && pressureValue <= mediumPressureMax)
    {
        // Medium pressure detected: turn on medium pressure LED, turn off others
        digitalWrite(lowPressureLED, LOW);
        digitalWrite(mediumPressureLED, HIGH);
        digitalWrite(highPressureLED, LOW);
        Serial.println("Status: Medium Pressure");
    }
    else if (pressureValue >= highPressureMin && pressureValue <= highPressureMax)
    {
        // High pressure detected: turn on high pressure LED, turn off others
        digitalWrite(lowPressureLED, LOW);
        digitalWrite(mediumPressureLED, LOW);
        digitalWrite(highPressureLED, HIGH);
        Serial.println("Status: High Pressure");
    }
    else
    {
        // Pressure reading is outside the functional range
        // Turn off all LEDs to indicate invalid/no pressure
        digitalWrite(lowPressureLED, LOW);
        digitalWrite(mediumPressureLED, LOW);
        digitalWrite(highPressureLED, LOW);
        Serial.println("Status: Out of Range");
    }
    
    // Small delay to avoid overwhelming the serial monitor
    delay(100);
}