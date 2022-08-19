int pinos[] = {27, 26, 25, 33, 32};

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 5; i++){
    pinMode(pinos[i],INPUT_PULLUP);
  }
  

}

void loop() {
  Serial.print("sinal: ");
  for(int i = 0; i < 5; i++){
    Serial.print(digitalRead(pinos[i]));
  }
  Serial.println();


}
