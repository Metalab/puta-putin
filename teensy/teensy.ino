/*

 Oct. 2012
 by overflo.
 
 https://metalab.at/wiki/Puta_Putin

 The code works, its nothing special.
 Abuse freely.

*/
#include <Servo.h>  


int ledpin=11; // teensy ..

int sensorpin = PIN_B4;
int servopin = PIN_D7;


int rotaugenpin1= PIN_D0;
int rotaugenpin2= PIN_B7;


int sensorthreshold = 120;


 long offen=0;
long open_soon=0;



int OPENPOS=180;
int CLOSEPOS=100;


int MOVEMENTTIMEOUT =1000;



Servo augen;

void setup() {
  Serial.begin(9600);
  pinMode(ledpin, OUTPUT);   

  pinMode(rotaugenpin1, OUTPUT); 
  pinMode(rotaugenpin2, OUTPUT); 

  
  digitalWrite(rotaugenpin1,1);
  digitalWrite(rotaugenpin2,1);
  
  augen.attach(servopin);
  augenzu();
  


  
}
 
void loop() {
  
  

  
// we read the sensor Value
  int sensorValue = analogRead(sensorpin);


  if (sensorValue >= sensorthreshold) 
  { 
  
   if(!open_soon) 
    open_soon=millis();  

 
  } 
  else
   open_soon=0;
  
  
    Serial.print("Pre sensorValue: " );  
  Serial.print(sensorValue);  
  Serial.print(" offen: ");
  Serial.print(offen);
  Serial.print(" open_soon: ");                            
  Serial.print(open_soon);
  Serial.print(" millis(): ");
  Serial.print(millis());
    Serial.print("\n");
  
  
  if(open_soon && ((millis()-open_soon)>MOVEMENTTIMEOUT))
  {
   open_soon=0;
   augenauf();   
  }


  if(offen && ((millis()-offen)>3000))
  {
    augenzu();
    
  }

  Serial.print("sensorValue: " );  
  Serial.print(sensorValue);  
  Serial.print(" offen: ");
  Serial.print(offen);
  Serial.print(" open_soon: ");                            
  Serial.print(open_soon);
  Serial.print(" millis(): ");
  Serial.print(millis());
    
  Serial.print("\n");

  delay(100);
  
  

}




void augenauf()
{
  
  Serial.println("auf");
    offen=millis();
    open_soon=0;
    augen.attach(servopin);;
    augen.write(OPENPOS); 
    glow();
    
    
    
    
    
}


void augenzu()
{
  
  
  Serial.println("zu");
 offen=0;
 open_soon=0;
 digitalWrite(ledpin, LOW); 
 augen.write(CLOSEPOS); 
 delay(1000);
 augen.detach(); 
}



void glow()
{
  


  
  while((analogRead(sensorpin) >sensorthreshold))
  {
  // an
 digitalWrite(rotaugenpin1,0);
  digitalWrite(rotaugenpin2,0);

 
  }
  
  
  // aus!
 digitalWrite(rotaugenpin1,1);
  digitalWrite(rotaugenpin2,1);
  
}

