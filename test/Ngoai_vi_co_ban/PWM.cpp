#include <Arduino.h>
 
const int ledPin = 16;  // chọn chân 16 xuất tín hiệu
// cài đặt PWM
const int freq = 5000;  // tần số xung
const int PwmChannel = 0; // kênh PWM - có 16 kênh từ 0 đến 15
const int resolution = 8; // độ phân giải 8 bit (1 - 16)
// ledc : led control
void setup(){
    // setup kênh pwm
    ledcSetup(PwmChannel, freq, resolution);
    // xuất pwm ra chân 16
    ledcAttachPin(ledPin, PwmChannel);
}
void loop(){
    // Sáng dần
    for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
        ledcWrite(PwmChannel, dutyCycle);
        delay(15);
    }
    // tắt dần
    for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
        ledcWrite(PwmChannel, dutyCycle);   
        delay(15);
    }
}