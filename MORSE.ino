/**
 * This project works with four buttons.
 * You only need download this code from Github and finally load them into the Arduino.
 * Electrical mounting can be found on the internet. You only need browse "Arduino button installation" and "Arduino led installation".
 * 
 * Button 1 -> For type the point (.).
 * Button 2 -> For type the stripe (-).
 * Button 3 -> For accept the word, like enter key :)
 * Button 4 -> For clear the morse words and normal workds.
 */
const String abecedario[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", " "}; //Declare a normal alphabet
const String abecedarioMorse[] = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..", "----"}; //Declare a morse aplhabet.

//Buttons consts
const int PUNTO = 3; //Variable to declare point button. (DIGITAL PIN 3)
const int RAYA = 5; //Variable to declare stripe button. (DIGITAL PIN 5)
const int ESPACIO = 6; //Variable to declare OK button. (DIGITAL PIN 6 )
const int BORRAR = 9; //Variable to decleare clear all button. (DIGITAL PIN 9)

//Led consts
const int ROJO = 10;  //Variable to declare red led (DIGITAL PIN 10)
const int VERDE = 11; //Variable to declare green led (DIGITAL PIN 11)

//Auxiliary but required variables.
String morseComb = "";
String alfComb = "";

//This whill be executed when Arduino board starts.
void setup() 
{
  Serial.begin(9600); //Set the data transfer limit

  //Start button data type declarations.
  pinMode(PUNTO, INPUT);
  pinMode(RAYA, INPUT);
  pinMode(ESPACIO, INPUT);
  pinMode(BORRAR, INPUT);

  //Declare led data type declarations.
  pinMode(ROJO, OUTPUT);
  pinMode(VERDE, OUTPUT);
}

//This whill be executed when Arduino board already started. This is a infinite loop. Like while(true)
void loop()
{
  //Read inputs from buttons. If button are pressed will be return a logical 1 but, when button are not pressed it will returns a logical 0.
  const int pto = digitalRead(PUNTO); //Input from point button.
  const int rya = digitalRead(RAYA); //Input from stripe button.
  const int ok = digitalRead(ESPACIO); //Input from ok button.
  const int clr = digitalRead(BORRAR); //Input from clear-all button.

  //HIGH = 1 and LOW = 0
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

