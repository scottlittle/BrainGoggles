//Scott Little, BrainGoggles, 2013, GNU GPL v3
#include <SoftwareSerial.h>
#include "Tlc5940.h"
SoftwareSerial bluetooth(4,2);  //TX 4, RX 2

#define SELPIN 7 //Selection Pin 
#define SELPIN2 8 //Selection Pin for 2nd ADC
#define DATAOUT 12//MOSI 
#define DATAIN  5//MISO 
#define SPICLOCK  6//Clock 
int readvalue;
int readvalue1;
float readvaluefloat;
byte readvaluelow;
byte readvaluehigh;
byte readvaluearray[2];

void setup()
{
  /* Call Tlc.init() to setup the tlc.
     You can optionally pass an initial PWM value (0 - 4095) for all channels.*/
  Tlc.init();  //interferes with other SPI
  //set pin modes 
  Tlc.clear();
  
  pinMode(SELPIN, OUTPUT); 
  pinMode(SELPIN2, OUTPUT);
  pinMode(DATAOUT, OUTPUT); 
  pinMode(DATAIN, INPUT); 
  pinMode(SPICLOCK, OUTPUT); 
  //disable device to start with 
  digitalWrite(SELPIN,HIGH); 
  digitalWrite(SELPIN2,HIGH);
  digitalWrite(DATAOUT,LOW); 
  digitalWrite(SPICLOCK,LOW); 
  //The next two lines set up the serial recieved from bluetooth.
  //pinMode(2, INPUT);
  //pinMode(4, OUTPUT);
  bluetooth.begin(9600); 
  Serial.begin(9600);
  
}

void loop()
{

  Tlc.set(1, 4095);
  Tlc.update();
  
  if (bluetooth.available()) // Wait until a character is received
  {
    char val = (char)bluetooth.read();
    //Serial.println(val);
  		
    switch(val) // Perform an action depending on the command
    {
      case 'q'://turn the light on when a 'q' is received
  	on();
      break;
  
      case 'w'://turn the light off when a 'w' is received
  	off();
      break;
  
      //default://otherwise remain in the previous state
  	//idle();
      //break;
    }
  }
  
  //Serial.println(" "); 
  
  readvalue = read_adc(1);
  //Serial.println(readvalue,DEC); 
  
  readvalue = read_adc(2); 
  //readvaluefloat = (float)readvalue1/4095*5.0;
  readvaluehigh = highByte(readvalue);
  readvaluelow = lowByte(readvalue);
  readvaluearray[0]=readvaluehigh;
  readvaluearray[1]=readvaluelow;
  bluetooth.write(readvaluearray,2);
  
  readvalue = read_adc(3); 
  //Serial.println(readvalue,DEC);
  readvalue = read_adc(4); 
  //Serial.println(readvalue,DEC);
  readvalue = read_adc(5); 
  //Serial.println(readvalue,DEC);
  readvalue = read_adc(6); 
  //Serial.println(readvalue,DEC);
  readvalue = read_adc(7); 
  //Serial.println(readvalue,DEC);
  readvalue = read_adc(8); 
  //Serial.println(readvalue,DEC);
  //Serial.println(" "); 
 
  readvalue = read_adc2(1); 
  //Serial.println(readvalue,DEC); 
  readvalue = read_adc2(2); 
  //Serial.println(readvalue,DEC); 
  readvalue = read_adc2(3); 
  //Serial.println(readvalue,DEC); 
  readvalue = read_adc2(4); 
  //Serial.println(readvalue,DEC); 
  readvalue = read_adc2(5); 
  //Serial.println(readvalue,DEC); 
  readvalue = read_adc2(6); 
  //Serial.println(readvalue,DEC); 
  readvalue = read_adc2(7); 
  //Serial.println(readvalue,DEC); 
  readvalue = read_adc2(8); 
  //Serial.println(readvalue,DEC); 
 
  //Serial.println(" "); 
  delay(50);
}




int read_adc(int channel){
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)
  
  //allow channel selection
  commandbits|=((channel-1)<<3);

  digitalWrite(SELPIN,LOW); //Select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    digitalWrite(DATAOUT,commandbits&1<<i);
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);    
  }

  digitalWrite(SPICLOCK,HIGH);    //ignores 2 null bits
  digitalWrite(SPICLOCK,LOW);
  digitalWrite(SPICLOCK,HIGH);  
  digitalWrite(SPICLOCK,LOW);

  //read bits from adc
  for (int i=11; i>=0; i--){
    adcvalue+=digitalRead(DATAIN)<<i;
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);
  }
  digitalWrite(SELPIN, HIGH); //turn off device
  return adcvalue;
}

int read_adc2(int channel){    //for the second ADC
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)
  
  //allow channel selection
  commandbits|=((channel-1)<<3);

  digitalWrite(SELPIN2,LOW); //Select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    digitalWrite(DATAOUT,commandbits&1<<i);
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);    
  }

  digitalWrite(SPICLOCK,HIGH);    //ignores 2 null bits
  digitalWrite(SPICLOCK,LOW);
  digitalWrite(SPICLOCK,HIGH);  
  digitalWrite(SPICLOCK,LOW);

  //read bits from adc
  for (int i=11; i>=0; i--){
    adcvalue+=digitalRead(DATAIN)<<i;
    //cycle clock
    digitalWrite(SPICLOCK,HIGH);
    digitalWrite(SPICLOCK,LOW);
  }
  digitalWrite(SELPIN2, HIGH); //turn off device
  return adcvalue;
}

//void idle(void)
//{
  //do nothing, remain in previous state
//}

void on(void)
{
  Tlc.set(5, 4095);  //set pin 5 to max brightness
  Tlc.update();  //execute set
  bluetooth.println("on");
  Serial.println("on");
}

void off(void)
{
  Tlc.set(5, 0);  //set pin 5 to min brightness
  Tlc.update();  //execute set
  bluetooth.println("off");
  Serial.println("off");
}
