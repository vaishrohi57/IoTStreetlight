#include <Servo.h>
int red = 10;
int yellow = 9;
int green = 8;int ambientSensor = A0;
int rainSensor = A1;int externalLight = 11;
int servoMotor = 12;
Servo myservo;int delayTime = 15000;
long prevMillis=0,trafficMillis=0;
void setup()
{
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(ambientSensor, INPUT);
  pinMode(rainSensor, INPUT);
  pinMode(externalLight, OUTPUT);
  myservo.attach(servoMotor); 
  Serial.begin(9600);
  myservo.write(0);
}
void checkAndSetAmbientLight()
{
  int ambientValue = analogRead(ambientSensor); 
  if(ambientValue < 800)
    digitalWrite(externalLight, HIGH);
  else
    digitalWrite(externalLight, LOW);
}
void checkAndSetRain()
{
  int rainValue = analogRead(rainSensor);
  Serial.println(rainValue);
  if(rainValue < 800)
  {
    myservo.write(180);
  }
  else
  {
    myservo.write(0);
  }
}
void loop()
{
  changeLights();
  prevMillis = millis(); 
  while(millis()-prevMillis<delayTime)
  {
    checkAndSetAmbientLight();
    checkAndSetRain();
  }
}
void changeLights()
{
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  trafficMillis = millis();
  while(millis()- trafficMillis<3000)
  {
    checkAndSetAmbientLight();
    checkAndSetRain();
  }
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);
  trafficMillis = millis();
  while(millis()-trafficMillis<5000)
  {
  checkAndSetAmbientLight();
  checkAndSetRain();
  }
  digitalWrite(yellow, LOW);
  digitalWrite(red, LOW);
  digitalWrite(green, HIGH);
  trafficMillis = millis();
  while(millis()-trafficMillis<3000)
  {
    checkAndSetAmbientLight();
    checkAndSetRain();
  }
}




