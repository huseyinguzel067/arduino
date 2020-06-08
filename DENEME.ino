//A:İÇ SİCAKLİK
//B:İÇ NEM
//C:DİŞ SİCAKLİK
//D:DİŞ NEM
//E:TOPRAK NEM
//F:SU DEPOSU
//G:IŞIK SİDDETİ
//H:HAREKET
//K:YAĞMUR
//Havalandırma kapalı:I
//Havalandırma Acık:i
//işik kapalı:j
//işik açık:l
//isitici açık:m
//isitici kapali:n
//Sulama açık:p
//sulama kapalı:r
//havalandırma aç:s
//havalandırma kapat:t
//suyu aç:u
//suyu kapat:v
//işik aç:y
//işik kapat:z
//isitici aç:w
//isitici kapat:q
#include <TimerOne.h>
#include <SPI.h>
#include <Ethernet.h>
#include <dht11.h> // dht11 kütüphanesini ekliyoruz.
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(10,99,4,29);
//IPAddress gateway(10,99,0,1);
//IPAddress subnet(255,255,240,0);
IPAddress ip(192,168,31,24);
IPAddress gateway(192,168,31,1);
IPAddress subnet(255, 255, 255, 0);
EthernetServer server(23);
boolean alreadyConnected = false; // whether or not the client was connected previously
///////////
#define DHT11PIN 2 // DHT11PIN olarak Dijital 2'yi belirliyoruz.
#define DHT11PI 8
int pirPin = 3; // PIR pin
int supin = 4;   // Led aç/kapa
int isiticipin=5;//Havalandırma aç/kapa
int ledpin=6;//Isıtıcı aç/kapa
int havapin=7;//Su aç/kapa
int nRainDigitalIn = 9;



int nempin = A3;
const int sensorPin = A2; //Su Seviyesi
int nRainIn = A1;//yagmur sensörü okuma pini
int LDR_Pin = A0; //analog pin 0


char giden;
dht11 DHT11;
char gelen;
boolean bIsRaining = false;
String gel;
String strRaining;
String su;
String isi;
String isik;
String hava;
int liquid_level;
int nRainVal;
int deger = 0;
int sayac=0;
void setup() {
  // Timer1.initialize(1000000); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
 // Timer1.attachInterrupt(bag);
  Ethernet.begin(mac, ip, gateway, subnet);
  // start listening for clients
  server.begin();
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
  Serial.print("Chat server address");
  Serial.println(Ethernet.localIP());
  //////////
  pinMode(pirPin, INPUT);  // PIR Pin'i giriş yapılıyor
  pinMode(2, INPUT);
  pinMode(8, INPUT);
  pinMode(nRainDigitalIn,INPUT);
  
  pinMode(ledpin, OUTPUT);      // LED Pin'i çıkış yapılıyor
  pinMode(havapin, OUTPUT);
  pinMode(supin, OUTPUT);
  pinMode(isiticipin, OUTPUT);
  
  Serial.begin(9600); //sets the baud rate for data transfer in bits/second
  pinMode(sensorPin, INPUT);//the liquid level sensor will be an input to the arduino
}
void hareket(){
 
 deger = digitalRead(pirPin);  // Dijital pin okunuyor
  Serial.print("H");
  Serial.println(deger); 
  // Okunan değer seri porttan okunuyor.
  if (deger == HIGH && isik!="z") {
  digitalWrite(ledpin, HIGH); // Eğer okunan değer 1 ise LED yakılıyor.

  
      Serial.println("isik acik");
  server.print("H");
   server.println("1");
  
    
  
  
  
   
  }
  else if(isik=="y")
  {
  digitalWrite(ledpin, HIGH);
   
   
   Serial.println("isik acik");
    server.print("H");
   server.println("1");
   
   
   
   
     
  // char deger='l';
    //  server.println(deger);
  
  }
  else if(deger==LOW && isik!="y"){
  digitalWrite(ledpin, LOW);  // Eğer okunan değer 0 ise LED söndürülüyor.
  
   
   
   
      Serial.println("isik kapali");
   
   
    server.print("H");
   server.println("0");
   
   
   
    
    // char deger='j';
    //  server.println(deger);
}
else if (deger==HIGH &&  isik=="z")
{
digitalWrite(ledpin, HIGH);
  Serial.println("isik acik");
server.print("H");
   server.println("1");


}

 // bag();
  //delay(2000);
//  bag();

  
}
void bag(){

EthernetClient client = server.available();
       if (Serial.available() > 0){
      
      String giden=Serial.readString();

      Serial.println(giden);
     server.print(giden);
     
      }
       
    if (client.available() > 0) {
      // read the bytes incoming from the client:
       Serial.println("burda");
     String gelen = client.readString();
       Serial.println(gelen.substring(3));
      gel=gelen.substring(3);
      Serial.println(gel);
    
     
      if(gel!=""){
       
      
      if(gel=="s" || gel=="t"){
        hava=gel;
      }
        if(gel=="y" || gel=="z"){
          isik=gel;
      }
        if(gel=="u" || gel=="v"){
          su=gel;
      }
        if(gel=="w"|| gel=="q"){
          isi=gel;
      }
      
}
    }
}

void loop() {  
  // wait for a new client:
  EthernetClient client = server.available();
  // when the client sends the first byte, say hello:
    if (!alreadyConnected) {
      // clead out the input buffer:
      client.flush();    
        Serial.println("We have a new client");
      client.println("Hello, client!");
     Serial.println("androiten kelme gir");  
      alreadyConnected = true;
    } 
    ///havalandırma****
    if(hava == "s"){
     
      Serial.println ("havalandirma acik");
     digitalWrite(havapin, HIGH);
        server.print("H");
   server.println("3");
     
      
        // char deger='i';
        // server.println(deger);
      
      
    }
    else if(hava=="t")
    {
    Serial.println ("havalandirma kapali");
    digitalWrite(havapin, LOW);
       server.print("H");
   server.println("2");
    }
    else{
    Serial.println ("havalandirma kapali");
       server.print("H");
   server.println("2");
    // digitalWrite(havapin, LOW);
    
    }
  //pır**************

  
  

  
  //***pır********
  // Bir satır boşluk bırakıyoruz serial monitörde.
  Serial.println("\n");
 /////isitici****
 if(isi=="w"){
 Serial.println("isitici acik");
 digitalWrite(isiticipin, HIGH);
    server.print("H");
   server.println("5");
   delay(1000);

   // char deger='m';
   // server.println("deger");
 }
 else
 {
   Serial.println("isitici kapali");
   digitalWrite(isiticipin, LOW);
      server.print("H");
   server.println("4");
   delay(1000);
     // char deger='n';
    //  server.println(deger);
 }


/////isitici****

  /////ic sıcaklık ve nem*************
  int chk = DHT11.read(DHT11PIN);
  // Sensörden gelen verileri serial monitörde yazdırıyoruz.
  Serial.print("B");
  Serial.println((float)DHT11.humidity, 0);
  Serial.print("A");
  Serial.println((float)DHT11.temperature, 0);

  bag();
  hareket();
 
  // 2 saniye bekliyoruz. 2 saniyede bir veriler ekrana yazdırılacak.
  delay(2000);
  bag();
  /////ic sıcaklık ve nem*************
  Serial.println("\n");
  /////dıs sıcaklık ve nem*************
  
  
  int ch = DHT11.read(DHT11PI);
  // Sensörden gelen verileri serial monitörde yazdırıyoruz.
  Serial.print("D");
  Serial.println((float)DHT11.humidity, 0);
  Serial.print("C");
  Serial.println((float)DHT11.temperature, 0);

  bag();
 hareket();
  // 2 saniye bekliyoruz. 2 saniyede bir veriler ekrana yazdırılacak.
  delay(2000);
  bag();
  /////dıs sıcaklık ve nem*************
  Serial.println("\n");
  /////toprak  nem*************
   int nem = analogRead(nempin);
  if (nem <= 300)
  {
    Serial.println("Toprak ideal nem seviyesinin ustunde");
    Serial.println("E");
    
  bag();
   hareket();
   delay(1000);
  bag();
  }
  else if (nem > 50 && nem <= 450)
  {
    Serial.println("Toprak ideal nem seviyesinin ustunde");
    Serial.print("E");
    Serial.println(nem);
   
    bag();
     hareket();
   delay(1000);
  
  bag();
  }
    
  else if (nem > 450 && nem <= 700)
  {
    Serial.println("Toprak ideal nem seviyesinde");
    Serial.print("E");
    Serial.println(nem);
   
   bag();
   delay(1000);
   bag();

  }
  else if (nem > 700 && nem <= 1500)
  {
    Serial.println("Toprak nem seviyesinin altinda sulama devreye girecek");
    Serial.print("E");
    Serial.println(nem);
 bag();
  hareket();
   delay(1000);

  bag();
  }
  //else      // Eğer nem değeri 850 den yüksek ise aşağıdaki kodlar devreye girecektir.
  //{
    //Serial.println("Toprak nem seviyesinin altinda sulama devreye girecek");
    //Serial.print("E");
    //Serial.println(nem);
    //bag();
   //delay(1000);
  //bag();
  //}
  /////toprak  nem*************
  Serial.println("\n");
  /////ışık şideti*************
  int LDRReading = analogRead(LDR_Pin);
  Serial.print("G");
  Serial.println(LDRReading);
bag();
 hareket();
 delay(1000);
bag();
////ışık şideti****
  Serial.println("\n");
//yagmur*****
  nRainVal = analogRead(nRainIn);
  bIsRaining = !(digitalRead(nRainDigitalIn));
  if (bIsRaining) {
    strRaining = "Evet";
    server.print("H");
   server.println("8");
   delay(100);
  }
  else {
    strRaining = "Hayir";
    server.print("H");
   server.println("9");
   delay(100);
  }
  Serial.print("Yagmur varmi");
  Serial.println(strRaining);
 
  
  Serial.print("K");
  Serial.println(nRainVal);
   
 
bag();
 hareket();
  delay(1000);
bag();
/////sulama****
if(su=="u"){
Serial.println("sulama acik");
digitalWrite(supin, HIGH);
   server.print("H");
   server.println("7");

}
else
{
  Serial.print("sulama kapali");
  digitalWrite(supin, LOW);
     server.print("H");
   server.println("6");
    // char deger='r';
    // server.println(deger);
}
/////sulama****

/////yagmur*************

  Serial.println("\n");
  /////su seviyesi*************
  liquid_level = analogRead(sensorPin); //arduino reads the value from the liquid level sensor
  Serial.print("F");
  Serial.println(liquid_level);//prints out liquid level sensor reading
 bag();
  hareket();
 delay(1000);//delays 100ms

bag();
  /////su seviyesi*************
  Serial.println("\n");
}

