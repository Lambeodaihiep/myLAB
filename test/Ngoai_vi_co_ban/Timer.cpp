// Timer hay bộ định thời là một ngoại vi của vi điều khiển có chức năng đếm xung, từ đó có thể cài đặt được thời gian nhất định.
// Time = T(clock) x N (số lần đêm)
// T là chu kỳ của 1 xung cấp vào timer
// N là số lần đếm của timer
// Trong vi điều khiển Timer thường được sử dụng như bộ hẹn giờ, lặp lại một hành động nhất định khi tới đúng thời điểm.
// Hàm delay cực kì phổ biến và rất hay được sử dụng trong các chương trình nhúng. Bằng cách truyền vào 1 tham số kiểu int, tương ứng với số mili giây (ms) mà MCU sẽ chờ trong đó.
// Nhược điểm là chương trình sẽ không thể xử lý các tác vụ khác khi đang delay, dẫn tới chậm, mất dữ liệu ...

// Hàm millis() có nhiệm vụ trả về một số unsigned long – là thời gian (tính theo mili giây) kể từ lúc mạch Arduino bắt đầu chương trình.
// Nó sẽ tràn số và quay lại 0 từ ban đầu.
// Chương trình vẫn có thể xử lý được các tác vụ khác khi đang chờ
// Thiếu tính chính xác, nếu vi điều khiển phải xử lý một tác vụ dài hơn thời gian delay,
// chúng ta sẽ không thể chạy các tác vụ đúng thời điểm, mà phải cho vi điều khiển xử lý hết rồi mới chạy tới.

// Vậy để khắc phục 2 nhược điểm của cách trên chúng ta có Ngắt Timer.

// Ưu điểm: Với ngắt Timer chúng ta có thể xử lý được các tác vụ trong chương trình chính mà vẫn có thể xử lý các tác vụ khác một cách lập tức khi tới thời gian.
// Nhược điểm: Nó có thể bị xung đột với các loại ngắt khác nếu không biết cách xử lý tốt, gây nên treo chương trình…

// Bật tắt đèn sử dụng ngắt Timer
#include <Arduino.h>

const int button = 4; 
const int ledPin1 = 26; // chân led
const int ledPin2 = 27;
int ledState = HIGH;
 
hw_timer_t* timer0 = NULL; //khơi tạo timer
hw_timer_t* timer1 = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED; //biến này có tác dụng chống sự xung đột giữa các CPU và chương trình chính khi hoạt động.
 
// hàm xử lý ngắt
void IRAM_ATTR blinkLED() {   
  portENTER_CRITICAL_ISR(&timerMux); //vào chế độ tránh xung đột
  digitalWrite(ledPin1, !ledState); 
  ledState = !ledState;
  Serial.println("Doi trang thai");
  portEXIT_CRITICAL_ISR(&timerMux); // thoát 
}

void ARDUINO_ISR_ATTR resetModule() {
  ets_printf("reboot\n");
  esp_restart();
}

void setup() {
  delay(2000);
  Serial.begin(115200);
  pinMode(ledPin1,OUTPUT);
  pinMode(ledPin2,OUTPUT);
  pinMode(button, INPUT); 
 
  //khởi tạo timer với chu kì 1us vì thạch anh của ESP32 chạy 8MHz
  timer0 = timerBegin(0, 80, true);
  timer1 = timerBegin(1, 80, true);
  //khởi tạo hàm xử lý ngắt ngắt cho Timer
  timerAttachInterrupt(timer0, &blinkLED, true);
  timerAttachInterrupt(timer1, &resetModule, true);  //attach callback
  //khởi tạo thời gian ngắt cho timer
  timerAlarmWrite(timer0, 1000000, true);
  timerAlarmWrite(timer1, 3000000, false);
  //bắt đầu chạy timer
  timerAlarmEnable(timer0);
  timerAlarmEnable(timer1);
}
  
void loop() {
  Serial.println("running main loop");

  timerWrite(timer1, 0); //reset timer (feed watchdog)
  long loopTime = millis();
  //while button is pressed, delay up to 3 seconds to trigger the timer
  while (!digitalRead(button)) {
    Serial.println("button pressed");
    delay(500);
  }
  delay(1000); //simulate work
  loopTime = millis() - loopTime;
  
  Serial.print("loop time is = ");
  Serial.println(loopTime); //should be under 3000
} 