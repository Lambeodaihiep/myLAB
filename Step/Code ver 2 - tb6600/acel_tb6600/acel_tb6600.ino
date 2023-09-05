#include <Arduino.h>

#include "config.h"

#include "AccelStepper.h"
AccelStepper stepper[2];

void stepperInit();   // Khai báo step với thư viện
void stepperStart();  // Khởi tạo (bao gồm Homing khi bắt đầu chạy và home về giữa)
void stepperHoming(); // Homing cho động cơ về vị trí ban đầu
void stepperHome();   // di chuyển động cơ về vị trí giữa, đặt là home
void readAngle();     // Nhập xuất dữ liệu bằng góc đơn vị độ
void deg2step();      // Truyền số bước, gia tốc cho động cơ
void theAccel();      // Tính toán gia tốc cho từng động cơ
void stepperRun();    // Thực hiện chạy động cơ


void setup() // chỉ chạy 1 lần duy nhất
{
  Serial.begin(9600); // khai báo sử dụng serial cổng 9600

  stepperInit(); // khai báo step
}

int kt = true; // biến khiểm tra
void loop()
{
  if (kt) // các hàm trong này chỉ thực hiện một lần duy nhất trong loop
  {

    //    stepperStart(); // khởi tạo step
    delay(500);

    kt = false;
  }
  readAngle();  // đọc vào giá trị từ serial
  stepperRun(); // chạy các giá trị vừa nhập
}

void stepperInit()
{
  for (int i = 0; i < N; i++)
  {
    stepper[i] = AccelStepper(motorInterfaceType, step[i], dir[i]); // Khai báo các chân ứng với mỗi động cơ
    pinMode(swLimit[i], INPUT_PULLUP);                              // Khai báo công tắc hành trình
  }
  delay(10);

  pinMode(en, OUTPUT);   // Chân dừng khẩn cấp
  digitalWrite(en, HIGH); // Tắt
}
void stepperStart()
{
  stepperHoming(); // thực hiện homming

  stepperHome(); // ra vị trí chính giữa
  for (int i = 0; i < N; i++)
  {
    stepper[i].setMaxSpeed(MAXSPEED); // Khởi tạo Vận tốc lớn nhất cho động cơ
  }
}

//----------------

void stepperHoming()
{
  Serial.println("X, Y plane is homing ...");
  for (int i = 0; i < N; i++) // Khởi tạo Vận tốc và Gia tốc
  {
    stepper[i].setMaxSpeed(MAXSPEED);
    stepper[i].setAcceleration(MAXACCEL);
  }

  long flagHome = 1; // Biến kiểm tra công tắc hành trình

  while (digitalRead(swLimit[0]) * digitalRead(swLimit[1]) == 0) // chừng nào có 1 trong 2 động
  { // cơ chưa về vị trí homing
    for (int i = 0; i < N; i++)                                  // for chạy lần lượt từng động cơ
    {
      if (digitalRead(swLimit[i]) != 1) // Nếu động cơ chưa homing xong
      {
        stepper[i].moveTo(flagHome); // Cho động cơ quay ngược chiều kim đồng hồ
        stepper[i].move(flagHome);
        stepper[i].run();
      }
    }
    flagHome++; // tăng giá trị cần quay về
    delayMicroseconds(1000);
  }

  for (int i = 0; i < N; i++)
  {
    stepper[i].setCurrentPosition(0); // Sau khi homing set vị trí đó là 0
  }


}

void stepperHome()
{


  for (int i = 0; i < N; i++) // Khởi tạo Vận tốc và Gia tốc
  {
    stepper[i].setMaxSpeed(MAXSPEED);
    stepper[i].setAcceleration(MAXACCEL);
  }
  degToGo[0] = degHome1; // đưa robot về giữa
  degToGo[1] = degHome2; // đưa robot về giữa

  stepperRun();

}

void readAngle()
{


  for (int i = 0; i < N; i++)
  {
    degToGo[i] = degGo[index];
    index++;
    if (index > numDeg)
    {
      index=0;

    }
    delay(5);
  }


}

void deg2step()
{
  theAccel();

  for (int i = 0; i < N; i++)                                // đổi từ góc sang bước,
  { // chia góc cho 1.8/microStep (vi bước)
    stepToGo[i] = degToGo[i] * microStep * ratioPuley / 1.8; // sau đó nhân với tỉ số
    //    stepToGo[i] = degToGo[i];
  }                                                          // truyền của bánh răng và dây đai



  for (int i = 0; i < N; i++)
  {
    stepper[i].moveTo(stepToGo[i]);       // gán các bước cần di chuyển cho step
    stepper[i].move(stepToGo[i]);         //
    stepper[i].setAcceleration(accel[i]); // gán gia tốc cho từng động cơ
    stepper[i].setMaxSpeed(MAXSPEED);


  }

  delay(10);

}

void theAccel()
{
  accel[0] = MAXACCEL; // cho động cơ 1 mặc định là maxAccel

  for (int i = 0; i < N; i++)                        // các động cơ khác nhận giá trị
  { // tỉ lệ so với động cơ 1
    accel[i] = (degToGo[i] / degToGo[0]) * accel[0]; // để đảm bảo
  }                                                  // các động cơ dừng đồng thời
}

void stepperRun()
{
  deg2step();

  while (stepper[0].distanceToGo() != 0) // Tiếp tục stepperRun() khi chưa thực hiện đủ bước
  {
    stepper[0].run();
    stepper[1].run();
  }
}
