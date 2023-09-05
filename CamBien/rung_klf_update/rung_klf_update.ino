#include "config.h"

initKlfSensor;

int count = 0;

void setup()
{
  Serial.begin(2000000);
  Serial.flush();
//  Serial.println("Millis,X1,Y1,Z1,X2,Y2,Z2,X3,Y3,Z3,X1.Klf,Y1.Klf,Z1.Klf,X2.Klf,Y2.Klf,Z2.Klf,X3.Klf,Y3.Klf,Z3.Klf");
  //  Serial.println("Millis,X2,Y2,Z2,X3,Y3,Z3,X2.Klf,Y2.Klf,Z2.Klf,X3.Klf,Y3.Klf,Z3.Klf");
}

void loop()
{
    readSensor;

    Serial.print(millis());
    Serial.print(",");

    printSensor;

    klfSensor;

    printSensor;

    Serial.println();
//    delayMicroseconds(100);
}
