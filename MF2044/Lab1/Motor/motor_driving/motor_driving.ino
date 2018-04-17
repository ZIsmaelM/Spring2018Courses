void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  TCCR4A = B00100011; //Mode 15, no prescaler (=1)
  TCCR4B = B00011001;
  OCR4AH = B00000001; //319 TOP value
  OCR4AL = B00111111;
  //OCR4BH = B00000000;
  //OCR4BL = B10100000;
  //OCR4A = 319;
  OCR4B = 160; // Default 50% duty cycle

}

void setPWM(float duty){
  OCR4B = (int)duty*319/100;
}

void loop() {
  // put your main code here, to run repeatedly:
//  setPWM (50.0);
//  delay(1000);
//  setPWM (75.0);
//  delay(1000);

  while(Serial.available()>1){
    float dutyReceived = Serial.parseFloat();
    Serial.println(dutyReceived);
    setPWM (dutyReceived);
  }
}
