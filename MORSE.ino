const String abecedario[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", " "};
const String abecedarioMorse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "----"};

const int PUNTO = 3;
const int RAYA = 5;
const int ESPACIO = 6;
const int BORRAR = 9;

const int ROJO = 10;
const int VERDE = 11;

String morseComb = "";
String alfComb = "";

void setup() 
{
  Serial.begin(9600);
  
  pinMode(LED_BUILTIN, OUTPUT);
  
  pinMode(PUNTO, INPUT);
  pinMode(RAYA, INPUT);
  pinMode(ESPACIO, INPUT);
  pinMode(BORRAR, INPUT);

  pinMode(ROJO, OUTPUT);
  pinMode(VERDE, OUTPUT);
}

void loop()
{
  const int pto = digitalRead(PUNTO);
  const int rya = digitalRead(RAYA);
  const int ok = digitalRead(ESPACIO);
  const int clr = digitalRead(BORRAR);

  if (pto == HIGH)
  {
    morseComb += ".";
    delay(200);
  }
  if (rya == HIGH)
  {
    morseComb += "-";
    delay(200);
  }
  if (ok == HIGH)
  {
    int encontrado = 0;
    for (int i=0; i<sizeof(abecedarioMorse); i++)
    {
      if (abecedarioMorse[i].equals(morseComb))
      {
        alfComb = abecedario[i];
        morseComb = "";
        encontrado = 1;
        break;
      }
    }

    if (encontrado == 1)
    {
      ledAux(VERDE, HIGH, 500);
      ledAux(VERDE, LOW, 2);
      Serial.print(alfComb);
      delay(200);
    }
    else
    {
      ledAux(ROJO, HIGH, 150);
      ledAux(ROJO, LOW, 100);
      ledAux(ROJO, HIGH, 150);
      ledAux(ROJO, LOW, 100);
      morseComb = "";
    }
  }
  if (clr == HIGH)
  {
    morseComb = "";
    alfComb = "";
    Serial.print(alfComb);
    delay(200);
    ledAnimacion();
  }
}

void ledAnimacion()
{
  for (int i=0; i<5; i++)
  {
    ledAux(VERDE, HIGH, 100);
    ledAux(ROJO, HIGH, 100);
    ledAux(VERDE, LOW, 100);
    ledAux(ROJO, LOW, 100);
  }
}

void ledAux(int led, int value, int tiempo)
{
  digitalWrite(led, value);
  delay(tiempo);
}

