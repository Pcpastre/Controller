int pinos[2][5] = {{27, 26, 25, 33, 32},
                   {27, 26, 25, 33, 32}};
                   
int pressed[2][5] = {{0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0}};


String comandos[2][5][2] = {
  {{"f1","!f1"},
  {"f2","!f2"},
  {"f3","!f3"},
  {"f4","!f4"},
  {"f5","!f5"}},
  
  {{"d","!d"},
  {"s","!s"},
  {"a","!a"},
  {"f","!f"},
  {"g","!g"}}
  
};

void setup() {
  Serial.begin(115200);
  for(int i = 0; i < 5; i++){
    pinMode(pinos[0][i],INPUT_PULLUP);
  }
  

}
String comand=" ";
void loop() {
      for(int i = 0; i < 5; i++){
        if(digitalRead(pinos[0][i]) == 0 && pressed[0][i] == 0){
             pressed[0][i] = 1;
             comand = comandos[0][i][0];
             Serial.println(comandos[0][i][0]);
            
        }else if(digitalRead(pinos[0][i]) == 1 && pressed[0][i] == 1){
            pressed[0][i] = 0;
            comand = comandos[0][i][1];
            Serial.println(comandos[0][i][1]);
        }   
    }
}
