#include <Servo.h>
#include <DFRobotDFPlayerMini.h>

#include <SoftwareSerial.h>
#include <Ultrasonic.h>

#define TRIGGER_PIN  10
#define ECHO_PIN     9

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

DFRobotDFPlayerMini myDFPlayer;

Servo tampa;  // cria um objeto servo para controlar um servo
int pos = 0;

int const buzzPin = 2;
void mededistancia();
void fechar();
void abrir();
boolean estado=false;
void setup() {

  pinMode(LED_BUILTIN, OUTPUT);  // inicializa o pino digital LED_BUILTIN (13) como saida (para comandar o LED)
  tampa.attach(3);               // Associa o servo no pino 3 (digital com PWM) ao objeto servo da tampa 
  pinMode(buzzPin, OUTPUT);      // se usar um buzzer, configurar o pino digital como OUTPUT para controla-lo


  
  Serial.begin(9600);
  myDFPlayer.begin(Serial);
  myDFPlayer.volume(20);
  tampa.write(65);              // tell servo to go to position in variable 'pos'
  
} // fim da funcao setup

void loop() {
   mededistancia();
  
} // fim da funcao loop


void beep (){
  digitalWrite(buzzPin, HIGH); delay(15); digitalWrite(buzzPin, LOW); // beep
  
}
void abrir(){
  for (pos = 62; pos >= 0; pos -= 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    tampa.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }  
}
void fechar(){
  for (pos = 0; pos <= 62; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    tampa.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
}
void mededistancia(){
  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
   if (cmMsec <= 30 && estado==false){
        abrir();
        beep();
        delay(5000);
        estado=true;
       }
   if(cmMsec > 40 && estado==true){
      fechar();
      myDFPlayer.play(1);
      delay(5000);
      estado=false;    
    }
  delay(1000);
}
