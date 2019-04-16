#include <SPI.h>

#include <MFRC522.h>

#define RST_PIN        9
#define SS_1_PIN       8
#define SS_2_PIN       10
#define NR_OF_READERS  2


int kirmizi_led=7;
int asansr_led=4;
int sinyal_led=5;


byte ID[4]={89,58,201,86};
byte ssPins[]={SS_1_PIN, SS_2_PIN};
MFRC522 mfrc522[NR_OF_READERS];





void setup() {
pinMode(kirmizi_led,OUTPUT);
pinMode(asansr_led,OUTPUT);
pinMode(sinyal_led,OUTPUT);


digitalWrite(kirmizi_led,LOW);
digitalWrite(asansr_led,LOW);
digitalWrite(sinyal_led,LOW);
Serial.begin(9600);
while(!Serial);
SPI.begin();


for(uint8_t reader=0; reader<NR_OF_READERS; reader++){
  mfrc522[reader].PCD_Init(ssPins[reader], RST_PIN);
  }

}


void loop() {

  while(1){
  for(uint8_t reader=0; reader<NR_OF_READERS; reader++){
     if (mfrc522[reader].PICC_IsNewCardPresent() && mfrc522[reader].PICC_ReadCardSerial())
    {
        if(mfrc522[reader].uid.uidByte[0]==ID[0] &&
           mfrc522[reader].uid.uidByte[1]==ID[1] &&
           mfrc522[reader].uid.uidByte[2]==ID[2] &&
           mfrc522[reader].uid.uidByte[3]==ID[3] ){
            
            if(reader==0 && reader!=1){
              
               digitalWrite(asansr_led,HIGH);
   
              Serial.println(" asansöre sinyal gönderiliyor");
              delay(100);

           
               for(int i=0; i<10; i++){
               
                Serial.println(" uyarı sinyali");
                digitalWrite(sinyal_led,HIGH);
                delay(300);
                digitalWrite(sinyal_led,LOW);
                delay(300);
               
             
               
               }
               
               
             }
               delay(300);
               if(reader==1){
               digitalWrite(asansr_led,LOW);
               Serial.println(" asansör sinyali kesil");
               delay(100);
               }
             
             
            }
             else{
            digitalWrite(kirmizi_led,HIGH);
            delay(500);
            digitalWrite(kirmizi_led,LOW);
          }
              }
  }
              delay(2000);
          digitalWrite(asansr_led,LOW);
          Serial.println(" asansör calışmaya devam");
         
            }
         
           } 
      

  
  
  





