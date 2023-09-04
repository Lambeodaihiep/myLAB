//Trong ESP32 có 9 chân Touch pin
// T0 (GPIO 4)
// T1 (GPIO 0)
// T2 (GPIO 2)
// T3 (GPIO 15)
// T4 (GPIO 13)
// T5 (GPIO 12)
// T6 (GPIO 14)
// T7 (GPIO 27)
// T8 (GPIO 33)
// T9 (GPIO 32)
#include <Arduino.h>
 
// chọn chân touch
const int touchPin = 4; 
const int ledPin = 16;
 
// Giới hạn touch (độ nhạy)
const int threshold = 20;
// Giá trị touch
int touchValue;
 
void setup(){
    Serial.begin(9600);
    delay(1000);
    // khởi tạo led là output
    pinMode (ledPin, OUTPUT);
}
 
void loop(){
    // đọc giá trị touch
    touchValue = touchRead(touchPin);
    Serial.print(touchValue);
    //nếu giá trị nhỏ hơn giới hạn
    if(touchValue < threshold){
        // bật led
        digitalWrite(ledPin, HIGH);
        //Serial.println(" - LED on");
    }
    else{
        // nếu lớn hơn hoặc bằng thì tắt led
        digitalWrite(ledPin, LOW);
        //Serial.println(" - LED off");
    }
    delay(500);
}