#include "kalman.cpp"
#include <SimpleKalmanFilter.h>

SimpleKalmanFilter klfX(1, 1, 0.01);

kalmanfillter klfx;

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

  Serial.print(millis());
  Serial.print(" ");

  Serial.print(xRaw - xMin);
  Serial.print(" ");
  //
  //  Serial.print(yRaw - yMin);
  //  Serial.print(" ");
  //
  //  Serial.print(zRaw - zMin);
  //  Serial.print(" ");

  Serial.print(klfx.loc(xRaw) - xMin);
  Serial.print(" ");


  //--------------------------------------------------------------

  xRaw = klfX.updateEstimate(xRaw);
  //  yRaw = klfY.updateEstimate(yRaw);
  //  zRaw = klfZ.updateEstimate(zRaw);

  //  Serial.print("DATA, TIME,");

  //--------------------------------------------------------------
  Serial.print(xRaw - xMin);
  Serial.print(" ");

  //  Serial.print(yRaw - yMin);
  //  Serial.print(" ");

  //  Serial.print(zRaw - zMin);


  if (count >= numMau)
  {
    while (1);
  }
  else
  {
    count++;
  }

  Serial.println();
  //--------------------------------------------------------------
  //  delay(20);
}
