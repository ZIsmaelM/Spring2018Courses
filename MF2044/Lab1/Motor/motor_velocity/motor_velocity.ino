#define pwm_pin 7
#define pinA 2
#define pinB 3
#define timer5_pin 45
#define enable 12
#define ppr 1000

int encoderCounts = 0;
int revolutions = 0;
float velocity = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(pwm_pin, OUTPUT);
  pinMode(pinA, INPUT);
  pinMode(pinB, INPUT);
  pinMode(timer5_pin, OUTPUT);
  pinMode(enable, OUTPUT);
  digitalWrite(enable, HIGH);
  // configure PWM:
  TCCR4A = B00100011; //Mode 15, no prescaler (=1)
  TCCR4B = B00011001;
  OCR4AH = B00000001; //319 TOP value
  OCR4AL = B00111111;
  //OCR4BH = B00000000;
  //OCR4BL = B10100000;
  //OCR4A = 319;
  OCR4B = 160; // Default 50% duty cycle

  // Configure encoder interrupts
  attachInterrupt(pinA, readEncoderA, CHANGE);
  attachInterrupt(pinB, readEncoderB, CHANGE);

  // Configure timer interrupt
  TCCR5A = 0;
  TCCR5B = B00000011;
  TIMSK5 = 1;
}

void setPWM(float duty){
  OCR4B = (int)duty*319/100;
}

ISR(TIMER5_OVF_vect){
  velocity = (revolutions+(float)encoderCounts/ppr)*3.8*60;

//  if (velocity > 0) {
//   Serial.println(revolutions);   
//  }
  
  encoderCounts = 0;
  revolutions = 0;
  
}

void readEncoderA(void){
  if(digitalRead(pinA)==HIGH){
    if(digitalRead(pinB)==HIGH){ 
      encoderCounts = encoderCounts + 1; //CW
      if(encoderCounts==ppr){
        revolutions += 1;
        encoderCounts = 0;
      }
      
    }else{
      encoderCounts = encoderCounts - 1; //CCW
      if(encoderCounts==-ppr){
        revolutions -= 1;
        encoderCounts = 0;
      }
    }
  }else{
    if(digitalRead(pinB)==LOW){ 
      encoderCounts = encoderCounts + 1; //CW
      if(encoderCounts==ppr){
        revolutions += 1;
        encoderCounts = 0;
      }
    }else{
      encoderCounts = encoderCounts - 1; //CCW
      if(encoderCounts==-ppr){
        revolutions -= 1;
        encoderCounts = 0;
      }
    }
  }
  //Serial.println(encoderCounts);
}

void readEncoderB(void){
  if(digitalRead(pinB)==HIGH){
    if(digitalRead(pinA)==LOW){ 
      encoderCounts = encoderCounts + 1; //CW
      if(encoderCounts==ppr){
        revolutions += 1;
        encoderCounts = 0;
      }
    }else{
      encoderCounts = encoderCounts - 1; //CCW
      if(encoderCounts==-ppr){
        revolutions -= 1;
        encoderCounts = 0;
      }
    }
  }else{
    if(digitalRead(pinA)==HIGH){ 
      encoderCounts = encoderCounts + 1; //CW
      if(encoderCounts==ppr){
        revolutions += 1;
        encoderCounts = 0;
      }
    }else{
      encoderCounts = encoderCounts - 1; //CCW
      if(encoderCounts==-ppr){
        revolutions -= 1;
        encoderCounts = 0;
      }
    }
  }
  //Serial.println(encoderCounts);
}

void loop() {
  // put your main code here, to run repeatedly:
//  setPWM (50.0);
//  delay(1000);
//  setPWM (75.0);
//  delay(1000);
  digitalWrite(enable, LOW);
  while(Serial.available()>1){
    float dutyReceived = Serial.parseFloat();
    //Serial.println(dutyReceived);
    encoderCounts = 0;
    revolutions = 0;
    setPWM (dutyReceived);
  }
  Serial.print("encoderCounts: ");
  Serial.println(encoderCounts);
  Serial.print("Velocity: ");
  Serial.println(velocity);
  delay(2000);
}
