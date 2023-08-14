#include <ESP8266WiFi.h>                                               
#include <FirebaseArduino.h>
#include <Servo.h>

Servo servo;

#define FIREBASE_HOST "fish-feed-4980e-default-rtdb.firebaseio.com"             
#define FIREBASE_AUTH "rbiLoougEfH7Bz3Fr7itR3iFsvssjK5M9DNd2CB4"      
//rbiLoougEfH7Bz3Fr7itR3iFsvssjK5M9DNd2CB4
#define WIFI_SSID "Kiyoo"                                          
#define WIFI_PASSWORD "d59i9xkv" 

int i;                                 
 
                                                 
String ser1,ser2,itv; 
int pnum,inum;                                                   
void setup() 
{
  servo.attach(5); //D1
  servo.write(0);

  delay(2000);
  Serial.begin(9600);
  delay(1000);   
  //pinMode(servo_pin,OUTPUT); 
  //pinMode(led, OUTPUT);                 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                               
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);  
  Serial.println(Firebase.error());               
  Firebase.setString("Fish_feeder/Servo1","0");
  Firebase.setString("Fish_feeder/Servo2","0");
  Firebase.setString("Fish_feeder/Interval","off");
}
 
void loop() 
{
  
  Firebase.setString("Fish_feeder/Servo1","0");
  Firebase.setString("Fish_feeder/Servo2","0");
  Firebase.setString("Fish_feeder/Interval","off");
  ser1=Firebase.getString("Fish_feeder/Servo1");
  ser1.replace("\"","");
  
  ser2=Firebase.getString("Fish_feeder/Servo2");
  ser2.replace("\"","");
  
  
  pnum=ser1.toInt();
  inum=ser2.toInt();
  

  if(pnum>0)
  {
  i=0;
  Serial.println(pnum);
  while(i<pnum)
  {
    servo.write(90);

    delay(500);

    servo.write(0);

    delay(400);
    i=i+1;
  }
  servo.write(90);
  }
  else if(inum>0)
  {
    Serial.println(inum);
    while(itv!="Stop")
    {
    itv=Firebase.getString("Fish_feeder/Interval");
    itv.replace("\"","");

    delay(inum*60*1000);
    servo.write(90);

    delay(500);

    servo.write(0);

    delay(400);
   
    }
    servo.write(90);
  }
  
}