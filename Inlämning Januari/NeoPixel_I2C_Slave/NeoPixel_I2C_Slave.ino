#include <Wire.h>
#define address 8
#define redLed 10
#define yellowLed 9
#define greenLed 8
//#define answerSize 2
#define carPir 2

//bool answer = false;
bool carIsThere = 0;
int pedestrian = 0;
int person;
bool stopcar;
void setup()
{
  Wire.begin(address);
  Serial.begin(9600);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  pinMode(carPir, INPUT);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);

}

void loop()
{

  idle();
  attachInterrupt(digitalPinToInterrupt(carPir), carApproached, RISING);

  if (person == 1)
  {
    //turnToRed();
    idle();
    return;
  }
  if (person == 0 && carIsThere == HIGH)
  {
    carSeen();
  }
  else
    carIsThere = LOW;

}

void carSeen ()
{
  Serial.println("SENDING BACK : ");
  Serial.println(carIsThere);
  delay(1000);
  turnToGreen();
  delay(4000);
  while (carIsThere == HIGH && person == LOW)
  {
    pinMode(greenLed, HIGH);
    while ( Wire.available())
    {
      person = Wire.read();
    }

    requestEvent();

    if (digitalRead(carPir) == LOW)
    {
      carIsThere = LOW;
      turnToRed();
    }
    if (person == HIGH)
    {
      turnToRed();
      delay(1000);

      break;
    }
  }
  idle();

}

void requestEvent()
{

  Wire.write(carIsThere);
}

void receiveEvent(int bytes)
{
  while ( 0 < Wire.available())
  {
    person = Wire.read();
  }
  Serial.println(person);
}

void carApproached()
{
  carIsThere = HIGH;
}

void turnToRed()
{
  digitalWrite(greenLed, HIGH);
  digitalWrite(yellowLed, HIGH);
  delay(2000);
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, HIGH);
  stopcar = true;
}

void turnToGreen()
{
  digitalWrite(yellowLed, HIGH);
  digitalWrite(redLed, LOW);
  delay(2000);
  digitalWrite(yellowLed, LOW);
  digitalWrite(greenLed, HIGH);
  stopcar = false;
}

void idle()
{
  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, HIGH);
  stopcar = true;
}
