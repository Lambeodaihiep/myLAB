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

#ifndef I2C_SLAVECPP
#define I2C_SLAVECPP

#include "AccelStepper.h"
#include "arduino.h"
#include <Wire.h>

#define slave 0 // thay đổi theo số thứ tự của Slave
const int address_slave[3] = {1,2,3};
#define N 3

#define motorInterfaceType 1
#define enable 8
#define MAXSPEED 100000000 // Vận tốc lớn nhất động cơ có thể đạt được

#define offset_L1 6 // sai số giữa L1 và phương ngang
#define kp08 29
#define offset_0do -1 // sai số tại 0 độ
#define offetLength_L1 20


class i2c_Slave
{

  AccelStepper stepper[N];               // Các động cơ bước
  const int step_[N] = {2, 3, 4};        // Chân Step/POL
  const int dir_[N] = {5, 6, 7};         // Chân Dir
  const int home_limit[N] = {9, 10, 11}; // Chân công tắc hành trình
  int ACCEL[N];                          // Gia tốc của động cơ
  int SPEED[N];                          // vận tốc của động cơ
  int GOTO[N];                          // Số bước cần di chuyển, nhập từ cổng Serial
  int SpeedMax = 1000;
  int AccelMax = 50000;
  double Tiso = 36.0 / 20.0;
  int Vibuoc=16;
  int a = 1;
  
  public:
  int kt =1;
  double Max;
  void init()
  {
    //Wire.begin(address_slave[slave]); // Khởi tạo thư viện i2c địa chỉ 1
    //Wire.onReceive(receiveEvent); // khởi tạo chế độ nhận tín hiệu từ boad chủ
    Serial.begin(115200);

    stepper[slave] = AccelStepper(motorInterfaceType, step_[slave], dir_[slave]); //Khai báo các chân ứng với mỗi động cơ
    pinMode(home_limit[slave], INPUT_PULLUP);                             //Khai báo công tắc hành trình
    delay(10);
    pinMode(enable, OUTPUT);   //Chân dừng khẩn cấp
    digitalWrite(enable, LOW); //Tắt
    }
  
  void Run(double Rad)
  {
    Serial.println();
    //RunRad(RAD);
    RunRad(Rad);
    RunStep(GOTO[slave]);
  }

  void Start()
  {
    Homming();

    stepper[slave].setCurrentPosition(0); //Sau khi homing set vị trí đó là 0
    
    delay(10);
    Serial.println("----------");
    Restart();
    
    stepper[slave].setCurrentPosition(0); //Sau khi homing set vị trí đó là 0
    
  }
 
  private:
  

  void Homming()
  {
    Serial.println("Stepper homing is: ");
    Serial.print(slave);
    Serial.println();

    stepper[slave].setMaxSpeed(MAXSPEED);
      ////stepper[i].setSpeed(SpeedMax);
    stepper[slave].setAcceleration(AccelMax);
    
    long flagHome = -1; // Biến di chuyển
    while (digitalRead(home_limit[slave] ))
    {
      //    Serial.println(digitalRead(home_limit[0])*digitalRead(home_limit[1])*digitalRead(home_limit[2]));

      if (digitalRead(home_limit[slave])) // Cho động cơ quay ngược chiều kim đồng hồ
      {
        stepper[slave].moveTo(flagHome);
        stepper[slave].move(flagHome);
        stepper[slave].run();
      }
      flagHome--;
    }
    Serial.println("Homing completed is ");
    Serial.print(slave);
    Serial.println("");
  }

  void Restart()
  {
    Serial.println("->->->->->");
    double RS[3] = {30+offset_0do, 30+offset_0do, 30+offset_0do};
    //double RS[3] = {30,30,30};
    RunUN(RS[slave]);
    delay(100);

    Serial.println("<-<-<-<-<-");
    double RS1[3] = { -22, -22, -22};
    Run(RS1[slave]);
    delay(100);
  }

  void RunUN(double RAD)
  {
    RunRad(RAD);

    RunStepUN(GOTO[slave]);
  }

  void RunRad(double Rad)
  {
  // 360=3200; tỷ số 1/16
  // 360 =200; tỷ số 1/1

    GOTO[slave] = 200*Vibuoc / 360.0 * Rad*Tiso;
  }

  int Kt()
  {
    if (stepper[slave].distanceToGo() != 0)
    {
      return 1;
    }

    return 0;
  }
  
  void RunStepUN(int Togo)
  {
    Serial.println("cac buoc can di");
  
    Serial.println(Togo);
    Speed(Togo);
    Serial.println("toc do cac buoc");
  
    Serial.println(SPEED[slave]);
  
    Serial.println("gia toc cac buoc");
 
    Serial.println(ACCEL[slave]);
  
  
    stepper[slave].setMaxSpeed(MAXSPEED);
    //stepper[i].setSpeed(SPEED[i]);
    stepper[slave].setAcceleration(ACCEL[slave]);
    stepper[slave].moveTo(Togo);
    stepper[slave].move(Togo);

    while (Kt())
    {
      if (stepper[slave].distanceToGo() != 0)
      {
        stepper[slave].run();
      }
    }
  }

  void RunStep(int Togo)
  {
    Serial.println("cac buoc can di");
  
    Serial.println(Togo);
    Speed(Togo);
    Serial.println("toc do cac buoc");
  
    Serial.println(SPEED[slave]);
  
    Serial.println("gia toc cac buoc");
  
    Serial.println(ACCEL[slave]);
  
    stepper[slave].setMaxSpeed(MAXSPEED);
    //stepper[i].setSpeed(SPEED[i]);
    stepper[slave].setAcceleration(ACCEL[slave]);
    stepper[slave].moveTo(Togo);
    stepper[slave].move(Togo);
  

    while (Kt())
    {
      if (stepper[slave].distanceToGo() != 0)
      {
        stepper[slave].run();
        limited();
      }
    }
  }
  

  // cân bằng tốc độ giữa các động cơ sử dụng i2c
  void Speed(int Togo)
  {
    //double Max = max(max(abs(Togo[0]), abs(Togo[1])), abs(Togo[2]));
    //double Max = Togo;
  
    SPEED[slave] = SpeedMax / Max * Togo;
    ACCEL[slave] = AccelMax / Max * Togo;
  
  }
  void limited()
  {
    if (!digitalRead(home_limit[slave])) // Cho động cơ quay ngược chiều kim đồng hồ
    {
      double RS[3] = {10, 10, 10};
//    RunUN(RS);
      kt = 1;
      loop();
      
      }
  }

  
  };


#endif
