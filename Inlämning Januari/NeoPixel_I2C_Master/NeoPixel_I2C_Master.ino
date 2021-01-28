#include <Wire.h>
#define address 8
#define recievedSize 4
#define redLed 10
#define yellowLed 9
#define greenLed 8
#define pir 2
bool buttonPressed ;
bool carIsThere ;

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
}

void loop()
{
  idle();
  attachInterrupt(digitalPinToInterrupt(pir), STOOOOOOPPP, RISING);

  if (buttonPressed == HIGH && carIsThere == HIGH)
  {
    turnToRedCars();
    delay(5000);
    turnToGreen();
    delay(6000);
    turnToRed();
    buttonPressed = LOW;
  }
  if (buttonPressed == LOW)
  {
    turnToGreenCars();
  }
  received();
}

void received()
{
  Wire.requestFrom(address, recievedSize);
  while ( Wire.available() )
  {
    carIsThere = Wire.read();
  }

}
void STOOOOOOPPP() {
  buttonPressed = HIGH;
  Serial.println("interrupt");
}

void turnToRedCars()
{
  //Serial.println("PEDESTRIAN WAITING : ");
  //Serial.println(buttonPressed);
  Wire.beginTransmission(address);
  Wire.write(1);
  delay(1000);
  Wire.endTransmission();
}
void turnToGreenCars()
{

  Wire.beginTransmission(address);
  //Serial.println("OKFORCARS : ");
  //Serial.println("OK");
  Wire.write(0);
  delay(1000);
  Wire.endTransmission();
}

void turnToRed()
{
  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  delay(2000);
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, HIGH);

}

void turnToGreen()
{
  digitalWrite(yellowLed, HIGH);
  digitalWrite(redLed, LOW);
  delay(2000);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);

}

void idle()
{
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, HIGH);
}
