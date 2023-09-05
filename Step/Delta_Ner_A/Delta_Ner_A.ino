///////////////
// Robot Delta//
///////////////

#include "arduino.h"
#include "Control_Step.cpp" //50 50 50 -50 -50 -50 0 0 50 50 0 0 0 50 -50 -50 0 0 0 -50 0
#include "Kinematic.cpp"
#include "i2c_Slave.cpp"


float pos[3], theta[3];
float RAD[3];                           // Số góc cần di chuyển, nhập từ cổng Serial
int InputRad[3];

double Tiso = 36.0 / 20.0;
int Vibuoc = 8;

// Khai báo thông số robot
//#define R 120
//#define r 38
//#define L 192
//#define l 415

StepMotor delta;
//i2c_Slave slave_step;
Kinematic Attach;

void setup()
{
  Serial.begin(115200);
  delta.init();
  Attach.init();
  //  Wire.begin(address_slave[slave]); // Khởi tạo thư viện i2c địa chỉ 1
  //  Wire.onReceive(receiveEvent); // khởi tạo chế độ nhận tín hiệu từ boad chủ
  //  slave_step.init();
  //  int GOTO[3];
  //  for (int i = 0; i < 3; i++)
  //    GOTO[i] = 200 * Vibuoc / 360.0 * InputRad[i] * Tiso;
  //slave_step.Max = max(max(abs(GOTO[0]), abs(GOTO[1])), abs(GOTO[2]));

}
void RUN_LINE(float runPoint[]);
void loop()
{

  if (delta.kt) // Chỉ thực hiện Start() duy nhất 1 lần cả chương trình
  {
    delta.Start();

    delta.kt = 0;
  }


//  Input();
  //
//  delta.Run(RADhihi);

  //  slave_step.Run(InputRad[slave]);
  //  delay(500);
  //   put your main code here, to run repeatedly:

  //  Serial.println();
    Attach.drawSquare(100, 100, 450, 200, 200);
  //  delay(500);

  //29 67 41 |23 59 0|52 8 41 -52 -8 -41



}

void Input()
{
  Serial.print("Nhap so buoc can di chuyen: ");
  while (Serial.available() == 0)
  {
  }

  for (int i = 0; i < N; i++)
  {
    RAD[i] = Serial.parseInt(); //Lấy giá trị từ Serial
  }
  Serial.print("Bước nhập: ");
  for (int i = 0; i < 3; i++)
  {
    Serial.print(RAD[i]); //In ra số bước sẽ thực hiện
    Serial.print(" ");
  }
  Serial.println("");

}


void receiveEvent() {
  while (Wire.available()) // chờ cho đến khi có tín hiệu
  {
    //int count =0;
    for (int i = 0; i < 3; i++)
    {
      InputRad[i] = Wire.read(); // để lưu dữ liệu nhận được
    }

    Serial.println("Data received to Slave 1");
    for (int i = 0; i < 3; i++)
      Serial.println(InputRad[i]);
  }
}

//--------//


//bool FKinematic(float theta1,float theta2,float theta3)
//{
//  float t = R-r;
//  theta1 = DEG_TO_RAD*theta1; // deg to radian
//  theta2 = theta2*DEG_TO_RAD;
//  theta3 = theta3*DEG_TO_RAD;
//
//  float y1 = -(t + L*cos(theta1));
//  float z1 = - L * sin(theta1);
//
//  float y2 = (t + L*cos(theta2)) * sin(PI/6);
//  float x2 = y2 * tan(PI/3);
//  float z2 = -L * sin(theta2);
//
//  float y3 = (t + L*cos(theta3)) * sin(PI/6);
//  float x3 = -y3 * tan(PI/3);
//  float z3 = -L * sin(theta3);
//
//  float w1 = pow(y1,2) + pow(z1,2);
//  float w2 = pow(x2,2) + pow(y2,2) + pow(z2,2);
//  float w3 = pow(x3,2) + pow(y3,2) + pow(z3,2);
//
//  float dnm = (y2-y1)*x3 - (y3-y1)*x2;
//
//  float a1 = (z2-z1)*(y3-y1) - (z3-z1)*(y2-y1);
//  float b1= -( (w2-w1)*(y3-y1) - (w3-w1)*(y2-y1) ) / 2;
//
//  float a2 = -(z2-z1)*x3 + (z3-z1)*x2;
//  float b2 = ( (w2-w1)*x3 - (w3-w1)*x2) / 2;
//
//  float a = pow(a1,2) + pow(a2,2) + pow(dnm,2);
//  float b = 2 * (a1*b1 + a2*(b2 - y1*dnm) - z1*pow(dnm,2));
//  float c = (b2 - y1*dnm)*(b2 - y1*dnm) + b1*b1 + pow(dnm,2)*(pow(z1,2) - l*l);
//
//  float d = b*b - 4*a*c;
//  Serial.print("d= ");
//  Serial.println(d);
//  if (d >= 0){
//    pos[2] = -0.5*(b + sqrt(d)) / a; //Z
//    pos[0] = (a1*pos[2] + b1) / dnm; //X
//    pos[1] = (a2*pos[2] + b2) / dnm; //Y
//    if ((abs(pos[0]) > 350 || abs(pos[1]) > 350 ||  pos[2] > 0 || pos[2] < -650))
//      return false;
//    else
//      return true;
//  }
//  else
//    return false;
//  }
//
//float IKinemTh(float x0, float y0, float z0)
//{
//  float theta = 0;
//  float y1 = -R;
//  y0 = y0-r;
//
//  float a = (pow(x0,2) + pow(y0,2) + pow(z0,2) + pow(L,2) - pow(l,2) - pow(y1,2))/(2*z0);
//  float b = (y1-y0)/z0;
//
//  float D = -pow((a + b*y1),2) + pow(L,2)*(pow(b,2)+1);
//  if (D < 0)
//  {
//    theta = 0;// false
//    Serial.println("IK false");
//  }
//  else{
//    float yj = (y1 - a*b - sqrt(D)) / (pow(b,2) + 1);
//    float zj = a + b*yj;
//    theta = atan(-zj/(y1-yj));
//    if (yj>y1)
//    {
//      theta = theta + PI;
//      theta = RAD_TO_DEG*theta;
//      }
//
//    return theta;
//  }
//  }
//
//bool IKinematic(float X, float Y, float Z)
//{
//  float x0 = X;
//  float y0 = Y;
//  float z0 = Z;
//  theta[0] = IKinemTh(x0,y0,z0);
//
//  x0 = X*cos(2*PI/3) + Y*sin(2*PI/3);
//  y0 = Y*cos(2*PI/3) - X*sin(2*PI/3);
//  z0 =Z;
//  theta[1] = IKinemTh(x0,y0,z0);
//  x0 = X*cos(2*PI/3) - Y*sin(2*PI/3);
//
//
//  y0 =Y*cos(2*PI/3) + X*sin(2*PI/3);
//  z0 = Z;
//  theta[2] = IKinemTh(x0,y0,z0);
//  for(int i =0;i<3;i++)
//  {
//    Serial.print(theta[i]);
//    Serial.print(" ");
//      }
//  Serial.println();
//  if (theta[0] != 0 && theta[1] != 0 && theta[2] != 0)
//    return true;
//  else
//    return false;
//  }
//
//void trajectry(float startPoint[], float endPoint[])
//{
//  delay(100);
//  float startTheta[3],endTheta[3],tmpTheta[3];
//  tmpTheta[0] = theta[0];
//  tmpTheta[1] = theta[1];
//  tmpTheta[2] = theta[2];
//
//  if(IKinematic(startPoint[0],startPoint[1],startPoint[2]))
//  {
//    startTheta[0] = theta[0];
//    startTheta[1] = theta[1];
//    startTheta[2] = theta[2];
//    }
//  double tmp[3];
//  tmp[0] = (double) ((startTheta[0]-tmpTheta[0])*RAD_TO_DEG);
//  tmp[1] = (double) ((startTheta[1]-tmpTheta[1])*RAD_TO_DEG);
//  tmp[2] = (double) ((startTheta[2]-tmpTheta[2])*RAD_TO_DEG);
//  Run(tmp);
//
//  if(IKinematic(endPoint[0],endPoint[1],endPoint[2]))
//  {
//    endTheta[0] = theta[0];
//    endTheta[1] = theta[1];
//    endTheta[2] = theta[2];
//    }
//  tmp[0] = (double)((endTheta[0]-startTheta[0])*RAD_TO_DEG);
//  tmp[1] = (double)((endTheta[1]-startTheta[1])*RAD_TO_DEG);
//  tmp[2] = (double)((endTheta[2]-startTheta[2])*RAD_TO_DEG);
//  Run(tmp);
//  }
//
//void drawSquare(float x, float y,float z, float width, float height)
//{
//  float Point1[3]= {x,y,-z};
//  float Point2[3] ={x-width,y,-z};
//  float Point3[3] ={x-width,y-height,-z};
//  float Point4[3] ={x,y-height,-z};
//  trajectry(Point1,Point2);
////  trajectry(Point2,Point1);
//  trajectry(Point2,Point3);
//  trajectry(Point3,Point4);
//  trajectry(Point4,Point1);
//
//
//  }

//float nho[3]={0,0,0};
//double RADhihi[3];
//void RUN_LINE(float runPoint[])
//{
//    for(int i=0;i<3;i++)
//    {
//      RADhihi[i]=runPoint[i]-nho[i];
//      runPoint[i]=RADhihi[i];
//    }
//    delta.Run(RADhihi);
//  
//}
