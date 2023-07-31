/*
   Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleScan.cpp
   Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

//----------Bluetooth----------------------
float scanTime = 1; //In seconds
String Esp32n1 = "7c:9e:bd:f8:c8:5e";//"4c:34:a3:9b:3d:ad";
String Esp32n2 = "3c:61:05:13:d5:e2";
String Esp32n3 = "3c:61:05:12:a4:56";
String Esp32n4 = "24:0a:c4:ed:58:d2";
String Esp32n5 = "ca:12:1f:53:7d:3e";
//int N= 1000;//n° de 100 interações
String Beacon1 = "ea:f7:7b:60:97:4e";
BLEScan* pBLEScan;

float distancia=0;
float ptdt=0;
//float Mediana1=0,Mediana2=0,Mediana3=0,Mediana4=0,Mediana5=0,Mediana6=0,Mediana7=0,Mediana8=0,Mediana9=0,RSSIfinal=0,RSSImedido=0;

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning...");
  BLEDevice::init("");
  
}

//-------------Funções auxiliares----------

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      String dispositivoencontrado = advertisedDevice.getAddress().toString().c_str();
      if (dispositivoencontrado == Beacon1)
      
    {
      Serial.println("Beacon1=");
     // Serial.println(advertisedDevice.getRSSI());
      float RSSImedido =advertisedDevice.getRSSI();
     float RSSIfiltrado= filtroPB(RSSImedido);
     //Serial.print(RSSIfiltrado);
     //Serial.print(",");
    //z
    3Serial.println(RSSImedido);
     float pli=1.6;//pass loss index
     float RSSI_1m= 68.7;
     float ptdt= (-RSSI_1m -RSSIfiltrado)/(10*pli);
     //Serial.println(ptdt);
     distancia = pow(10,ptdt);
      //Serial.print(",");
     Serial.println(distancia);
    }
    //String dispositivoencontrado2 = advertisedDevice.getAddress().toString().c_str();
    //  if (dispositivoencontrado2 == Esp32n2)
      
    //{
    //  Serial.println("Rssi Esp 2=");
    //  Serial.println(advertisedDevice.getRSSI());
    //}
    //String dispositivoencontrado3 = advertisedDevice.getAddress().toString().c_str();
    //  if (dispositivoencontrado3 == Esp32n4)
      
    //{
    
     
     
      
    //}
   // }
      
}
};

//-----------------------Passa Baixa----------------


float filtroPB(float x)
{
  static float y_pass[2] = {0,0}, x_pass[2] = {0,0};
  const float a=0.75, b =0.80;
  float y = (a+b)*y_pass[0]-a*b*y_pass[1]+(1-a-b+a*b)*x_pass[1];
  deslocaVetor(y_pass, 2, y);
  deslocaVetor(x_pass, 2, x);
  return y;
}


void deslocaVetor(float *vetorAddr, int tam, float valor)
{
  for(int k=tam-1; k>0;k--)
  {
    *(vetorAddr+k)=*(vetorAddr+k-1);
  }
  *vetorAddr = valor;
}
//---------------------Escaneamento BLE--------------------
void scanBLE()
{
  
  BLEScan* pBLEScan = BLEDevice::getScan(); //create new scan
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
  BLEScanResults foundDevices = pBLEScan->start(scanTime);
  //Serial.println("Dispositivos Encontrados");
  //Serial.println(foundDevices.getCount());
  //Serial.println("Sinal RSSI esp32 n°2= ");
  
}



void loop()
{
  
  scanBLE();
  
 }
