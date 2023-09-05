/* Ping))) Sensor
  The circuit:
    +V connection of the PING))) attached to +5V
    GND connection of the PING))) attached to ground
    SIG connection of the PING))) attached to digital pin 7
*/

#ifndef KALMANCPP
#define kalman

#include "arduino.h"
//#include <stdio.h>
//#include <math.h>

class kalmanfillter
{
    double sigma = 0.0;
    double mu = 198.0; // 198.0
    double A = 1; // ma tran chuyen trang thai
    double C = 1; // Ma tran do
    double Q = 0.1; // nhieu qua trinh 0.001
    double R = 3; // nhieu do 0.005

  public:
    double loc(double data)
    {
      double data_loc = klf(mu, sigma, data);
//      delay(20);
      //      Serial.print(data);
      //      Serial.print(',');

      //              Serial.println(data_loc);

      return data_loc;
    }


  private:
    int klf(double mut, double sigmat, double zt)
    {
      // Du doan
      double mu_dudoan = A * mut;
      double sigma_dudoan = A * sigmat * A + Q;
      // Hieu chinh
      double kgain = sigma_dudoan * C / (C * sigma_dudoan * C + R);
      double mu_hieuchinh = mu_dudoan + kgain * (zt - C * mu_dudoan);
      double sigma_hieuchinh = (1 - kgain * C) * sigma_dudoan;
      //
      mu = mu_hieuchinh;
      sigma = sigma_hieuchinh;
      return mu_hieuchinh;
    }
};
#endif
