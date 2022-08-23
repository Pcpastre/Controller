
int pinos[4][5] = {{13, 12, 14, 27, 26},
                   {25, 33, 32, 22, 23},
                   {5, 18, 19, 21, 03},
                   {15, 2, 4, 16, 17}};

int pressed[4][5] = {{0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0},
                     {0, 0, 0, 0, 0}};

/*String comandos[4][5][2] = {
    {{"f1", "!f1"},
     {"f2", "!f2"},
     {"f3", "!f3"},
     {"f4", "!f4"},
     {"f5", "!f5"}},

    {{"f6", "!f6"},
     {"f7", "!f7"},
     {"f8", "!f8"},
     {"f9", "!f9"},
     {"f10", "!f10"}},

    {
        {"f11", "!f11"},
        {"f12", "!f12"},
        {"1", "!1"},
        {"2", "!2"},
        {"3", "!3"},
    },

    {
        {"4", "!4"},
        {"5", "!5"},
        {"6", "!6"},
        {"7", "!7"},
        {"8", "!8"},
    }

};*/
String comandos[4][5][2] = {
    {{"9", "!9"},
     {"0", "!0"},
     {"-", "!-"},
     {"=", "!="},
     {"q", "!q"}},

    {{"w", "!w"},
     {"e", "!e"},
     {"r", "!r"},
     {"t", "!t"},
     {"ip", "!ip"}},

    {
        {"u", "!u"},
        {"i", "!i"},
        {"o", "!p"},
        {"'", "!'"},
        {"[", "!["},
    },

    {
        {"a", "!a"},
        {"s", "!s"},
        {"d", "!d"},
        {"f", "!f"},
        {"g", "!g"},
    }

};

void setup()
{
  Serial.begin(115200);
  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 5; i++)
    {
      pinMode(pinos[j][i], INPUT_PULLUP);
    }
  }
}
String comand = " ";
void loop()
{
  for (int j = 0; j < 4; j++)
  {
    for (int i = 0; i < 5; i++)
    {
      if (digitalRead(pinos[j][i]) == 0 && pressed[j][i] == 0)
      {
        pressed[j][i] = 1;
        comand = comandos[j][i][0];
        Serial.println(comandos[j][i][0]);
      }
      else if (digitalRead(pinos[j][i]) == 1 && pressed[j][i] == 1)
      {
        pressed[j][i] = 0;
        comand = comandos[j][i][1];
        Serial.println(comandos[j][i][1]);
      }
      delay(1);
    }
  }
}
