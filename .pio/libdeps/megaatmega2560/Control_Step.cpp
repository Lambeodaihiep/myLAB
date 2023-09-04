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

#ifndef CONTROL_STEPCPP
#define CONTROL_STEPCPP

#include "AccelStepper.h"
#include "arduino.h"

#define motorInterfaceType 1
#define enable 8
#define MAXSPEED 1000 // Vận tốc lớn nhất động cơ có thể đạt được

#define offset_L1 6 // sai số giữa L1 và phương ngang
#define kp08 29
#define offset_0do -1 // sai số tại 0 độ
#define offetLength_L1 20

const int N = 3;
const int N_NEW = 6;

class StepMotor
{
    AccelStepper stepper[N];               // Các động cơ bước
    const int step_[N] = {3, 4, 2};        // Chân Step/POL
    const int dir_[N] = {6, 7, 5};         // Chân Dir
    const int home_limit[N] = {A2, A1, A3}; // Chân công tắc hành trình
    
    int ACCEL[N];                          // Gia tốc của động cơ
    int SPEED[N];                          // vận tốc của động cơ
    int GOTO[N];                          // Số bước cần di chuyển, nhập từ cổng Serial

    int GOTO_NEW[N];
    int high_speed = 0;//3000;
    int SpeedMax = 1000+high_speed;
    int AccelMax = 2000+high_speed;
    double Tiso = 37.0 / 20.0;
    int Vibuoc = 16;
    int a = 1;

  public:
    int kt = 1;
    void init()
    {
      for (int i = 0; i < N; i++)
      {
        stepper[i] = AccelStepper(motorInterfaceType, step_[i], dir_[i]); // Khai báo các chân ứng với mỗi động cơ
        pinMode(home_limit[i], INPUT);                                    // Khai báo công tắc hành trình
      }
      delay(10);
      pinMode(enable, OUTPUT); // Chân dừng khẩn cấp
      digitalWrite(enable, HIGH);
    }
    int getTheta1() {
      return stepper[0].currentPosition();
    }
    int getTheta2() {
      return stepper[1].currentPosition();
    }
    int getTheta3() {
      return stepper[2].currentPosition();
    }
    void Run(double Rad[])
    {
//      //Serial.println();
      //RunRad(RAD);
      RunRad(Rad);
      RunStep(GOTO_NEW);
    }
    void Run_NEW(double Rad[])
    {
//      //Serial.println();
      //RunRad(RAD);
      RunRad_NEW(Rad);
      RunStep_NEW(GOTO);
    }
    void Start()
    {
      Homming();
      for (int i = 0; i < 3; i++)
      {
        stepper[i].setCurrentPosition(0); //Sau khi homing set vị trí đó là 0
      }
      delay(10);
      //Serial.println("----------");
      Restart();
      for (int i = 0; i < 3; i++)
      {
        stepper[i].setCurrentPosition(0); //Sau khi homing set vị trí đó là 0
      }
    }


  private:


    void Homming()
    {
      //Serial.println("X, Y, Z plane is homing ...");

      for (int i = 0; i < N; i++) // Khởi tạo Vận tốc và Gia tốc 0.18 0.94 0.41 1.02 0.30 0.85
      {
        stepper[i].setMaxSpeed(MAXSPEED);
        ////stepper[i].setSpeed(SpeedMax);
        stepper[i].setAcceleration(500);
      }
      long flagHome = -1; // Biến di chuyển
      while (digitalRead(home_limit[0]) || digitalRead(home_limit[1]) || digitalRead(home_limit[2]))
      {
        //Serial.println(digitalRead(home_limit[0])*digitalRead(home_limit[1])*digitalRead(home_limit[2]));
        for (int i = 0; i < N; i++)
        {
          if (digitalRead(home_limit[i])) // Cho động cơ quay ngược chiều kim đồng hồ
          {
            stepper[i].moveTo(flagHome);
            stepper[i].move(flagHome);
            stepper[i].run();
          }
        }
        flagHome--;
      }
      //Serial.println("Homing is completed!!");
      //Serial.println("");
    }

    void Restart()
    {
      //Serial.println("->->->->->");
      double RS[3] = {30 + offset_0do, 30 + offset_0do, 30 + offset_0do};
      //double RS[3] = {30,30,30};
      Run(RS);
      delay(500);

      //Serial.println("<-<-<-<-<-");
      double RS1[3] = { -27, -27, -27};
      Run(RS1);
      delay(500);
    }

    void RunUN(double RAD[])
    {
      RunRad(RAD);

      RunStepUN(GOTO);
    }

    void RunRad(double Rad[])
    {
      // 360=3200; tỷ số 1/16
      // 360 =200; tỷ số 1/1

      for (int i = 0; i < N; i++)
      {
        GOTO_NEW[i] = 200 * Vibuoc / 360.0 * Rad[i] * Tiso;
      }
    }


    void RunRad_NEW(double Rad[])
    {
      // 360=3200; tỷ số 1/16
      // 360 =200; tỷ số 1/1

      for (int i = 0; i < N_NEW; i++)
      {
        GOTO[i] = 200 * Vibuoc / 360.0 * Rad[i] * Tiso;
      }
    }

    int Kt()
    {
      if (stepper[0].distanceToGo() != 0 || stepper[1].distanceToGo() != 0 || stepper[2].distanceToGo() != 0)
      {
        return 1;
      }

      return 0;
    }

    void RunStepUN(int Togo[])
    {
      //Serial.println("cac buoc can di");
      for (int i = 0; i < N; i++)
      {
        //Serial.println(Togo[i]);
      }
      Speed(Togo);
      //Serial.println("toc do cac buoc");
      for (int i = 0; i < N; i++)
      {
        //Serial.println(SPEED[i]);
      }
      //Serial.println("gia toc cac buoc");
      for (int i = 0; i < N; i++)
      {
        //Serial.println(ACCEL[i]);
      }
      for (int i = 0; i < N; i++)
      {
        stepper[i].setMaxSpeed(MAXSPEED);
        //stepper[i].setSpeed(SPEED[i]);
        stepper[i].setAcceleration(ACCEL[i]);
        stepper[i].moveTo(Togo[i]);
        stepper[i].move(Togo[i]);
      }

      while (Kt())
      {
        for (int i = 0; i < N; i++)
        {
          if (stepper[i].distanceToGo() != 0)
          {
            stepper[i].run();
          }
        }
      }
    }

    void RunStep(int Togo[])
    {
      //Serial.println("cac buoc can di");
      for (int i = 0; i < N; i++)
      {
        //Serial.println(Togo[i]);
      }
      Speed(Togo);
      //Serial.println("toc do cac buoc");
      for (int i = 0; i < N; i++)
      {
        //Serial.println(SPEED[i]);
      }
      //Serial.println("gia toc cac buoc");
      for (int i = 0; i < N; i++)
      {
        //Serial.println(ACCEL[i]);
      }
      for (int i = 0; i < N; i++)
      {
        stepper[i].setMaxSpeed(MAXSPEED);
        //stepper[i].setSpeed(SPEED[i]);
        stepper[i].setAcceleration(ACCEL[i]);
        stepper[i].moveTo(Togo[i]);
        stepper[i].move(Togo[i]);
      }

      while (Kt())
      {
        for (int i = 0; i < N; i++)
        {
          if (stepper[i].distanceToGo() != 0)
          {
            stepper[i].run();
//            limited();
          }
        }
      }
    }

    void RunStep_NEW(int Togo[])
    {
      //Serial.println("cac buoc can di");
      for (int i = 0; i < N_NEW; i++)
      {
        //Serial.println(Togo[i]);
      }

      Speed(Togo);
      //Serial.println("gia toc cac buoc");
      for (int i = 0; i < N; i++)
      {
        //Serial.println(ACCEL[i]);
      }

      for (int i = 0; i < N; i++)
      {
        stepper[i].setMaxSpeed(MAXSPEED);
        //stepper[i].setSpeed(SPEED[i]);
        stepper[i].setAcceleration(ACCEL[i]);
        stepper[i].moveTo(Togo[i]);
        stepper[i].move(Togo[i]);
      }

      while (Kt())
      {
        for (int i = 0; i < N; i++)
        {
          if (stepper[i].distanceToGo() != 0)
          {
            stepper[i].run();
            limited();
          }
        }
      }

      //----------------------------
      for (int i = 0; i < N; i++)
      {
        stepper[i].setMaxSpeed(MAXSPEED);
        //stepper[i].setSpeed(SPEED[i]);
        stepper[i].setAcceleration(ACCEL[i]);
        stepper[i].moveTo(Togo[i + 3]);
        stepper[i].move(Togo[i + 3]);
      }

      while (Kt())
      {
        for (int i = 0; i < N; i++)
        {
          if (stepper[i].distanceToGo() != 0)
          {
            stepper[i].run();
            limited();
          }
        }
      }
    }
    void Speed(int Togo[])
    {
      double Max = max(max(abs(Togo[0]), abs(Togo[1])), abs(Togo[2]));
      for (int i = 0; i < N; i++)
      {
        SPEED[i] = SpeedMax / Max * Togo[i];
        ACCEL[i] = AccelMax / Max * Togo[i];
      }
    }

    void Speed_NEW(int Togo_NEW[])
    {
      int Togo[3];
      for (int i = 0; i < N_NEW - 3; i++)
      {
        Togo[i] = Togo_NEW[i] + Togo_NEW[i + 3];
      }
      double Max = max(max(abs(Togo[0]), abs(Togo[1])), abs(Togo[2]));
      for (int i = 0; i < N; i++)
      {
        SPEED[i] = SpeedMax / Max * Togo[i];
        ACCEL[i] = AccelMax / Max * Togo[i];
      }
    }

    void limited()
    {
      for (int i = 0; i < N; i++)
      {
        if (!digitalRead(home_limit[i])) // Cho động cơ quay ngược chiều kim đồng hồ
        {
          double RS[3] = {10, 10, 10};
          //      RunUN(RS);
          kt = 1;
          loop();
        }
      }
    }


};


#endif
