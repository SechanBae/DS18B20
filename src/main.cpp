//I Sechan Bae, 000803348 certify that this material is my original work. No other person's work has been used without due acknowledgement. I have not made my work available to anyone else."
#include <Arduino.h> 
#include <OneWire.h> 
#include <DallasTemperature.h> 
 
// Pin that the  DS18B20 is connected to 
const int oneWireBus = D3;      
 
// Setup a oneWire instance to communicate with any OneWire devices 
OneWire oneWire(oneWireBus); 
 
// Pass our oneWire reference to Dallas Temperature sensor  
DallasTemperature DS18B20(&oneWire); 
DeviceAddress tempSensor;
String getJudgement(float temp){
  float upper[]={10,15,25,30,35,50};
  float lower[]={0,10,15,25,30,35};
  String judgements[]={"Cold!","Cool","Perfect","Warm","Hot","Too Hot!"};
  for(int i=0;i<6;i++){
    if((temp<upper[i])&&(temp>=lower[i])){
      return judgements[i];
    }
  }
  return "Out of Range";
}
void setup() { 
  // configure the USB serial monitor 
  Serial.begin(115200); 
 
  // Start the DS18B20 sensor 
  DS18B20.begin();
  uint8_t address[8];
  if(!DS18B20.getAddress(tempSensor,0)){
    Serial.println("NO DS18B20 DEVICE FOUND: ");
    return;
  }
  
  Serial.print("DS18B20 DEVICE FOUND : ");
  for(int i=0;i<8;i++){
    Serial.printf("%02X",address[i]);
  }
  Serial.println();
} 
 
void loop() { 
  float fTemp; 
 
  // ask DS18B20 for the current temperature 
  DS18B20.requestTemperatures(); 
 
  // fetch the temperature.  We only have 1 sensor, so the index is 0. 
  fTemp = DS18B20.getTempCByIndex(0); 
  String judgement=getJudgement(fTemp);
  // print the temp to the USB serial monitor 
  Serial.println("Current temperature is: " + String(fTemp) + " deg. Celsius or "+judgement); 
 
  // wait 2s (2000ms) before doing this again 
  delay(5000); 
} 