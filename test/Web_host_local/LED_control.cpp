#include <Arduino.h>
//khai báo thư viện để kết nối wifi cho esp32 webserver
#include <WiFi.h>
#include <string>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <SPI.h>
//khai báo chân sử dụng led 
const int led1 = 26;
const int led2 = 27;
 
const char* ssid ="Dao Nam";
const char* password = "18052001";
//Tạo một web server tại cổng 80 - cổng mặc định cho esp32 webserver
WiFiServer webServer(80);

String led1Status = "Tat";
String led2Status = "Tat";
 
String header;
 
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
 
void setup() {
  Serial.begin(115200);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  // Set outputs to LOW
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
 
  Serial.print("Connecting to wifi ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
   
  //khởi tạo webserver
  webServer.begin();
}
 
void loop() {
  WiFiClient webClient = webServer.available(); // nếu có client kết nối với esp32 webserver
 
  if(webClient)
  {
    //khoi tao gia tri ban dau cho time
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New web Client");
    //biến lưu giá trị response
    String currentLine = "";
    //nếu có client connect và không quá thời gian time out
    while(webClient.connected() && currentTime - previousTime <= timeoutTime)
    {
      //đọc giá trị timer tại thời điểm hiện tại
      currentTime = millis();
      //nếu client còn kết nối
      if(webClient.available())
      {
        //đọc giá trị truyền từ client theo từng byte kiểu char
        char c = webClient.read();
        Serial.write(c);
        header += c; // lưu giá trị vào Header
        if(c == '\n') //Nếu đọc được kí tự xuống dòng (hết chuỗi truyền tới)
        {
          if (currentLine.length() == 0) 
          {
            //esp32 webserver response
            // HTTP headers luôn luôn bắt đầu với code HTTP (ví d HTTP/1.1 200 OK)
            webClient.println("HTTP/1.1 200 OK");
            webClient.println("Content-type:text/html"); // sau đó là kiểu nội dụng mà client gửi tới, ví dụ này là html
            webClient.println("Connection: close"); // kiểu kết nối ở đây là close. Nghĩa là không giữ kết nối sau khi nhận bản tin
            webClient.println();
 
            // nếu trong file header có giá trị
            if (header.indexOf("GET /led1/on") >= 0) 
            {
              Serial.println("Led1 on");
              led1Status = "Bat";
              digitalWrite(led1, HIGH);
            } 
            else if (header.indexOf("GET /led1/off") >= 0) 
            {
              Serial.println("Led1 off");
              led1Status = "Tat";
              digitalWrite(led1, LOW);
            } 
            else if (header.indexOf("GET /led2/on") >= 0) 
            {
              Serial.println("Led2 on");
              led2Status = "Bat";
              digitalWrite(led2, HIGH);
            } 
            else if (header.indexOf("GET /led2/off") >= 0) 
            {
              Serial.println("Led2 off");
              led2Status = "Tat";
              digitalWrite(led2, LOW);
            }
            // Response trang HTML của esp32 webserver
            webClient.println("<!DOCTYPE html><html>");
            webClient.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            //thêm font-awesome 
            webClient.println("<link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\">");
            // code CSS cho web
            //css cho toan bo trang 
            //webClient.println("<img src="data:image/gif;base64);
            webClient.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            //css cho nut nhan
            webClient.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            webClient.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            webClient.println(".button2 {background-color: #5e0101;}</style></head>");
            // Web Page Heading H1 with CSS
            webClient.println("<body><h1 style=\"color:Tomato;\">Test ESP32 Station Web Server</h1>");

            // Web Page Heading H2
            webClient.println("<h2 style=\"color:Tomato;\">Using Sever-Sent Events</h2>");

            // Web Page Heading H3
            webClient.println("<h3 style=\"color:#077a39;\"><a href=\"https://www.youtube.com\">HELLO</a></h3>");
            webClient.println("<i class=\"fa fa-home\" aria-hidden=\"true\"></i>");

            // Display current state, and ON/OFF buttons for Led1
            webClient.println("<p>Trang thai Led1: " + led1Status + "</p>");
            // If the Led1Status is off, it displays the ON button       
            if (led1Status=="Tat") 
            {
              //khởi tạo một nút nhấn có đường dẫn đích là /led1/on
              webClient.println("<p><a href=\"/led1/on\"><button class=\"button\">Bat den</button></a></p>");
            } 
            else
            {
              //khởi tạo một nút nhấn có đường dẫn đích là /led1/off
              webClient.println("<p><a href=\"/led1/off\"><button class=\"button button2\">Tat den</button></a></p>");
            } 
                
            // Display current state, and ON/OFF buttons for Led2
            webClient.println("<p>Trang thai Led2: " + led2Status + "</p>");
            // If the led2 is off, it displays the ON button       
            if (led2Status=="Tat") 
            {
              //khởi tạo một nút nhấn có đường dẫn đích là /led2/on
              webClient.println("<p><a href=\"/led2/on\"><button class=\"button\">Bat den</button></a></p>");
            } 
            else
            {
              //khởi tạo một nút nhấn có đường dẫn đích là /led2/on
              webClient.println("<p><a href=\"/led2/off\"><button class=\"button button2\">Tat den</button></a></p>");
            }
            webClient.println("</body></html>");
             
            // The HTTP response ends with another blank line
            webClient.println();
            // Break out of the while loop
            break;
          }
          else
          {
            currentLine = "";
          }
        }
        else if (c != '\r')   //nếu giá trị gửi tới khác xuống duòng
        {
          currentLine += c;     //lưu giá trị vào biến
        }
      }
    }
    // Xoá header để sử dụng cho lần tới
    header = "";
    // ngắt kết nối với client trên esp32 webserver
    webClient.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}