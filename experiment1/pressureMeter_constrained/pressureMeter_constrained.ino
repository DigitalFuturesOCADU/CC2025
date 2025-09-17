/*
Creation & Computation
FSR Sensor Workshop - Pressure Meter

This example creates a visual pressure meter using LEDs.
It reads values from a Force Sensitive Resistor (FSR) pressure sensor connected to analog pin A0.
The sensor value is mapped to light up a corresponding number of LEDs (from 0 to 6).
This helps visualize pressure levels and understand sensor mapping.


*/ñ

// Startup Steps:
// Step 1: Define the pin numbers and constants.
// We use clear variable names to specify which pins are used.
// This makes it easy to change the setup if needed.
int sensor_pin = A0;        // Analog input pin for the pressure sensor
int first_led_pin = 2;      // Digital pin for the first LED (LEDs will use pins 2-7)
int min_pressure = 0;       // Minimum pressure value (no force applied)
int max_pressure = 1023;    // Maximum pressure value (adjust based on your sensor)
const int num_leds = 6;     // Number of LEDs used for the pressure meter display

// Step 2: Define variables to store data.
// We use an array to store the LED pin numbers for easy access.
int led_pins[num_leds];     // Array to store LED pin numbers

// Step 3: Setup function - runs once when the Arduino starts.
// Here, we initialize serial communication and set up the LED pins.
void setup()
{
  // Initialize serial communication at 9600 bits per second.
  // This allows us to see sensor values in the Serial Monitor for debugging.
  Serial.begin(9600);

  // Initialize LED pins as outputs.
  // We use a loop to set up all LED pins from first_led_pin to first_led_pin + num_leds - 1.
  for (int i = 0; i < num_leds; i++)
  {
    led_pins[i] = first_led_pin + i;  // Calculate pin number for each LED
    pinMode(led_pins[i], OUTPUT);     // Set the pin as an output
  }
}

// Runtime Steps:
// Loop function - runs repeatedly after setup.
// This is where we read the sensor, calculate LED display, and update the output.
void loop()
{
  // Runtime Step 1: Read the analog value from the pressure sensor.
  // The FSR sensor is connected to the pin defined above.
  // analogRead() returns a value between 0 and 1023 representing pressure level.
  int sensor_value = analogRead(sensor_pin);

  // Runtime Step 2: Constrain the sensor value to the expected range.
  // This prevents unexpected behavior if the sensor reads outside normal range.
  // constrain() ensures the value stays between min_pressure and max_pressure.
  sensor_value = constrain(sensor_value, min_pressure, max_pressure);

  // Runtime Step 3: Map the sensor value to the number of LEDs to light up.
  // map() converts the sensor range to LED range (0 to num_leds).
  // For example, low pressure lights 0 LEDs, high pressure lights all 6 LEDs.
  int leds_to_light = map(sensor_value, min_pressure, max_pressure, 0, num_leds);  // Runtime Step 4: Light up the appropriate number of LEDs.
  // We loop through all LEDs and turn on only the first 'leds_to_light' number.
  for (int i = 0; i < num_leds; i++)
  {
    if (i < leds_to_light)
    {
      digitalWrite(led_pins[i], HIGH);  // Turn on this LED
    }
    else
    {
      digitalWrite(led_pins[i], LOW);   // Turn off this LED
    }
  }

  // Runtime Step 5: Print values to the serial monitor for debugging.
  // This helps us see the raw sensor value and how many LEDs are lit.
  Serial.print("Sensor value: ");
  Serial.print(sensor_value);
  Serial.print(" | LEDs lit: ");
  Serial.println(leds_to_light);

  // Runtime Step 6: Wait a short time before the next reading.
  // This prevents the display from updating too quickly.
  // Delay for 100 milliseconds.
  delay(100);
}
