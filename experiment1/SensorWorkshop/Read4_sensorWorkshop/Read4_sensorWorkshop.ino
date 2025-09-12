/*
Creation & Computation
Pressure Sensor Workshop - 4 Sensors
This simple example helps you check if your pressure sensors are working and what values they produce.

Follow the steps to create the voltage divider circuit using a 10k for each sensor.


*/

// Startup Steps:
// Step 1: Define the pin numbers for the pressure sensors.
// We use integers to specify which analog pins the sensors are connected to.
// This makes it easy to change the pins if needed.
int pressureSensorPin1 = A0;
int pressureSensorPin2 = A1;
int pressureSensorPin3 = A2;
int pressureSensorPin4 = A3;

// Step 2: Define variables to store sensor data.
// We use integer variables to hold the analog readings from the sensors.
// The analog readings range from 0 to 1023.
int pressureSensorValue1;
int pressureSensorValue2;
int pressureSensorValue3;
int pressureSensorValue4;

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
// This is where we read the sensors and print the values.
void loop()
{
  // Runtime Step 1: Read the analog values from the sensor pins.
  // The pressure sensors are connected to the pins defined above.
  // analogRead() returns a value between 0 and 1023.
  pressureSensorValue1 = analogRead(pressureSensorPin1);
  pressureSensorValue2 = analogRead(pressureSensorPin2);
  pressureSensorValue3 = analogRead(pressureSensorPin3);
  pressureSensorValue4 = analogRead(pressureSensorPin4);

  // Runtime Step 2: Print the sensor values to the serial monitor with descriptive text.
  // This sends the data to the computer so we can see it clearly.
  Serial.print("Pressure Sensor 1 Value: ");
  Serial.println(pressureSensorValue1);
  Serial.print("Pressure Sensor 2 Value: ");
  Serial.println(pressureSensorValue2);
  Serial.print("Pressure Sensor 3 Value: ");
  Serial.println(pressureSensorValue3);
  Serial.print("Pressure Sensor 4 Value: ");
  Serial.println(pressureSensorValue4);

  // Runtime Step 3: Wait a short time before the next reading.
  // This prevents the serial monitor from being flooded with data.
  // delay is usually a bad practice in real applications, but it's fine for this simple example.
  // Delay for 100 milliseconds.
  delay(100);
}
