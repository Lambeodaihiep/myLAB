//DAC là một ngoại vi rất mạnh nếu bạn làm các ứng dụng liên quan tới âm thanh (audio).
//DAC thường được sử dụng trong các mạch Audio. Trong đó nó nhiệm vụ thu thập thông tin âm thanh số và 
//  chuyển đối nó sang một tín hiệu tương tự. Sau đó, tín hiệu đó sẽ được truyền sang bộ khuếch đại âm 
//  thanh rồi mới đến tai nghe hoặc loa để bạn có thể nghe được.
// DAC trên ESP32 sẽ mặc định có độ phân giải là 8bit và đây cũng là độ phân giải lớn nhất.
#include <Arduino.h>

#define DAC1 25
// khởi tạo giá trị DAC
int Value = 0; //255= 3.3V 128=1.65V
void setup() {
    Serial.begin(115200);
}
 
void loop() { 
    //Khởi tạo tín hiệu hình sin
    // tăng dần điện áp
    for(int Value = 0; Value <= 255; Value++){   
        //ghi giá trị điện áp lên chân DAC
        dacWrite(DAC1, Value);
        delay(15);
    }
    // giảm dần điện áp
    for(int Value = 255; Value >= 0; Value--){
        //ghi giá trị điện áp lên chân DAC
        dacWrite(DAC1, Value); 
    }
}

