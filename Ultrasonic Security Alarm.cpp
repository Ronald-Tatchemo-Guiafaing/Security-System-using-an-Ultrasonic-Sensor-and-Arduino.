// Ultrasonic-Based Security Alarm System

#define TRIG_PIN 6          // Trigger pin for ultrasonic sensor
#define ECHO_PIN 5          // Echo pin for ultrasonic sensor
#define BUZZER_PIN 2        // Buzzer pin

float buzzerDelay;           // Variable to hold the calculated delay for the buzzer


void setup() 
{
    Serial.begin(9600);                   // Initialize serial communication at 9600 baud
    pinMode(TRIG_PIN, OUTPUT);            // Set trigger pin as output
    pinMode(ECHO_PIN, INPUT);             // Set echo pin as input
    pinMode(BUZZER_PIN, OUTPUT);          // Set buzzer pin as output
}


void loop() 
{
    long duration;                          // Variable to hold duration of the echo pulse
    long distance;                          // Variable to hold calculated distance

    // Clear the trigger pin condition
    digitalWrite(TRIG_PIN, LOW);        
    delayMicroseconds(2);                   // Wait for 2 microseconds
  
    // Set trigger pin to HIGH for 10 microseconds
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);                 
    digitalWrite(TRIG_PIN, LOW);
  
    // Read the duration of the echo pulse
    duration = pulseIn(ECHO_PIN, HIGH);
  
    // Calculate distance in centimeters
    distance = (duration / 2) / 29.1;

    // Set buzzer delay based on distance
    buzzerDelay = (distance * 3) + 30;

    // Print the measured distance to the Serial Monitor
    Serial.print(distance);
    Serial.println(" cm");

    // Activate buzzer if the distance is less than a specified threshold
    if (distance < 50) 
    {
        digitalWrite(BUZZER_PIN, HIGH);   // Turn on the buzzer
        delay(buzzerDelay);                // Delay for calculated duration
        digitalWrite(BUZZER_PIN, LOW);    // Turn off the buzzer
    } 
    else 
    {
        digitalWrite(BUZZER_PIN, LOW);    // Ensure buzzer is off if distance is safe
    }
  
    delay(200);                            // Short delay before next measurement
}