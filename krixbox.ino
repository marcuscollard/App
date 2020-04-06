#include <SoftwareSerial.h>

//analog pins för accelerometer
const int maxGpin= A4;
const int minGpin= A3;
const int aXpin  = A2;
const int aYpin  = A1;
const int aZpin  = A0;


//defines for the bluetooth device
const byte rxPin = 2;
const byte txPin = 3;
SoftwareSerial btSerial(rxPin, txPin);


//debug
//definitioner för konvertering från adc till volt.
const float maxGvolts;
const float minGvolts;
const float maxAdcBits = 2047.0f;
const float maxAdcVolts = 4.95f;
const float voltsPerBit = (maxAdcVolts / maxAdcBits);
const float voltsPerG = 1.50f;

//definitioner för debug
//const float zeroG = 0.82f; //Värdet i volt där axlarna är i våg. cos(90)
//const float negG  = 0.66f; //värdet där axlarna är i lod. (-1g)
float aXprint, aYprint, aZprint;


void setup() {
  //USB serial data
  Serial.begin(9600);

  //Bluetooth serial data
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  btSerial.begin(9600);

  analogReference(EXTERNAL);
  
}


void loop(){
  //initialisering kör en gång
  const int maxGread = analogRead(maxGpin);
  const int minGread = analogRead(minGpin);
  const float maxGvolts = maxGread*voltsPerBit;
  const float minGvolts = minGread*voltsPerBit;
  const float maxG = maxGvolts/voltsPerG;
  const float minG = minGvolts/voltsPerG;
  analogRead(aXpin);
  analogRead(aYpin);
  analogRead(aZpin);
  delay(500);
  Serial.print(maxGvolts);
  Serial.print(" maxGvolts\t");
  Serial.print(maxG);
  Serial.print(" maxG\n");
  Serial.print(minGvolts);
  Serial.print(" MIN_Volts\t");
  Serial.print(minG);
  Serial.print(" minG\n");
  delay(500);
  
  
  delay(500);
  while(1){
    collission(maxG, minG); //kollar efter en smäll
    dbgPrint(maxG, minG);
    //btSerial.print(0); //skriver en nolla till bt hela tiden
 
    delay(10);
    //btSerial.flush();
    //Serial.flush();
  }
}

/*Tar värden från accelerometern och skickar en etta till blåtanden
 *om det skulle vara så att det smäller kraftigare än gränsvärdet.
 *Skickar även information till USB-porten för att se hur kraftig smällen var,
 *mest för debug och kalibreringssyfte.
 */
void collission(const float maxG, const float minG)
{
 //Samma som ovan fast i andra riktningen
 
  float aX = (analogRead(aXpin)*voltsPerBit)/voltsPerG;
  float aY = (analogRead(aYpin)*voltsPerBit)/voltsPerG;
  float aZ = (analogRead(aZpin)*voltsPerBit)/voltsPerG; 

  aXprint = aX;
  aYprint = aY;
  aZprint = aZ;
 
//  dbgPrint(maxG, minG);


  if(aX>maxG||aX<minG){
    btSerial.print(1);
    
    Serial.print("X-Bonk!");    
    dbgPrint(maxG, minG);
  }
  if(aY>maxG||aY<minG){
    btSerial.print(1);
    Serial.print("Y-Bonk!");
    dbgPrint(maxG, minG);
  }
  if(aZ>maxG||aZ<minG){
    btSerial.print(1);
    Serial.print("Z-Bonk!");
    dbgPrint(maxG, minG);
  }
}

void dbgPrint(float maxG, float minG)
{  
    Serial.print(aXprint);
    Serial.print(",");  
    Serial.print(aYprint);
    Serial.print(",");
    Serial.print(aZprint);
    Serial.print('\t');
    Serial.print (maxG);
    Serial.print(",");
    Serial.print (minG);
    Serial.print('\n');
}
