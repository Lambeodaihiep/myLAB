/*
  Arduino Tetris
  Copyright (C) 2015 João André Esteves Vilaça

  https://github.com/vilaca/Handheld-Color-Console

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef KINEMATICCPP
#define KINEMATICCPP

#include "C:\Users\DELL\Documents\PlatformIO\Projects\delta\.pio\libdeps\megaatmega2560\Control_Step.cpp"
#include "arduino.h"

// Khai báo thông số robot
#define R 120
#define r 38
#define L 192
#define l 425

class Kinematic
{
    float pos[3], theta[3];
  public:
    StepMotor motor;
    void init()
    {
      motor.init();
    }
    void drawLine(float startPoint[], float endPoint[])
    {
      //    delay(100);
      float startTheta[3], endTheta[3], tmpTheta[3];
      tmpTheta[0] = theta[0];
      tmpTheta[1] = theta[1];
      tmpTheta[2] = theta[2];

      if (IKinematic(startPoint[0], startPoint[1], startPoint[2]))
      {
        startTheta[0] = theta[0];
        startTheta[1] = theta[1];
        startTheta[2] = theta[2];
      }
      double tmp[3];
      tmp[0] = (double) ((startTheta[0] - tmpTheta[0]) * RAD_TO_DEG);
      tmp[1] = (double) ((startTheta[1] - tmpTheta[1]) * RAD_TO_DEG);
      tmp[2] = (double) ((startTheta[2] - tmpTheta[2]) * RAD_TO_DEG);

      //Serial.println("ggg");
      //Serial.println(tmp[0]);
      //Serial.println(tmp[1]);
      //Serial.println(tmp[2]);
      motor.Run(tmp);

      if (IKinematic(endPoint[0], endPoint[1], endPoint[2]))
      {
        endTheta[0] = theta[0];
        endTheta[1] = theta[1];
        endTheta[2] = theta[2];
      }
      tmp[0] = (double)((endTheta[0] - startTheta[0]) * RAD_TO_DEG);
      tmp[1] = (double)((endTheta[1] - startTheta[1]) * RAD_TO_DEG);
      tmp[2] = (double)((endTheta[2] - startTheta[2]) * RAD_TO_DEG);
      motor.Run(tmp);
      //Serial.println("ggg...");
      //Serial.println(tmp[0]);
      //Serial.println(tmp[1]);
      //Serial.println(tmp[2]);
    }

    int go_up = 40;
    
    void goto_attach(float startPoint[], float endPoint[])
    {
      float startPoint1[3] = {startPoint[0], startPoint[1], startPoint[2] + go_up};
      float endPoint1[3] = {endPoint[0], endPoint[1], startPoint[2] + go_up};

      drawLine(startPoint, startPoint1);
      drawLine(startPoint1, endPoint1);
      drawLine(endPoint1, endPoint);



    }
    void drawSquare(float x, float y, float z, float width, float height)
    {
      float Point1[3] = {100, 100, -450};
      float Point1_tamgiac[3] = { -100, 0, -450};
      float Point2_tamgiac[3] = {100, -100, -450};
      float Point2[3] = { -100, 100, -450};
      float Point3[3] = { -100, -100, -450};
      float Point4[3] = {100, -100, -450};

      float Point1_star[3] = {100, 100, -450};
      float Point2_star[3] = {53.35, 8.48, -450};
      float Point3_star[3] = {126.01, -64.2, -450};
      float Point4_star[3] = {24.52, -48.13, -450};
      float Point5_star[3] = { -22.12, -139.68, -450};
      float Point6_star[3] = { -38.2, -38.2, -450};
      float Point7_star[3] = { -141.42, -22.12, -450};
      float Point8_star[3] = { -48.13, 24.52, -450};
      float Point9_star[3] = { -64.2, 126.01, -450};
      float Point10_star[3] = {8.45, 53.35, -450};




      //    ve tam giac va hinh vuong
      //    drawLine(Point1,Point2);
      //
      drawLine(Point2, Point3);
      drawLine(Point3, Point4);
      drawLine(Point4, Point1);
      drawLine(Point1, Point1_tamgiac);
      drawLine(Point2_tamgiac, Point1);

      // ve ngoi sao
      drawLine(Point1_star, Point2_star);
      drawLine(Point2_star, Point3_star);
      drawLine(Point3_star, Point4_star);
      drawLine(Point4_star, Point5_star);
      drawLine(Point5_star, Point6_star);
      drawLine(Point6_star, Point7_star);
      drawLine(Point7_star, Point8_star);
      drawLine(Point8_star, Point9_star);
      drawLine(Point9_star, Point10_star);
      drawLine(Point10_star, Point1_star);

      //    delay(500);
      //    drawLine(Point3,Point1);
      //
      ////    drawLine(Point2,Point1);
      //    delay(500);
      //
      //    drawLine(Point4,Point1);


    }

  private:
    bool FKinematic(float theta1, float theta2, float theta3)
    {
      float t = R - r;
      theta1 = DEG_TO_RAD * theta1; // deg to radian
      theta2 = theta2 * DEG_TO_RAD;
      theta3 = theta3 * DEG_TO_RAD;

      float y1 = -(t + L * cos(theta1));
      float z1 = - L * sin(theta1);

      float y2 = (t + L * cos(theta2)) * sin(PI / 6);
      float x2 = y2 * tan(PI / 3);
      float z2 = -L * sin(theta2);

      float y3 = (t + L * cos(theta3)) * sin(PI / 6);
      float x3 = -y3 * tan(PI / 3);
      float z3 = -L * sin(theta3);

      float w1 = pow(y1, 2) + pow(z1, 2);
      float w2 = pow(x2, 2) + pow(y2, 2) + pow(z2, 2);
      float w3 = pow(x3, 2) + pow(y3, 2) + pow(z3, 2);

      float dnm = (y2 - y1) * x3 - (y3 - y1) * x2;

      float a1 = (z2 - z1) * (y3 - y1) - (z3 - z1) * (y2 - y1);
      float b1 = -( (w2 - w1) * (y3 - y1) - (w3 - w1) * (y2 - y1) ) / 2;

      float a2 = -(z2 - z1) * x3 + (z3 - z1) * x2;
      float b2 = ( (w2 - w1) * x3 - (w3 - w1) * x2) / 2;

      float a = pow(a1, 2) + pow(a2, 2) + pow(dnm, 2);
      float b = 2 * (a1 * b1 + a2 * (b2 - y1 * dnm) - z1 * pow(dnm, 2));
      float c = (b2 - y1 * dnm) * (b2 - y1 * dnm) + b1 * b1 + pow(dnm, 2) * (pow(z1, 2) - l * l);

      float d = b * b - 4 * a * c;
      //Serial.print("d= ");
      //Serial.println(d);
      if (d >= 0) {
        pos[2] = -0.5 * (b + sqrt(d)) / a; //Z
        pos[0] = (a1 * pos[2] + b1) / dnm; //X
        pos[1] = (a2 * pos[2] + b2) / dnm; //Y
        if ((abs(pos[0]) > 350 || abs(pos[1]) > 350 ||  pos[2] > 0 || pos[2] < -650))
          return false;
        else
          return true;
      }
      else
        return false;
    }

    float IKinemTh(float x0, float y0, float z0)
    {
      float theta = 0;
      float y1 = -R;
      y0 = y0 - r;

      float a = (pow(x0, 2) + pow(y0, 2) + pow(z0, 2) + pow(L, 2) - pow(l, 2) - pow(y1, 2)) / (2 * z0);
      float b = (y1 - y0) / z0;

      float D = -pow((a + b * y1), 2) + pow(L, 2) * (pow(b, 2) + 1);
      if (D < 0)
      {
        theta = 0;// false
        //Serial.println("IK false");
      }
      else {
        float yj = (y1 - a * b - sqrt(D)) / (pow(b, 2) + 1);
        float zj = a + b * yj;
        theta = atan(-zj / (y1 - yj));
        if (yj > y1)
        {
          theta = theta + PI;
          theta = RAD_TO_DEG * theta;
        }

        return theta;
      }
    }

    bool IKinematic(float X, float Y, float Z)
    {
      float x0 = X;
      float y0 = Y;
      float z0 = Z;
      theta[0] = IKinemTh(x0, y0, z0);

      x0 = X * cos(2 * PI / 3) + Y * sin(2 * PI / 3);
      y0 = Y * cos(2 * PI / 3) - X * sin(2 * PI / 3);
      z0 = Z;
      theta[1] = IKinemTh(x0, y0, z0);
      x0 = X * cos(2 * PI / 3) - Y * sin(2 * PI / 3);


      y0 = Y * cos(2 * PI / 3) + X * sin(2 * PI / 3);
      z0 = Z;
      theta[2] = IKinemTh(x0, y0, z0);
      for (int i = 0; i < 3; i++)
      {
        //Serial.print(theta[i]);
        //Serial.print(" ");
      }
      //Serial.println();
      if (theta[0] != 0 && theta[1] != 0 && theta[2] != 0)
        return true;
      else
        return false;
    }



};


#endif
