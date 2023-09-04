//String dataFromClient = "-20,-28,-36,-45,-53,-60,-67,-73,-77,-79,-79,-75,-68,-58,-45,-29,-11,7,26,44,59,71,79,85,86,85,82,76,69,62,54,45,37,28,20,22,29,36,41,45,46,46,42,36,26,13,-2,-22,-44,-67,-90,-112,-132,-147,-158,-164,-164,-160,-153,-142,-129,-115,-101,-86,-72,-59,-48,-37,-27,-19,-19,-27,-37,-48,-60,-73,-87,-102,-117,-131,-145,-156,-165,-169,-170,-165,-154,-139,-120,-98,-74,-50,-28,-7,9,23,33,40,44,45,44,41,36,29,22,2,3,4,6,7,8,9,10,11,11,11,11,10,8,6,3,1,2,5,7,10,11,12,12,12,12,11,10,8,7,6,5,3,2,1,5,7,7,8,7,6,4,2,1,6,12,19,27,35,43,51,58,63,67,69,69,66,63,57,51,45,38,32,26,20,15,11,8,5,3,5,8,11,15,20,26,32,38,45,52,58,63,67,70,70,69,65,60,53,45,36,28,20,13,7,2,1,4,6,7,8,7,7,5,4";
#include <Stepper.h>
#include <Arduino.h>

const int vibuoc = 16;

//String dataFromClient;

#define numberStepper 3
#define numberSplit 35
#define MAXSPEED 20
#define offset_0do -1 // sai số tại 0 độ
const double Tiso = 36.0 / 20.0;

const int home_limit[numberStepper] = {A3, A2, A1};


//int theta[numberStepper][numberSplit];
//int vel[numberStepper][numberSplit];

//int data[numberStepper * 2 * numberSplit] = { -31,-47,-63,-78,-92,-103,-110,-110,-102,-85,-58,-25,11,47,78,102,116,121,118,109,95,80,63,47,30,32,47,58,64,65,58,43,18,-14,-55,-100,-145,-184,-213,-228,-229,-219,-199,-173,-145,-117,-91,-67,-46,-29,-29,-46,-67,-91,-118,-147,-176,-203,-224,-236,-237,-223,-195,-156,-110,-64,-21,13,38,55,63,63,57,47,33,2,3,4,5,6,7,8,8,7,6,3,1,2,5,7,8,9,9,8,7,5,4,3,2,1,4,5,5,5,3,1,4,10,17,25,33,41,46,49,49,47,42,36,29,23,17,12,8,5,2,5,8,12,17,23,29,36,43,47,50,50,48,42,34,26,18,10,4,1,3,5,5,5,4,2}; // 25 sample 1.5s
int data[numberStepper * 2 * numberSplit] = { -19,-26,-31,-35,-37,-38,-36,-31,-24,-14,-1,13,30,48,66,83,99,112,122,128,131,130,126,120,112,102,91,81,70,59,49,40,32,24,16,-20,-29,-37,-45,-53,-61,-69,-75,-81,-85,-87,-87,-84,-78,-69,-58,-44,-28,-12,3,19,33,44,53,60,64,65,64,61,57,52,45,38,30,22,-20,-29,-37,-45,-53,-61,-69,-75,-81,-85,-87,-87,-84,-78,-69,-58,-44,-28,-12,3,19,33,44,53,60,64,65,64,61,57,52,45,38,30,22,3,4,5,6,6,6,5,4,3,1,1,3,6,9,12,15,18,20,20,20,20,20,20,20,19,17,15,13,11,10,8,6,5,3,1,8,11,14,17,19,20,20,20,20,20,20,20,20,20,20,17,12,7,1,4,7,10,13,16,19,20,20,20,20,18,16,14,11,9,7,8,11,14,17,19,20,20,20,20,20,20,20,20,20,20,17,12,7,1,4,7,10,13,16,19,20,20,20,20,18,16,14,11,9,7};//35 sample
//int data[numberStepper * 2 * numberSplit] = {-22,-31,-38,-45,-51,-56,-59,-61,-60,-56,-50,-41,-30,-16,1,15,33,50,65,78,88,96,100,100,99,95,89,81,73,64,55,47,38,29,20,-21,-30,-38,-46,-53,-60,-66,-71,-74,-76,-75,-71,-65,-56,-45,-31,-16,-1,14,29,42,53,61,67,70,71,70,67,62,57,50,43,36,28,20,-18,-26,-35,-44,-54,-65,-76,-87,-99,-110,-120,-128,-135,-139,-140,-137,-130,-120,-107,-91,-73,-55,-37,-19,-3,9,20,28,33,36,36,34,31,25,19,4,6,7,8,9,10,11,11,11,11,10,8,6,4,1,1,4,7,10,12,14,15,16,16,16,15,14,13,11,10,8,7,5,4,2,8,11,13,15,17,18,19,20,19,18,15,12,8,3,2,5,8,11,14,17,20,20,20,20,20,20,20,20,20,20,18,14,11,8,6,8,11,14,17,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,18,10,4,1,3,6,9,10,10,9,7,5};
//int data[numberStepper * numberSplit];
const int stepsPerRevolution = 800 * vibuoc;


// initialize the Stepper library on pins 8 through 11:
Stepper myStepper1(1600 * vibuoc, 5, 2);
Stepper myStepper2(1600 * vibuoc, 6, 3);
Stepper myStepper3(1600 * vibuoc, 7, 4);

int calStep(float theta1, float theta2)
{
  float tmpTheta = theta2 - theta1;
  float tmpNumSteps = tmpTheta / ((float)360 / (float)800 / vibuoc) * Tiso;

  int stepsToGo = tmpNumSteps; // số bước cần di chuyển

  //  Serial.print("So goc: ");
  //  Serial.println(tmpTheta);
  //  Serial.print("So buoc: ");
  //  Serial.println(stepsToGo);
  return stepsToGo;
}

long calSpeed(float vel)
{
  if (vel < 0) // do/giay
  {
    vel = -vel;
  }
  //  vel *= numberSplit;
  vel = int(vel * numberSplit);

  //  Serial.print("Van toc vel: ");
  //  Serial.println(vel);
  return vel;
}

void In_Output()
{
  //  Serial.println("start");
//  while (Serial.available() == 0)
//  {
//  }
  String dataFromClient = Serial.readStringUntil('\n');
  //  Serial.print(dataFromClient);
  unsigned int data_num = 0;
  // loop as long as a comma is found in the string
  while (dataFromClient.indexOf(",") != -1) {
    // take the substring from the start to the first occurence of a comma, convert it to int and save it in the array
    data[ data_num ] = dataFromClient.substring(0, dataFromClient.indexOf(",")).toInt();
    data_num++; // increment our data counter
    //cut the data string after the first occurence of a comma
    dataFromClient = dataFromClient.substring(dataFromClient.indexOf(",") + 1);
  }
  // get the last value out of the string, which as no more commas in it
  data[ data_num ] = dataFromClient.toInt();

  //  Serial.println("end");
  //  for (int i = 0; i < numberStepper * 2 * numberSplit; i++)
  //    Serial.println(data[i]);


}

void RunMotor()
{
int velocity = 10;
  for (int i = 0; i < numberSplit; i++)
  {

    
    //    if (i < 5)
    //    {
    //
    //      myStepper1.setSpeed(velocity / (5));
    //      myStepper2.setSpeed(velocity / (5));
    //      myStepper3.setSpeed(velocity / (5));
    //    }
    //    else if (i > 30)
    //    {
    //      myStepper1.setSpeed(velocity / (5));
    //      myStepper2.setSpeed(velocity / (5));
    //      myStepper3.setSpeed(velocity / (5));
    //    }
    //    else
    //    {
    //      myStepper1.setSpeed(velocity * 1.5);
    //      myStepper2.setSpeed(velocity * 1.5);
    //      myStepper3.setSpeed(velocity * 1.5);
    //    }

    myStepper1.setSpeed(velocity * 1.5);
    myStepper2.setSpeed(velocity * 1.5);
    myStepper3.setSpeed(velocity * 1.5);
    myStepper1.step(-data[0 * numberSplit + i]);
    myStepper2.step(-data[1 * numberSplit + i]);
    myStepper3.step(-data[2 * numberSplit + i]);
  }
  delay(200);
  digitalWrite(10, 1);

  for (int i = numberSplit - 1; i >= 0; i--)
  {
    myStepper1.setSpeed(velocity * 1.5);
    myStepper2.setSpeed(velocity * 1.5);
    myStepper3.setSpeed(velocity * 1.5);
    myStepper1.step(data[0 * numberSplit + i]);
    myStepper2.step(data[1 * numberSplit + i]);
    myStepper3.step(data[2 * numberSplit + i]);
  }
  delay(200);
  digitalWrite(10, 0);


}

void RunOneStep(float theta1, float theta2, float theta3)
{
  int thetaMin = min(min(abs(theta1), abs(theta2)), abs(theta3));
  int thetaMax = max(max(abs(theta1), abs(theta2)), abs(theta3));
  if (thetaMax - thetaMin > 80)
  {
    for (int i = 0; i < 20; i++)
    {
      myStepper1.step(theta1 / 20);
      myStepper2.step(theta2 / 20);
      myStepper3.step(theta3 / 20);
    }
  }
  else
  {
    for (int i = 0; i < 5; i++)
    {
      myStepper1.step(theta1 / 5);
      myStepper2.step(theta2 / 5);
      myStepper3.step(theta3 / 5);
    }
  }

}

void Homming()
{
  //  Serial.println("X, Y, Z plane is homing ...");

  myStepper1.setSpeed(MAXSPEED);
  myStepper2.setSpeed(MAXSPEED);
  myStepper3.setSpeed(MAXSPEED);
  long flagHome = -1; // Biến di chuyển
  while ((digitalRead(home_limit[0]) || digitalRead(home_limit[1]) || digitalRead(home_limit[2])))
  {
    //    Serial.println(digitalRead(home_limit[0]));

    if (digitalRead(home_limit[0]))
    {
      myStepper1.step( calStep(flagHome, 0));

    }
    if (digitalRead(home_limit[1]))
    {
      myStepper2.step( calStep(flagHome, 0));
    }
    if (digitalRead(home_limit[2]))
    {
      myStepper3.step(calStep(flagHome, 0));
    }




    //flagHome--;
  }
  //  Serial.println("Homing is completed!!");
  //  Serial.println("");
}

void Run(float theta[])
{
  for (int j = 0; j < numberSplit * 2; j++)
  {

    myStepper1.setSpeed(MAXSPEED / 2 );
    myStepper2.setSpeed(MAXSPEED / 2 );
    myStepper3.setSpeed(MAXSPEED / 2 );

    myStepper1.step(calStep(theta[0] / (2 * numberSplit), 0));
    myStepper2.step(calStep(theta[1] / (2 * numberSplit), 0));
    myStepper3.step(calStep(theta[2] / (2 * numberSplit), 0));
  }
}
void Restart()
{
  //  Serial.println("->->->->->");
  float RS[3] = { 30 + offset_0do, 30 + offset_0do, 30 + offset_0do};
  //double RS[3] = {30,30,30};
  Run(RS);
  delay(100);


  float RS1[3] = { -22, -22, -22};
  Run(RS1);
  //  Serial.println("<-<-<-<-<-");
  delay(100);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);//bơm
  pinMode(10, OUTPUT);//hút

  pinMode(11, INPUT);//cảm biến
  Serial.begin(115200);

}

bool kt = true;
int a;
long t1;

void loop() {
  // put your main code here, to run repeatedly:

  //  delay(1000);

  //  In_Output();

  if (kt)
  {
    Homming();
    Restart();
    float startTheta[3] = { 32.2328, 32.2328, 32.2328};// toạ độ (100,-100,-450);
    //    float startTheta[3] = { -32.7906, 32.7906, -32.7906}; // toạ độ (100,0,-450);
    //    float startTheta[3] = { -36.4134, 50.4478, -20.5132}; // toạ độ băng chuyền -450
    Run(startTheta);
    delay(1000);
    kt = false;
  }
  In_Output();
  RunMotor();

  if (a) {
    digitalWrite(12, 1);
    t1 = millis();
  }
  else {
    if (millis() - t1 > 15000)
    {
      digitalWrite(12, 0);
    }
  }

  a = digitalRead(11);
//  while (1);

}