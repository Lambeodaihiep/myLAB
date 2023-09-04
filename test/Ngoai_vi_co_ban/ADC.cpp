#include <Arduino.h>

// ADC : chuyển đổi tín hiệu analog dưới dạng điện áp hoặc dòng điện thành các giá trị số đại diện cho cường độ điện áp hay tín hiệu đó
// analogReadResolution(resolution): thiết lập độ phân giải. Giá trị từ 9 (0 – 511) đến 12 bit (0 – 4095). Mặc định là độ phân giải 12 bit.
// analogSetWidth(width): thiết lập độ phân giải. Giá trị từ 9 (0 – 511) đến 12 bit (0 – 4095). Mặc định là độ phân giải 12 bit
// analogSetCycles(cycles): thiết lập số chu kỳ cho một lần lấy mẫu. Mặc định là 8. Phạm vi: 1 đến 255.
// analogSetSamples(samples): đặt số lượng mẫu trong một lần lấy mẫu. Mặc định là 1 mẫu. Nó có tác dụng làm tăng độ nhạy.
// analogSetClockDiv(attenuation): đặt bộ chia cho clock ADC. Mặc định là 1. Phạm vi: 1 đến 255.
// adcAttachPin(pin): Gắn một chân vào chế độ ADC (cũng xóa bất kỳ chế độ tương tự nào khác được bật trên chân đó). Trả về kết quả TRUE hoặc FALSE.
// adcStart(pin): bắt đầu chuyển đổi ADC trên chân
// adcBusy(pin): Kiểm tra xem chân có đang bận chuyển đổi không (trả về TRUE hoặc FALSE).
// resultadcEnd(pin): Nhận kết quả của chuyển đổi: trả về số nguyên 16 bit.

void setup() {
    Serial.begin(115200);
    pinMode(2,INPUT);
}

void loop() {

    analogReadResolution(11); //thiết lập độ phân giải. Giá trị từ 9 (0 – 511) đến 12 bit (0 – 4095). Mặc định là độ phân giải 12 bit.
    Serial.println(analogRead(2));
    delay(500);
}