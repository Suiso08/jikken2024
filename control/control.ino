#include <SoftwareSerial.h>
 
SoftwareSerial btport(10, 11);
int jumpflg = 0;
int squatflg = 0;
int GCD = 0;

void setup() {
  Serial.begin(9600); 
  btport.begin(38400);
}

void loop() {
// 地球の重力である1Gの加速度(m/s^2)
  float ms2 = 9.80665;
  
  // 電源電圧5V時のオフセット電圧(0G = 2.5V = 2500mV)
  float offset_voltage = 2500.0;
 
  // XYZの電圧(mV)を取得する
  float x =  (analogRead(A0) / 1024.0) * 5.0 * 1000;
  float y =  (analogRead(A1) / 1024.0) * 5.0 * 1000;
  float z =  (analogRead(A2) / 1024.0) * 5.0 * 1000;
 
  // XYZからオフセット電圧を引いた電圧を求める
  x = x - offset_voltage;
  y = y - offset_voltage;
  z = z - offset_voltage;
 
  // XYZから重力を求める
  float xg = x / 1000.0;
  float yg = y / 1000.0;
  float zg = z / 1000.0;
 
  // XYZの重力から加速度(m/s^2)を算出
  float xms2 = xg * ms2;
  float yms2 = yg * ms2;
  float zms2 = zg * ms2; 

  if(GCD == 0)
  {
    if(xms2 <= -15.0)
    {
      if(squatflg >= 1)
      {
        GCD = 3;
      }
      else
      {
        jumpflg = 5; 
      }
    }
    else if(xms2 >= -5.0)
    {
      if(jumpflg >= 1)
      {
        GCD = 3;
      }
      else
      {
        squatflg = 5;
      }
    }
    squatflg--;
    jumpflg--;
  }
  else
  {
    if(squatflg >= 1)
    {
        Serial.println('S');
        btport.println('S');
    }
    else  if(jumpflg >= 1)
    {
        Serial.println('J');
        btport.println('J');
    }
    GCD--;
  }
/*
  Serial.print(xms2);
  Serial.print(", ");
  Serial.print(yms2);
  Serial.print(", ");
  Serial.print(zms2);
  Serial.print(", ");
  Serial.print(GCD);
  Serial.print(", ");
  Serial.print(jumpflg);
  Serial.print(", ");
  Serial.print(squatflg);
  Serial.println();
*/ 
  delay(50);
}
