//-------------------------------- STEPPER MOTOR --------------------------------
#define motorInterfaceType 1 // mode 1 thư viện accel

#define N 2 // Số lượng động cơ bước

//------------ STEP 1 ------------
#define stepL1 2    // dây động cơ bên trái
#define dirL1 3     // dây động cơ bên trái
#define swLimit1 9 // dây số 9

//------------ STEP 2 ------------
#define stepL2 4    // dây động cơ bên phải
#define dirL2 5     // dây động cơ bên phải
#define swLimit2 10 // dây số 8

const int step[N] = {stepL1, stepL2};        // list chân step
const int dir[N] = {dirL1, dirL2};           // list chân dir
const int swLimit[N] = {swLimit1, swLimit2}; // list công tắc hành trình
long long int accel[N];                                // Gia tốc của động cơ
long degToGo[N];                             // Số góc nhập vào

//#define numLine 1
//#define numDeg 4*2*2
//long degGo[numDeg] = {
//8000,4000, -8000, -4000 ,
//4000,8000, -4000, -8000 ,
//8000,4000, -8000, -4000 ,
//4000,8000, -4000, -8000 
//}; //endDEG

#define numDeg 5*2*2
long degGo[numDeg] = {
90,90, -90, -90,
90,90, -90, -90,
90,90, -90, -90,
90,90, -90, -90,
90,90, -90, -90
}; //endDEG


long index = 0; //chỉ số chạy mảng nhập sẵn


long stepToGo[N];                            // Số bước cần di chuyển
#define degHome1 -98* microStep * ratioPuley / 1.8                           // số góc từ công tắc hành trình về giữa
#define degHome2 -94* microStep * ratioPuley / 1.8                           // số góc từ công tắc hành trình về giữa

#define en 8 // chân en động cơ, LOW chạy HIGH tắt

//------------ Phần cứng ------------
#define microStep 32   // Vi bước sử dụng
#define ratioPuley 1 // Tỉ số truyền đai pulley

//------------ Tốc độ ------------

#define SPEED_ 24000
#define ACCEL_ 500

//#define MAXSPEED int(SPEED_ * microStep) // Vận tốc lớn nhất động cơ có thể đạt được
//#define MAXACCEL int(ACCEL_ * microStep)  // Gia tốc lớn nhất động cơ có thể đạt được

#define MAXSPEED 2000000
#define MAXACCEL 10000

//-------------------------------- RC SERVO --------------------------------

//------------ SERVO ------------
#define pinServo 9 // dây số 7

#define posMax 180 // vị trí cao nhất L3
#define posMin 0   // vị trí thấp nhất L3

int posWrite; // vị trí hoạt đông của L3
//------------ BIẾN TRỞ ------------
#define pinRes A0 // dây số 6

#define resMin 290 // giá trị min ổn định biến trở
#define resMax 500 // giá trị max ổn định biến trở
