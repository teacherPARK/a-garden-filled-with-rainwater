#include <ESP8266WiFi.h>
 
const char* ssid     = "dgedu-learning"; 
const char* password = "1907029089"; 
 
WiFiServer server(80);
 
void setup() {
  pinMode(A0,INPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println();
 
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
 
  server.begin();
  Serial.println("Server started");
 
  Serial.println(WiFi.localIP());
}
 
void loop() {
  int rainwater = analogRead(A0); 
  delay(50);
  Serial.println(rainwater);
  WiFiClient client = server.available();
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println("Refresh: 1");
  client.println();
  client.println("<!DOCTYPE html>");
  client.println("<html xmlns='http://www.w3.org/1999/xhtml'>");
  client.println("<head>\n<meta http-equiv='Content-Type' content='text/html; charset=utf-8' />");
  
  client.println("2022 주니어 소프트웨어 창작대회 뽀롱뽀롱 뽀로로팀");
  client.println("</head>\n<body>");
  client.println("<center>");
  client.println("<br>");
  client.println("<H1>빗물 저금통에 남은 빗물</H1>");
 
 
  if (rainwater < 10 ) {                      
    client.print("<H2><span style=color:red><b>빗물 부족!</H2>");  
    client.println("<br>");
    client.println("<br>");
    client.println("<H3><span style=color:red>남아 있는 빗물의 양</H3>");
    client.println(rainwater);
      
  }
  else if (rainwater < 500 )          
  {
    client.print("<H2><span style=color:orange><b>빗물 보충 필요</H2>");       
    client.println("<br>");
    client.println("<br>");
    client.println("<H3><span style=color:orange>남아 있는 빗물의 양</H3>");
    client.println(rainwater);
}
  else                                        
  {
    client.print("<H2><span style=color:green><b>빗물 충분</H2>");       
    client.println("<br>");
    client.println("<br>");
    client.println("<H3><span style=color:green>남아 있는 빗물의 양</H3>");
    client.println(rainwater);
}
  client.println("<br>");
  client.println("<br>");
 
  client.println("<H1> 빗물 모아 텃밭 </H1>"); // 페이지 내용 설정
  client.println("<pre>");
  client.print("</body>\n</html>");
 
}
