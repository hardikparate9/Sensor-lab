#define BLYNK_TEMPLATE_ID "TMPL3q4CfoFaz"
#define BLYNK_TEMPLATE_NAME "car parking"
#define BLYNK_AUTH_TOKEN "qaWEn7qMnD1-JhO2hOyxBPACHLQNPCW9"
//#include <version.h>
#include <Servo.h> //includes the servo library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <BlynkSimpleEsp8266.h> 
#include <version.h>
#include <ESP8266Wifi.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
Servo myservo;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "OnePlus 8";
char pass[] = "qwerty123";

BlynkTimer timer;

#define ir_enter 2
#define ir_back  4

#define ir_car1 5
#define ir_car2 6
#define ir_car3 7
#define ir_car4 8
#define ir_car5 9
#define ir_car6 10

int S1=0, S2=0, S3=0, S4=0, S5=0, S6=0;
int flag1=0, flag2=0; 
int slot = 6;  

void setup(){
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass);
//  timer.setInterval(1000);
  pinMode(ir_car1, INPUT);
  pinMode(ir_car2, INPUT);
  pinMode(ir_car3, INPUT);
  pinMode(ir_car4, INPUT);
  pinMode(ir_car5, INPUT);
  pinMode(ir_car6, INPUT);

  pinMode(ir_enter, INPUT);
  pinMode(ir_back, INPUT);
    
  myservo.attach(3);
  myservo.write(90);

  lcd.begin(20, 4);  
  lcd.setCursor (0,1);
  lcd.print("    Car  parking  ");
  lcd.setCursor (0,2);
  lcd.print("       System     ");
  delay (2000);
  lcd.clear();   

//  Read_Sensor();

  int total = S1+S2+S3+S4+S5+S6;
  slot = slot-total; 
}


void loop(){
  Blynk.run();
  timer.run();
 // Read_Sensor();
  int total = S1+S2+S3+S4+S5+S6;
  slot = (6-total); 

  lcd.setCursor (0,0);
  lcd.print("   Have Slot: "); 
  lcd.print(slot);
  lcd.print("    ");  

  lcd.setCursor (0,1);
  if(S1==1){lcd.print("S1:Fill "); Blynk.virtualWrite(V0, S1);}
  else{lcd.print("S1:Empty"); Blynk.virtualWrite(V0, S1);}

  lcd.setCursor (10,1);
  if(S2==1){lcd.print("S2:Fill ");Blynk.virtualWrite(V1, S2);}
  else{lcd.print("S2:Empty");Blynk.virtualWrite(V1, S2);}

  lcd.setCursor (0,2);
  if(S3==1){lcd.print("S3:Fill ");Blynk.virtualWrite(V2, S3);}
  else{lcd.print("S3:Empty");Blynk.virtualWrite(V1, S3);}

  lcd.setCursor (10,2);
  if(S4==1){lcd.print("S4:Fill ");Blynk.virtualWrite(V3, S4);}
  else{lcd.print("S4:Empty");Blynk.virtualWrite(V3, S4);}

  lcd.setCursor (0,3);
  if(S5==1){lcd.print("S5:Fill  ");Blynk.virtualWrite(V4, S5);}
  else{lcd.print("S5:Empty");Blynk.virtualWrite(V4, S5);}

  lcd.setCursor (10,3);
  if(S6==1){lcd.print("S6:Fill  ");Blynk.virtualWrite(V5, S6);}
  else{lcd.print("S6:Empty");Blynk.virtualWrite(V5, S6);}    

  if(digitalRead(ir_enter) == 0 && flag1==0){
    if(slot>0){
      flag1=1;
      if(flag2==0){
        myservo.write(180);
        slot = slot-1;
      }
    }
    else{
      lcd.setCursor (0,0);
      lcd.print(" Sorry Parking Full ");  
      delay(1500);
    }   
    Blynk.virtualWrite(V6, slot);
  }

  if(digitalRead(ir_back) == 0 && flag2==0){
    flag2=1;
    if(flag1==0){
      myservo.write(180);
      slot = slot+1;
    }
    Blynk.virtualWrite(V6, slot);
  }

  if(flag1==1 && flag2==1){
    delay (1000);
    myservo.write(90);
    flag1=0, flag2=0;
  }

  delay(1);
}
