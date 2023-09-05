//#include "kalman.cpp"

#define xPin A3
#define yPin A4
#define zPin A5

#define xMin 15
#define yMin -20
#define zMin -10

//--------------------------------------------------------------
// Take multiple samples to reduce noise
int count = 0;
const int samples = 10;
//--------------------------------------------------------------

//kalmanfillter klfx;
//
//kalmanfillter klfy;
//
//kalmanfillter klfz;
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


  //  Serial.print("DATA, TIME,");

//  Serial.print(millis());
  Serial.print(" ");

  //--------------------------------------------------------------
//  Serial.print(klfx.loc(xRaw) - xMin);
//  Serial.print(" ");
//
//  Serial.print(klfy.loc(yRaw) - yMin);
//  Serial.print(" ");
//
//  Serial.print(klfz.loc(zRaw) - zMin);


  if(count>=2600)
  {
//    while(1);
  }
  else
  {
    count++;
  }

      Serial.print(xRaw - xMin);
      Serial.print(",");
  
      Serial.print(yRaw - yMin);
      Serial.print(",");
  
      Serial.print(zRaw - zMin);
  //
  Serial.println();
  //--------------------------------------------------------------
  //  delay(20);
}
