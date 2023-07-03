#include <Servo.h>


String matlabData;
Servo servoMotor2;

void setup() {
 //pinMode(LED_BUILTIN, OUTPUT);

   Serial.begin(9600);
   servoMotor2.attach(9);
}

void loop() {

  if (Serial.available()>0){  //si hay datos disponibles en el serial
    //digitalWrite(LED_BUILTIN, HIGH);

    
    matlabData=Serial.readString();
    servoMotor2.write(matlabData.toInt());
    delay(1000);

    
   // Serial.println(matlabData);
  }
  else {
        //digitalWrite(LED_BUILTIN, LOW);
        
        servoMotor2.write(0);
          delay(1000);
          
          }
}

//CÓDIGO ROBOT LEER TRES ÁGULOS CAJITAS
//Descomentar en matlab App Designer el código indicado
//Comentar todo el código superior y descomentar este


//#include <Servo.h>
 
//String readString;

//Servo servoMotor1;
//Servo servoMotor2;
//Servo servoMotor3;

//void setup() {
// Iniciamos el monitor serie para mostrar el resultado
//  Serial.begin(9600);
 
// Iniciamos el servo para que empiece a trabajar con el pin 9
//   servoMotor1.attach(8);
//   servoMotor2.attach(9);
//   servoMotor3.attach(10);
   
//}
 

//void loop() {

// if (Serial.available()>0)  {
//   char c = Serial.read();  
//   if (c == ',') {
//     if (readString.length() >1) {
//       int n = readString.toInt();  //convert readString into a number
//
//       if(readString.indexOf('a') >0) servoMotor1.write(n);
//       if(readString.indexOf('b') >0) servoMotor2.write(n);
//       if(readString.indexOf('c') >0) servoMotor3.write(n);
//     
//
//       readString=""; 
//     }
//   } 
//   else {     
//       readString += c; 
//       servoMotor1.write(0);
//       servoMotor2.write(0);
//       servoMotor3.write(0);
//   }
//  }
//    delay(1000);
//}
