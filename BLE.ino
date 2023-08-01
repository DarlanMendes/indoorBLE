/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <map>
#include <string>
//----------Bluetooth----------------------
float scanTime = 1; //In seconds
 std::map<char, double> beaconRSSIs={
   {'A',0},
    {'B',0},
    {'C',0},
    {'D',0}
 };
  std::map<char, String> beaconMACs ={
    {'A',"ea:f7:7b:60:97:4e"},
    {'B',"c4:01:12:14:28:8a"},
    {'C',"fc:15:e2:04:45:8b"},
    {'D',"e7:66:37:f2:0c:a4"}
  };
BLEScan* pBLEScan;



void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
  BLEDevice::init("");
 
}



class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      String macDispositivoEncontrado = advertisedDevice.getAddress().toString().c_str();
      
      for (const auto& kvp : beaconMACs) {
            if (macDispositivoEncontrado == kvp.second) {
                beaconRSSIs[kvp.first] = advertisedDevice.getRSSI();
            }
        } //kvp chave-value-pair destructured  kvp.first 'A' ...'D' \ kvp.second == MAC endereço
    }
};


//---------------------Escaneamento BLE--------------------
void scanBLE()
{
  
  BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  BLEScanResults foundDevices = pBLEScan->start(scanTime);
  
  
}

void printRSSIs(){
  Serial.print("Rssi beaconA: ");
  Serial.println(beaconRSSIs['A']);
  Serial.print("Rssi beaconB: ");
  Serial.println(beaconRSSIs['B']);
   Serial.print("Rssi beaconC: ");
  Serial.println(beaconRSSIs['C']);
   Serial.print("Rssi beaconB: ");
  Serial.println(beaconRSSIs['D']);
}

void loop()
{
  
  
   if (Serial.available()) {
      Serial.println("Entrou");
        // Ler e processar a mensagem enviada pelo terminal serial
        String mensagem = Serial.readStringUntil('\n');
        if(mensagem == "GetRssi"){
          scanBLE();
          printRSSIs();
        }
        
    }
 }