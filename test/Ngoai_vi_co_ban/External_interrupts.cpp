// Ngắt: Chương trình sẽ bị thoát ra khỏi quá trình tuần tự, xử lý xong các lệnh trong ngắt, sau đó mới quay lại xử lý tiếp trong loop
// Ngắt là một công việc được ưu tiên làm trước, khi xử lý xong mới được làm các việc khác.
// Các sự kiện ngắt có thể đến từ nhiều nguồn khác nhau như: ADC, IO, UART. TIMER…
// Mọi chân input trên esp32 đều được cài đặt để sử dụng ngắt ngoài
// Mode:
// LOW	     Interrupt được kích hoạt khi chân ở mức LOW
// HIGH	     Interrupt được kích hoạt khi chân ở mức HIGH
// CHANGE	 Interrupt được kích hoạt khi chân thay đổi mức, từ HIGH sang LOW, hoặc LOW sang HIGH
// FALLING	 Interrupt được kích hoạt khi chân thay đổi mức, từ HIGH sang LOW
// RISING	 Interrupt được kích hoạt khi chân thay đổi mức, từ LOW sang HIGH
// attachInterrupt(GPIOPin, ISR, Mode); cài đặt ngắt ngoài cho chân GPIOin, ISR là hàm được gọi khi có ngắt
// detachInterrupt(GPIOin); xóa cấu hình ngắt trên chân GPIOin
#include <Arduino.h>
 
const int led = 17;
const int button = 16;
bool ledstates = 0;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED; //biến này có tác dụng chống sự xung đột giữa các CPU và chương trình chính khi hoạt động.
 
void IRAM_ATTR buttonPush() {
    portENTER_CRITICAL_ISR(&mux);//Phần quan trọng cần được bảo vệ khỏi mọi truy cập đồng thời để thay đổi nó
    Serial.println("Button Pushed!!!");
    digitalWrite(led, ~ledstates);
    portEXIT_CRITICAL_ISR(&mux);//Cho phép tiếp tục chạy các task khác
}
void setup() {
    pinMode(button, INPUT_PULLUP);
    
    // cài đặt ngắt vào chân button, kiểu ngắt falling (xung xuống), hàm gọi khi bấm nút
    attachInterrupt(digitalPinToInterrupt(button), buttonPush, FALLING);
    
    // chọn led là đầu ra
    pinMode(led, OUTPUT);
    //ghi giá trị ban đầu
    digitalWrite(led, ledstates);
}
void loop() {
  // do nothing
}