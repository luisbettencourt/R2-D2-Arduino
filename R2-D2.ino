#include "musical_notes.h" // inclui library referente aos sons emitidos pelo buzzer
#include <Servo.h> // inclui library referente ao motor servo

// definição de variáveis
Servo motor;
int LEDpin[] = {4, 5, 6, 2}; // definição dos pins de saída dos LEDs
int PIRpin[] = {10, 11, 12}; // definição dos pins de entrada dos sensores PIR
int speakerPin = 3; // definição dos pins de saída do buzzer
boolean PIRstatus;                  
int PIRstateprev[] = {1, 1, 1};
int PIRpinAtual = 3;
int PIRposition[] = {30, 150, 90};

 void setup()
 {
   Serial.begin(9600);
   for (int i = 0; i < 4; i++)  { // define todos os LEDS como OUTPUTS
    pinMode(LEDpin[i], OUTPUT);
   }
   for (int i = 0; i < 3; i++)  { // define todos os sensores PIR como INPUTS
    pinMode(PIRpin[i], INPUT);
   }
   pinMode(speakerPin, OUTPUT); // define o buzzer como OUTPUT
   motor.attach(7); // define o PIN do servo
   motor.write(PIRposition[2]); // coloca o servo na posiçao central (90º) 
}

void loop () 
{
  for (int PIR = 0; PIR < 3; PIR++) { // começa o loop para cada sensor PIR
    int PIRciclo = PIRpin[PIR]; // define o pin do PIR para o número do loop
    int LEDciclo = LEDpin[PIR]; // define o pin do LED correspondente ao PIR do loop
    PIRstatus = digitalRead(PIRciclo); // lê a informação no sensor PIR (se detetar movimento a variável PIRstatus é definida como HIGH, senão como LOW)

    if (PIRstatus == HIGH) { // se for detetado movimento no sensor
      digitalWrite(LEDciclo, HIGH); // acende o LED correspondente ao loop
      if(PIRstateprev[PIR] == 0) { // se o estado prévio do PIR for LOW
        if (PIRpinAtual != PIRciclo && PIRstateprev[PIR] == 0) { // se a posição do servo for diferente da posição correpondente ao sensor PIR do loop
          digitalWrite(2, HIGH); // acende o LED da cabeça do R2D2
          motor.write(PIRposition[PIR]); // move o servo para a posição correspondente ao sensor PIR do loop
          randomSound(); // o buzzer reproduz um som aleatório da lista de sons
          Serial.print("Ângulo da cabeça : ");
          Serial.println(PIRposition[PIR]);
          delay(50);
          digitalWrite(2, LOW); // desliga o LED da cabeça do R2D2
          PIRpinAtual = PIRciclo; // define a posição do servo como a posição correspondente ao sensor PIR
          }
        PIRstateprev[PIR] = 1; // define o estado prévio do PIR para HIGH
        } 
      }
      
    else  { // caso não seja detetado movimento no sensor
      digitalWrite(LEDciclo, LOW);  // desliga o LED correspondente ao sensor PIR
      PIRstateprev[PIR] = 0;   // define o estado prévio do PIR para LOW
      }   
    } 
}


// função na qual o buzzer reproduz um som aleatório da lista de sons
void randomSound() {
  int randNumber = random(1,6);
  switch(randNumber) {
    case 1: squeak();
    break;
    case 2: catcall();
    break;
    case 3: ohhh();
    break;
    case 4: laugh();
    break;
    case 5: r2D2();
    break;
    case 6: ariel();
    break;   
  }
}

// definição de funções para a reprodução de sons específicos
void beep (int speakerPin, float noteFrequency, long noteDuration)
{    
  int x;
  // Convert the frequency to microseconds
  float microsecondsPerWave = 1000000/noteFrequency;
  // Calculate how many HIGH/LOW cycles there are per millisecond
  float millisecondsPerCycle = 1000/(microsecondsPerWave * 2);
  // Multiply noteDuration * number or cycles per millisecond
  float loopTime = noteDuration * millisecondsPerCycle;
  // Play the note for the calculated loopTime.
  for (x=0;x<loopTime;x++)   
          {   
              digitalWrite(speakerPin,HIGH); 
              delayMicroseconds(microsecondsPerWave); 
              digitalWrite(speakerPin,LOW); 
              delayMicroseconds(microsecondsPerWave); 
          } 
}     

void r2D2(){
          beep(speakerPin, note_A7,100); //A 
          beep(speakerPin, note_G7,100); //G 
          beep(speakerPin, note_E7,100); //E 
          beep(speakerPin, note_C7,100); //C
          beep(speakerPin, note_D7,100); //D 
          beep(speakerPin, note_B7,100); //B 
          beep(speakerPin, note_F7,100); //F 
          beep(speakerPin, note_C8,100); //C 
          beep(speakerPin, note_A7,100); //A 
          beep(speakerPin, note_G7,100); //G 
          beep(speakerPin, note_E7,100); //E 
          beep(speakerPin, note_C7,100); //C
          beep(speakerPin, note_D7,100); //D 
          beep(speakerPin, note_B7,100); //B 
          beep(speakerPin, note_F7,100); //F 
          beep(speakerPin, note_C8,100); //C 
}

void ariel() {
          beep(speakerPin, note_C6,300); //C
          delay(50);
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,600); //D#
          delay(250);
          
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,300); //D#
          delay(50);
          beep(speakerPin, note_F6,600); //F
          delay(250);
          
          beep(speakerPin, note_C6,300); //C
          delay(50);
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,500); //D#
          delay(50);          
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,300); //D#
          delay(50);             
          beep(speakerPin, note_D6,300); //D
          delay(50);
          beep(speakerPin, note_Eb6,300); //D#
          delay(50);
          beep(speakerPin, note_F6,600); //F
          delay(50); 
}
 
void squeak() {
  for (int i=100; i<5000; i=i*1.45) {
    beep(speakerPin,i,60);
  }
  delay(10);
  for (int i=100; i<6000; i=i*1.5) {
    beep(speakerPin,i,20);
  }
}

void catcall() {
  for (int i=1000; i<5000; i=i*1.05) {
    beep(speakerPin,i,10);
  }
 delay(300);
 
  for (int i=1000; i<3000; i=i*1.03) {
    beep(speakerPin,i,10);
  }
  for (int i=3000; i>1000; i=i*.97) {
    beep(speakerPin,i,10);
  }
}

void ohhh() {
  for (int i=1000; i<2000; i=i*1.02) {
    beep(speakerPin,i,10);
  }
  for (int i=2000; i>1000; i=i*.98) {
    beep(speakerPin,i,10);
  }
}

void laugh() {
  for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
    for (int i=1000; i<2000; i=i*1.10) {
    beep(speakerPin,i,10);
  }
  delay(50);
  for (int i=1000; i>500; i=i*.90) {
    beep(speakerPin,i,10);
  }
  delay(50);
}




    

    



