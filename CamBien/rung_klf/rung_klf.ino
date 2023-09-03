#include <SimpleKalmanFilter.h>

SimpleKalmanFilter klfX(1, 1, 0.01);
SimpleKalmanFilter klfY(1, 1, 0.01);
SimpleKalmanFilter klfZ(1, 1, 0.01);

#define xPin A0
#define yPin A1
#define zPin A2

#define xMin 338+80
#define yMin 343+50
#define zMin 272+20

#define numMau 10025+1

//--------------------------------------------------------------
// Take multiple samples to reduce noise
int count = 0;
const int samples = 10;
//--------------------------------------------------------------

void setup()
{
  Serial.begin(2000000);

  //  Serial.println("CLEARDATA");
  Serial.println("Millis X Y Z");
//
//  while (Serial.available() == 0)
//  {
//  }
//  delay(1000);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  
}


void loop()
{
 

  //--------------------------------------------------------------
  //Read raw values
  int xRaw = 0, yRaw = 0, zRaw = 0;
  for (int i = 0; i < samples; i++)
  {
    xRaw += analogRead(xPin);
    yRaw += analogRead(yPin);
    zRaw += analogRead(zPin);
  }
  xRaw /= samples;
  yRaw /= samples;
  zRaw /= samples;

  //  Serial.print(xRaw - xMin);
  //  Serial.print(" ");
  //
  //  Serial.print(yRaw - yMin);
  //  Serial.print(" ");
  //
  //  Serial.print(zRaw - zMin);
  //  Serial.print(" ");
  //--------------------------------------------------------------

  xRaw = klfX.updateEstimate(xRaw);
  yRaw = klfY.updateEstimate(yRaw);
  zRaw = klfZ.updateEstimate(zRaw);

  //  Serial.print("DATA, TIME,");

//  Serial.print(millis());
  Serial.print(" ");

  //--------------------------------------------------------------
  Serial.print(xRaw - xMin);
  Serial.print(" ");

  Serial.print(yRaw - yMin);
  Serial.print(" ");

  Serial.print(zRaw - zMin);


  if (count >= numMau)
  {
    //    while (1);
  }
  else
  {
    count++;
  }

  Serial.println();
  //--------------------------------------------------------------
  //  delay(20);
}
