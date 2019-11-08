// LDR pins
#define LDR_1 13
//servo angles
#define angle1_u 95
#define angle1_s 115
// speed parameter
#define parameter1 2.8
#define parameter2 2.5
#define stay 60

#define inf 2147483647
//import header file
#include <Servo.h>

Servo myservo;
//timing variable
long val_now = 0, t1 = inf,t1_s = inf,t1_u = inf;
// woking state 
bool flag1 = false;
//count the score
int score=0;
int wait,rest;

//get present time
long now()
{
  val_now = millis();
  return val_now;
}
//press function
void press_1()
{
  myservo.write(angle1_s);
  //reset t1
  t1 = inf;
  //start timing the press time
  t1_s = millis();
  score++;
}
//release function
void up_1()
{
  //reset
  t1_s = inf;
  myservo.write(angle1_u);
  //flag1=false;
  t1_u = millis();
}
void setup() {
  // put your setup code here, to run once:
  myservo.attach(11);  // attaches the servo on pin 11 to the servo object
  pinMode(LDR_1, INPUT);
  //initialise servos
  myservo.write(angle1_u);
}

void loop() {
  // put your main code here, to run repeatedly:
  //if there is a black block and the servo is not in previous event
  if (!flag1 && digitalRead(LDR_1) == HIGH)
  {
    flag1 = true;
    //start time when detect a black block
    t1 = millis();
    
  }
  //Servo 1
  //press
  if (flag1&&((now() - t1) > wait))
  {
    press_1();
  }
  //release
  if (flag1&&((now() - t1_s)> stay))
  {
    up_1();
  }
  //finish resting
  if (flag1&&((now() - t1_u)> (rest)))
  {
    t1_u = inf;
    flag1 = false;
  }

}
