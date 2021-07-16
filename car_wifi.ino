#include <ESP8266WiFi.h>
//前左
//const int D1;
//= 5;
//const int D3;
//= 0;
//前右
//const int D2;
//= 4;
//const int D4;
//= 2;
//后左
//const int D5;
//= 14;
//const int D6;
//= 12;
//后右
//const int D7;
//= 13;
//const int D8;
//= 15;

//设置WiFi名称和密码  const:常量
const char *ssid = "cxcx";
const char *psw  = "12345678";
//定义ch（字符）存储手机发送的值
char ch;   
//定义端口，启动tcp服务
const int LocalPort = 666;
WiFiServer server(LocalPort);

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft_AP...");
  if(WiFi.softAP(ssid, psw))
    Serial.print("you can try to connect with cxcx");
  else
    Serial.print("Failed");
  Serial.println();
  server.begin();
  Serial.printf("APIP is %s", WiFi.softAPIP().toString().c_str());
  Serial.println();
  Serial.printf("端口 is：%d", LocalPort);
  /*引脚初始化*/
  gpio_init();
}
void gpio_init()
{
  pinMode(D1,OUTPUT);
  digitalWrite(D1,LOW);
  pinMode(D3,OUTPUT);
  digitalWrite(D3,LOW);

  pinMode(D2,OUTPUT);
  digitalWrite(D2,LOW);
  pinMode(D4,OUTPUT);
  digitalWrite(D4,LOW);

  pinMode(D5,OUTPUT);
  digitalWrite(D5,LOW);
  pinMode(D6,OUTPUT);
  digitalWrite(D6,LOW);

  pinMode(D7,OUTPUT);
  digitalWrite(D7,LOW);
  pinMode(D8,OUTPUT);
  digitalWrite(D8,LOW);
  }
void loop()
{
  WiFiClient client = server.available();
  if(client)
  {
    client.write("Hello！Thank you for connecting with me.");
    while(client.connected())
    {
      if(client.available())
      {
        ch = client.read();
        //client.write("已收到请稍等\n");
        Serial.println(ch);
        if (ch=='a')             //前进
          {
            digitalWrite(D1,LOW);
            digitalWrite(D3,HIGH);
            digitalWrite(D2,LOW);
            digitalWrite(D4,HIGH);

            digitalWrite(D5,LOW);
            digitalWrite(D6,HIGH);
            digitalWrite(D7,LOW);
            digitalWrite(D8,HIGH);
            client.write("前进");
          }
        else if (ch=='b')        //后退
          {
            digitalWrite(D1,HIGH);
            digitalWrite(D3,LOW);
            digitalWrite(D2,HIGH);
            digitalWrite(D4,LOW);

            digitalWrite(D5,HIGH);
            digitalWrite(D6,LOW);
            digitalWrite(D7,HIGH);
            digitalWrite(D8,LOW);
            client.write("后退");
          }
        else if (ch=='c')        //左转
          {
            digitalWrite(D1,HIGH);
            digitalWrite(D3,LOW);
            digitalWrite(D2,LOW);
            digitalWrite(D4,HIGH);

            digitalWrite(D5,HIGH);
            digitalWrite(D6,LOW);
            digitalWrite(D7,LOW);
            digitalWrite(D8,HIGH);
            client.write("左转");
          }
        else if (ch=='d')        //右转
          {
            digitalWrite(D1,LOW);
            digitalWrite(D3,HIGH);
            digitalWrite(D2,HIGH);
            digitalWrite(D4,LOW);

            digitalWrite(D5,LOW);
            digitalWrite(D6,HIGH);
            digitalWrite(D7,HIGH);
            digitalWrite(D8,LOW);
            client.write("右转");
          }
        else if (ch=='t')        //停止
          {
            digitalWrite(D1,LOW);
            digitalWrite(D3,LOW);
            digitalWrite(D2,LOW);
            digitalWrite(D4,LOW);
            digitalWrite(D5,LOW);
            digitalWrite(D6,LOW);
            digitalWrite(D7,LOW);
            digitalWrite(D8,LOW);
            client.write("停止");
          }
        else
          {
            client.write("没有此指令");
          }
      }
    }  
  }
  client.stop(); 
}
