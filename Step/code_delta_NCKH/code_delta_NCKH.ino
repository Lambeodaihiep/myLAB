///////////////
//Robot Delta//
///////////////

#include "arduino.h"
#include "Control_Step.cpp" //50 50 50 -50 -50 -50 0 0 50 50 0 0 0 50 -50 -50 0 0 0 -50 0
#include "Kinematic.cpp"


int bom = 10;
int dai = 11;
int kich = 0;


float pos[3], theta[3];
float RAD[3];                           // Số góc cần di chuyển, nhập từ cổng Serial
int InputRad[3];

double Tiso = 36.0 / 20.0;
int Vibuoc = 16;

// Khai báo thông số robot
//#define R 120
//#define r 38
//#define L 192
//#define l 415

StepMotor delta;

Kinematic Attach;

void setup()
{
  Serial.begin(115200);
  delta.init();
  Attach.init();

  pinMode(bom, OUTPUT);
  pinMode(dai, OUTPUT);

  dung_bang();
  bom_nha();
}

float homePoint[] = {0, 0, -460};
float tagetPoint[] = {0, 0, -400};


float homePoint0[] = {0, 70, -440};
float tagetPoint0[] = {0, -70, -440};

float tagetPoint1[3];

int lenh;

void RUN_LINE(float runPoint[]);
void loop()
{

  if (delta.kt) // Chỉ thực hiện Start() duy nhất 1 lần cả chương trình
  {
    delta.Start(); //đây là code homming, nếu dùng thì comment đồng thời đường thẳng và máy khâu, không được cmt cái này

    delta.kt = 0;
  }

//  may_khau(); //-> bật cái này và comment cái đường thẳng //đây là code may khau

  Attach.drawLine(homePoint0, tagetPoint0); //đây là code đường thẳng, bật lên nếu thực hiện khảo sát
  Attach.drawLine(tagetPoint0, homePoint0); //đây là code đường thẳng, bật lên nếu thực hiện khảo sát


//******************************************************************************************
//  gotoPoint();

//  hoat_dong();


}

void input()
{
  Serial.print("Nhap so buoc can di chuyen: ");
  while (Serial.available() == 0)
  {
  }

  lenh = Serial.parseInt();
  for (int i = 0; i < 2; i++)
  {
    tagetPoint[i] = Serial.parseInt(); //Lấy giá trị từ Serial
  }
  Serial.print("Bước nhập: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(tagetPoint[i]); //In ra số bước sẽ thực hiện
    Serial.print(" ");
  }
  Serial.println("");
}

void may_khau()
{
  Attach.drawLine(homePoint, tagetPoint);
  Attach.drawLine(tagetPoint, homePoint);
}

void hoat_dong()
{

  input();
  while (tagetPoint[0] + tagetPoint[1] == 0)
  {
    input();
  }


  dung_bang();
  Serial.println("go go go");
  Attach.goto_attach(homePoint, tagetPoint);

  bom_hut();
  delay(1000);




  //  chay_bang();
  Attach.goto_attach(tagetPoint, homePoint);
  bom_nha();






}

void gotoPoint()
{


  input();
  while (tagetPoint[0] + tagetPoint[1] == 0)
  {
    input();
  }

  Serial.println("go go go");
  Attach.drawLine(homePoint, tagetPoint);

  for (int i = 0; i < 3; i++)
  {
    homePoint[i] = tagetPoint[i];
  }

}

void bom_hut()
{
  digitalWrite(bom, kich);
  delay(1000);
}

void bom_nha()
{
  digitalWrite(bom, !kich);
  delay(500);
}

void chay_bang()
{
  digitalWrite(dai, kich);
  delay(500);
}

void dung_bang()
{
  digitalWrite(dai, !kich);
  delay(500);
}
