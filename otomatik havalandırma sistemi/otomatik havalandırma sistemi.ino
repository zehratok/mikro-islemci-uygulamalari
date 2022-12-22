#define BLYNK_TEMPLATE_ID "TMPLjObdfSj4"
#define BLYNK_DEVICE_NAME "GazDedektor"
#define BLYNK_AUTH_TOKEN "s8o5iHidZmtIA4PLooFe_GgVXF2siSui"
char auth[] = "s8o5iHidZmtIA4PLooFe_GgVXF2siSui"; //Blynk token
char ssid[] = "Alaska"; //Wifi ismi
char pass[] = "alaska1234"; //Wifi parolası
//Gerekli kütüphaneler
#include <SPI.h>
#include <BlynkSimpleEsp8266.h>
//Sabit değişkenler
#define MQ2pin (A0) //A0
#define BLYNK_PRINT Serial
#define buzzerPin 0 //D3
#define GreenLed 14 //D5
#define RedLed 12 //D6
#define Air 5 //D1 motor sürücü in1
#define Air2 4 //D2 motor sürücü in2
BlynkTimer timer;
float sensorDegeri; //Sensörden okunacak değer
int n,m;
void setup()
{
 Serial.begin(115200);
 Serial.println("Gas sensor warming up!");
 delay(5000);
 Blynk.begin(auth, ssid, pass);
 pinMode(Air, OUTPUT); //motor sürücü in1 çıkış olarak tanımlandı
 pinMode(Air2, OUTPUT); //motor sürücü in2 çıkış olarak tanımlandı
 pinMode(GreenLed, OUTPUT); //yeşil led çıkış olarak tanımlandı
 pinMode(RedLed, OUTPUT); //kırmızı led çıkış olarak tanımlandı
 pinMode(16,OUTPUT);
 pinMode(buzzerPin,OUTPUT); //buzzer çıkış olarak tanımlandı
 pinMode(MQ2pin, INPUT); //gaz sensörü giriş olarak tanımlandı
 digitalWrite(GreenLed, LOW); //başlangıçta yeşil led sönük
 digitalWrite(RedLed, LOW); //başlangıçta kırmızı led sönük
 timer.setInterval(1000L, sendUptime);
}
void sendUptime()
{
 Blynk.virtualWrite(V2, sensorDegeri); //Blynk üzerinde sensörden okunan değer yazdırıldı
}
void loop()
{
 sensorDegeri = analogRead(MQ2pin); //sensör değeri onup değişkene atandı
 Serial.println("");
 Serial.print("Sensor Degeri: ");
 Serial.print(sensorDegeri); //sensör değeri seri porta yazdırıldı
 Serial.println("");
 Serial.println("");
 Serial.print("smoke: ");
 Serial.print(A0); //
 Serial.println("");
 Blynk.virtualWrite(V2, sensorDegeri); //sensör değeri Blynk’e yazdırıldı
 if(sensorDegeri > 550 && sensorDegeri < 900) //sensör değeri normalin üzerindeyse
 {
 Serial.print("Smoke detected!");
 digitalWrite(Air, HIGH); //havalandırma sistemi devreye girdi
 digitalWrite(Air2, LOW);
 delay(2000);
 }

 n=analogRead(A0);
 if(n>900)
 {
 n==m;
 m=analogRead(A0);
 Serial.println(m);
 }
 if(n>550 && n<900) //sensör değeri normalin üzerindeyse
 {
 digitalWrite(buzzerPin, LOW);
 digitalWrite(RedLed, HIGH); //kırmızı led ışık vermeye başladı
 digitalWrite(Air, HIGH); //havalandırma sistemi devreye girdi
 digitalWrite(Air2, LOW); //havalandırma sistemi devreye girdi
 digitalWrite(GreenLed, LOW); //yeşil led söndü
 digitalWrite(Air, HIGH);
 tone(buzzerPin,800,80); //buzzer ötmeye başladı
 delay(2000);
 }

 if(n<550)
 {
 digitalWrite(GreenLed,HIGH ); //yeşil led ışık vermeye başladı
 digitalWrite(buzzerPin,LOW);
 digitalWrite(Air,LOW); //havalandırma sistemi devreden çıktı
 digitalWrite(Air2,LOW); //havalandırma sistemi devreden çıktı
 digitalWrite(RedLed,LOW); //kırmızı led söndü
 delay(2000);
 noTone(buzzerPin); //buzzer ötmeyi durdurdu
 }
 Blynk.run();
}