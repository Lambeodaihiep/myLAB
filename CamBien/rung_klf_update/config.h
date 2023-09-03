#define xPin1 A0
#define yPin1 A1
#define zPin1 A2

#define xPin2 A3
#define yPin2 A4
#define zPin2 A5

#define xPin3 A6
#define yPin3 A7
#define zPin3 A8

//----------------------

//#define xMin1 427
//#define yMin1 45
//#define zMin1 36
//
//#define xMin2 43
//#define yMin2 42
//#define zMin2 50
//
//#define xMin3 89
//#define yMin3 89
//#define zMin3 89
//
//#define xGnd 150
//#define yGnd 100
//#define zGnd 50
//#define addGnd 5
//
//#define xCalib1 xMin1 + xGnd
//#define yCalib1 yMin1 + yGnd
//#define zCalib1 zMin1 + zGnd
//
//#define xCalib2 xMin2 + xGnd + addGnd
//#define yCalib2 yMin2 + yGnd + addGnd
//#define zCalib2 zMin2 + zGnd + addGnd
//
//#define xCalib3 xMin3 + xGnd + addGnd + addGnd
//#define yCalib3 yMin3 + yGnd + addGnd + addGnd
//#define zCalib3 zMin3 + zGnd + addGnd + addGnd

#define xCalib1 0
#define yCalib1 0
#define zCalib1 0

#define xCalib2 0
#define yCalib2 0
#define zCalib2 0

#define xCalib3 0
#define yCalib3 0
#define zCalib3 0

//----------------------------------------------------------------
const int samples = 10;

int xRaw1 = 0, yRaw1 = 0, zRaw1 = 0;
int xRaw2 = 0, yRaw2 = 0, zRaw2 = 0;
int xRaw3 = 0, yRaw3 = 0, zRaw3 = 0;

//----------------------

#define readSumS1               \
  xRaw1 += analogRead(xPin1); \
  yRaw1 += analogRead(yPin1); \
  zRaw1 += analogRead(zPin1)

#define readSumS2               \
  xRaw2 += analogRead(xPin2); \
  yRaw2 += analogRead(yPin2); \
  zRaw2 += analogRead(zPin2)

#define readSumS3               \
  xRaw3 += analogRead(xPin3); \
  yRaw3 += analogRead(yPin3); \
  zRaw3 += analogRead(zPin3)

#define readSumSensor \
  readSumS1;        \
  readSumS2;        \
  readSumS3

//----------------------

#define agvS1         \
  xRaw1 /= samples; \
  yRaw1 /= samples; \
  zRaw1 /= samples

#define agvS2         \
  xRaw2 /= samples; \
  yRaw2 /= samples; \
  zRaw2 /= samples

#define agvS3         \
  xRaw3 /= samples; \
  yRaw3 /= samples; \
  zRaw3 /= samples

#define agvSensor \
  agvS1;        \
  agvS2;        \
  agvS3

//----------------------

#define readSensor                    \
  for (int i = 0; i < samples; i++) \
    readSumSensor;                \
  agvSensor

//----------------------------------------------------------------
#include <SimpleKalmanFilter.h>

#define initKlfParameter 1, 1, 0.1

#define initKlfS1                               \
  SimpleKalmanFilter klfX1(initKlfParameter); \
  SimpleKalmanFilter klfY1(initKlfParameter); \
  SimpleKalmanFilter klfZ1(initKlfParameter)

#define initKlfS2                               \
  SimpleKalmanFilter klfX2(initKlfParameter); \
  SimpleKalmanFilter klfY2(initKlfParameter); \
  SimpleKalmanFilter klfZ2(initKlfParameter)

#define initKlfS3                               \
  SimpleKalmanFilter klfX3(initKlfParameter); \
  SimpleKalmanFilter klfY3(initKlfParameter); \
  SimpleKalmanFilter klfZ3(initKlfParameter)

#define initKlfSensor \
  initKlfS1;        \
  initKlfS2;        \
  initKlfS3

//----------------------------------------------------------------

#define printS1                    \
  Serial.print(xRaw1 - xCalib1); \
  Serial.print(",");             \
  Serial.print(yRaw1 - yCalib1); \
  Serial.print(",");             \
  Serial.print(zRaw1 - zCalib1); \
  Serial.print(",")

#define printS2                    \
  Serial.print(xRaw2 - xCalib2); \
  Serial.print(",");             \
  Serial.print(yRaw2 - yCalib2); \
  Serial.print(",");             \
  Serial.print(zRaw2 - zCalib2); \
  Serial.print(",")

#define printS3                    \
  Serial.print(xRaw3 - xCalib3); \
  Serial.print(",");             \
  Serial.print(yRaw3 - yCalib3); \
  Serial.print(",");             \
  Serial.print(zRaw3 - zCalib3); \
  Serial.print(",")

#define numMau 10025 + 1

#define printSensor      \
  printS1;             \
  printS2;             \
  printS3;             \
  //  if (count >= numMau) \
  //    while (1)        \
  //      ;            \
  //  else                 \
  //    count++

//----------------------------------------------------------------

#define klfS1                            \
  xRaw1 = klfX1.updateEstimate(xRaw1); \
  yRaw1 = klfY1.updateEstimate(yRaw1); \
  zRaw1 = klfZ1.updateEstimate(zRaw1)

#define klfS2                            \
  xRaw2 = klfX2.updateEstimate(xRaw2); \
  yRaw2 = klfY2.updateEstimate(yRaw2); \
  zRaw2 = klfZ2.updateEstimate(zRaw2)

#define klfS3                            \
  xRaw3 = klfX3.updateEstimate(xRaw3); \
  yRaw3 = klfY3.updateEstimate(yRaw3); \
  zRaw3 = klfZ3.updateEstimate(zRaw3)

#define klfSensor \
  klfS1;        \
  klfS2;        \
  klfS3

//----------------------------------------------------------------
