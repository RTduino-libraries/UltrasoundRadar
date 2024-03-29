#include <RTduino.h>
#include <Servo.h>

// Defines Tirg and Echo pins of the Ultrasonic Sensor
const int trigPin = D2;
const int echoPin = D4;
// Variables for the duration and the distance
long duration;
int distance;

Servo myServo; // Creates a servo object for controlling the servo motor

// Function for calculating the distance measured by the Ultrasonic sensor
int calculateDistance()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH); // Reads the echoPin, returns the sound wave travel time in microseconds
    distance= duration*0.034/2;
    return distance;
}

void radar_setup(void)
{
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT); // Sets the echoPin as an Input
    Serial.begin();
    myServo.attach(D3); // Defines on which pin is the servo motor attached
}
void radar_loop(void)
{
    // rotates the servo motor from 15 to 165 degrees
    for(int i=15;i<=165;i++)
    {
        myServo.write(i);
        delay(15);
        distance = calculateDistance();// Calls a function for calculating the distance measured by the Ultrasonic sensor for each degree

        Serial.print(i); // Sends the current degree into the Serial Port
        Serial.print(","); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
        Serial.print(distance); // Sends the distance value into the Serial Port
        Serial.print("."); // Sends addition character right next to the previous value needed later in the Processing IDE for indexing
    }
    // Repeats the previous lines from 165 to 15 degrees
    for(int i=165;i>15;i--)
    {
        myServo.write(i);
        delay(15);
        distance = calculateDistance();
        Serial.print(i);
        Serial.print(",");
        Serial.print(distance);
        Serial.print(".");
    }
}
RTDUINO_SKETCH_LOADER("radar", radar_setup, radar_loop);
