//-------------------------------- STEPPER MOTOR --------------------------------
#define motorInterfaceType 1 // mode 1 thư viện accel

#define N 1 // Số lượng động cơ bước

//------------ STEP 1 ------------
#define stepL1 2    // dây động cơ bên trái
#define dirL1 3     // dây động cơ bên trái
#define swLimit1 9 // dây số 9

const int step[N] = {stepL1};        // list chân step
const int dir[N] = {dirL1};           // list chân dir
const int swLimit[N] = {swLimit1}; // list công tắc hành trình
long long int accel[N];                                // Gia tốc của động cơ
long long int degToGo[N];                             // Số góc nhập vào

//#define numLine 1
//#define numDeg 4*2*2
//long degGo[numDeg] = {
//8000,4000, -8000, -4000 ,
//4000,8000, -4000, -8000 ,
//8000,4000, -8000, -4000 ,
//4000,8000, -4000, -8000 
//}; //endDEG

#define numDeg 2
int deg =360*5+60;
long long int degGo[numDeg] = {
deg,-deg,
}; //endDEG


long index = 0; //chỉ số chạy mảng nhập sẵn


long long int stepToGo[N];                            // Số bước cần di chuyển

#define en 8 // chân en động cơ, LOW chạy HIGH tắt

//------------ Phần cứng ------------
#define microStep 32   // Vi bước sử dụng
#define ratioPuley (37.0 / 20.0) // Tỉ số truyền đai pulley

//------------ Tốc độ ------------

#define SPEED_ 2400000
#define ACCEL_ 3000

//#define MAXSPEED int(SPEED_ * microStep) // Vận tốc lớn nhất động cơ có thể đạt được
//#define MAXACCEL int(ACCEL_ * microStep)  // Gia tốc lớn nhất động cơ có thể đạt được

#define MAXSPEED 2000000
#define MAXACCEL 25000
