// LDR pins
#define LDR_1 13
#define LDR_2 12
#define LDR_3 8
//servo angles
#define angle1_u 95
#define angle1_s 115
#define angle2_u 100
#define angle2_s 85
#define angle3_u 80
#define angle3_s 95
// speed parameter
#define parameter1 2.8
#define parameter2 2.5
#define stay 60

#define inf 2147483647
//import header file
#include <Servo.h>

Servo myservo, myservo_1, myservo_2,myservo_3; // create servo object to control a servo
//timing variable
long val_init = 0, val_now = 0, t1 = inf, t2 = inf, t3 = inf, t1_s = inf, t2_s = inf, t3_s = inf, t1_u = inf, t2_u = inf, t3_u = inf;
// woking state 
bool flag1 = false, flag2 = false, flag3 = false;
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
void press_2()
{
  myservo_1.write(angle2_s);
  //reset t2
  t2 = inf;
  //start timing the press time
  t2_s = millis();
  score++;
}
void up_2()
{
  //reset
  t2_s = inf;
  myservo_1.write(angle2_u);
  //flag2=false;
  t2_u = millis();
}
void press_3()
{
  myservo_2.write(angle3_s);
  //reset t3
  t3 = inf;
  //start timing the press time
  t3_s = millis();
  score++;
}
void up_3()
{
  //reset
  t3_s = inf;
  myservo_2.write(angle3_u);
  //flag3=false;
  t3_u = millis();
}

void setup() {
  myservo.attach(11);  // attaches the servo on pin 9 to the servo object
  myservo_1.attach(10);
  myservo_2.attach(9);
  pinMode(LDR_1, INPUT);
  pinMode(LDR_2, INPUT);
  pinMode(LDR_3, INPUT);
  //initialise servos
  myservo.write(angle1_u);
  myservo_1.write(angle2_u);
  myservo_2.write(angle3_u);
}

void loop() {
  //if there is a black block and the servo is not in previous event
  if (!flag1 && digitalRead(LDR_1) == HIGH)
  {
    flag1 = true;
    //start time when detect a black block
    t1 = millis();
    
  }
if (!flag2 && digitalRead(LDR_2) == HIGH)
  {
    flag2 = true;
    t2 = millis();
  }
 if (!flag3 && digitalRead(LDR_3) == HIGH)
  {
    flag3 = true;
    t3 = millis();
  }

//couculate waiting time according to the score in order to follow the beat
wait = 300-score*parameter2;//the time servo needs to wait before pressing after the LDR detects a black block
rest = 500-score*parameter1;// the time to rest before next press

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
 //servo 2
  if ((now() - t2) > wait)
  {

    press_2();
  }
  if (now() - t2_s > stay)
  {
    up_2();
  }
  if ((now() - t2_u) > (rest))
  {
    t2_u = inf;
    flag2 = false;
  }


//Servo 3
  //delay for 0.45s
  if ((now() - t3) > wait)
  {

    press_3();
  }
  if (now() - t3_s > stay)
  {
    up_3();
  }
  if ((now() - t3_u) > (rest))
  {
    t3_u = inf;
    flag3 = false;
  }

  
}
