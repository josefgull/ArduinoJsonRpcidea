//this  code is a very ditry why to comunicate witha arduino over Json RPC   


#include <Arduino.h>
#include <ArduinoJson.h>


int flag;
String str;
StaticJsonDocument <600>doc;


void m1(){
  doc["Angle"] = "getAngle"+random(1);          //Requestig values from microcontroller
  doc["MAGnitude"] = "getMagnitude"+random(1);
  serializeJsonPretty(doc, Serial);
}


void m2()         //methode m1
{
  uint8_t r = doc["r"];   //reading out vars
  uint8_t g = doc["g"];
  uint8_t b = doc["b"];
  Serial.print("b=");
  Serial.println(b);
  
  serializeJsonPretty(doc, Serial);
}


void jsonRpc(String str){                                     //determins with methode should be called
  DeserializationError error = deserializeJson(doc, str);
  // Test if parsing succeeds.
  if (error)
  {
    Serial.println(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
  }
 
    String methode = doc["methode"];
  
  if (methode=="m1")   //method names should be short
    updateLedRing();
    
  else if (methode=="m2")
    getVal();
    
  else 
   Serial.print(F("No such methode "));
}




void setup()
{
  delay(2000);
  Serial.begin(115200);
}


void loop()
{
  if (Serial.available() > 0)
 {
    str = Serial.readStringUntil('\n');// strings need to be written in this format  {"methode":"m1","params":{"r":13,"g":13,"b":13},"id":0} wthi\n at the end
    flag = 1;
  }
  if (flag == 1)
  {
    jsonRpc(str);
    flag=0;
  }
  delay(20);
}
