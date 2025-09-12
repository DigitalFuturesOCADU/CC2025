/*
Creation & Computation
Pressure Sensor Workshop
This simple example helps you check if your pressure sensor is working and what values it produces.

Follow the steps to create the voltage divider circuit using a 10k

*/

// Startup Steps:
// Step 1: Define the pin number for the pressure sensor.
// We use an integer to specify which analog pin the sensor is connected to.
// This makes it easy to change the pin if needed.
int pressureSensorPin = A0;

// Step 2: Define variables to store sensor data.
// We use an integer variable to hold the analog reading from the sensor.
// The analog reading ranges from 0 to 1023.
int pressureSensorValue;

// Step 3: Setup function - runs once when the Arduino starts.
// Here, we initialize the serial communication to send data to the computer.
void setup()
{
  // Turn on the Serial port so we can print out the sensor values.
  // 9600 specifies the speed and this needs to match the Serial Monitor setting.
  Serial.begin(9600);
}

// Runtime Steps:
// Loop function - runs repeatedly after setup.
// This is where we read the sensor and print the value.
void loop()
{
  // Runtime Step 1: Read the analog value from the sensor pin.
  // The pressure sensor is connected to the pin defined above.
  // analogRead() returns a value between 0 and 1023.
  pressureSensorValue = analogRead(pressureSensorPin);

  // Runtime Step 2: Print the sensor value to the serial monitor with descriptive text.
  // This sends the data to the computer so we can see it clearly.
  Serial.print("Pressure Sensor Value: ");
  Serial.println(pressureSensorValue);

  // Runtime Step 3: Wait a short time before the next reading.
  // This prevents the serial monitor from being flooded with data.
  // delay is usually a bad practice in real applications, but it's fine for this simple example.
  // Delay for 100 milliseconds.
  delay(100);
}
