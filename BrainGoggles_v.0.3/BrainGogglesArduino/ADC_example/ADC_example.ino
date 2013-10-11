
#define SELPIN 7 //Selection Pin 
#define SELPIN2 8 //Selection Pin for 2nd ADC
#define DATAOUT 11//MOSI 
#define DATAIN  12//MISO 
#define SPICLOCK  13//Clock 
int readvalue;
float readvaluefloat;

void setup(){ 
 //set pin modes 
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

 Serial.begin(9600); 
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

void loop() { 
  
 readvalue = read_adc(1);
 Serial.println(readvalue,DEC); 
  readvalue = read_adc(2); 
  readvaluefloat = (float)readvalue/4095*5.0;
 Serial.println(readvaluefloat,DEC);
  readvalue = read_adc(3); 
 Serial.println(readvalue,DEC);
  readvalue = read_adc(4); 
 Serial.println(readvalue,DEC);
  readvalue = read_adc(5); 
 Serial.println(readvalue,DEC);
  readvalue = read_adc(6); 
 Serial.println(readvalue,DEC);
  readvalue = read_adc(7); 
 Serial.println(readvalue,DEC);
  readvalue = read_adc(8); 
 Serial.println(readvalue,DEC);
 Serial.println(" "); 
 
 readvalue = read_adc2(1); 
 Serial.println(readvalue,DEC); 
  readvalue = read_adc2(2); 
 Serial.println(readvalue,DEC); 
  readvalue = read_adc2(3); 
 Serial.println(readvalue,DEC); 
  readvalue = read_adc2(4); 
 Serial.println(readvalue,DEC); 
  readvalue = read_adc2(5); 
 Serial.println(readvalue,DEC); 
  readvalue = read_adc2(6); 
 Serial.println(readvalue,DEC); 
  readvalue = read_adc2(7); 
 Serial.println(readvalue,DEC); 
  readvalue = read_adc2(8); 
 Serial.println(readvalue,DEC); 
 
 Serial.println(" "); 
 delay(2000); 
} 
 
