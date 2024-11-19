#include <Keypad.h>

char* senha = "ABC123";

const byte LINHAS = 4;
const byte COLUNAS = 4;

char digitos[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinosLinha[LINHAS] = { 11, 10, 9, 8 };
byte pinosColuna[COLUNAS] = { 7, 6, 5, 4 };

Keypad keypad = Keypad( makeKeymap(digitos), pinosLinha, pinosColuna, LINHAS, COLUNAS );

int position = 0;
int ledVermelho = 12;
int ledVerde = 13;
int releFechadura = 3;
int tempoAberto = 2000;

void setup(){ 
  estadoPorta(true);
  pinMode(ledVermelho,OUTPUT); 
  pinMode(ledVerde,OUTPUT);
  pinMode(releFechadura,OUTPUT);

};

void loop(){
  char digito = keypad.getKey();

  if (digito !=0){
    
    if (digito == senha[position]){
      position ++;
    } else {
      position = 0;
    } ;
    
    if (position == 6){
      estadoPorta(false);
    };
    delay(100);
  };
};

void estadoPorta(int trancado){
  
  if (trancado){
    digitalWrite(ledVermelho, HIGH);
    digitalWrite(ledVerde, LOW);
    digitalWrite(releFechadura, LOW);
  } else {
    digitalWrite(ledVermelho, LOW);
    digitalWrite(ledVerde, HIGH);
    digitalWrite(releFechadura, HIGH);
    delay(tempoAberto);
    position = 0;
    digitalWrite(releFechadura, LOW);
    estadoPorta(true);
  };
};
