/* PURPOSE: to detect rpm by counting pulses from encoder */

// DEFINING ARDUINO PINS
int encoder_pin_A = 3;
int encoder_pin_B = 2;
int motorA = 9;
int motorB = 10;

// DEFINING REQUIRED CONSTANTS
float currentTime = 0; 
float previousTime = 0;
int i = 0;
float pi = 22/7;
float wheel_radius = 65;
float rpm = 0;
float dist = 0;
volatile int pulse_count = 0 ;
int ppr = 515; // TOTAL PULSE COUNT PER REVOLUTION CAN BE CALCULATED USING A REPO PROVIDED

int duration = 50; //in ms


void setup() {
  
Serial.begin(9600); 
pinMode(motorA, OUTPUT); 
pinMode(motorB, OUTPUT); 
}

void loop() {
  currentTime = millis(); //initializing timer
  
  // if difference in times is greater than given duration, calculate the rpm using the pulse count and then set it to zero
  if (currentTime - previousTime > duration){
    detachInterrupt(encoder_pin_A);
    previousTime = currentTime;
    
    rpm = float(pulse_count)/float(ppr)*float(60000/duration); // Calculating rpm
    Serial.println(rpm);
    dist = float(pi*wheel_radius*rpm*float(duration)/1000); // Calculating distance travelled using wheel radius
    //Serial.println("dist "+ String(dist));
    //Serial.println(pulse_count);
    analogWrite(motorA,80);
    digitalWrite(motorB,LOW);
    pulse_count = 0;
    
  }
  attachInterrupt(digitalPinToInterrupt(encoder_pin_A), StartInterruptA, RISING); // when it gets a signal at rising edge it will call StartInterruptA() function

}

void StartInterruptA(){
    //Serial.println(digitalRead(encoder_pin_B));
    if (digitalRead(encoder_pin_B)){
      pulse_count += 1;
    }
    else{
      pulse_count -= 1;      
    }
    
}
