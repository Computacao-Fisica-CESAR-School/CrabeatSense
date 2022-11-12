// Importa as bibliotecas necessarias
#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Define as especificações do LCD
#define col 20
#define lin 4
#define ende 0x27

//Cria a variavel LCD com suas caracteristicas
LiquidCrystal_I2C lcd(ende, col, lin);

//Diz para o arduino quais são os pinos dos sensores (Trigger, Echo)
Ultrasonic volumeSensor(12, 13);
Ultrasonic rateSensor(4, 5);
Ultrasonic jumpSensor(6, 7);
Ultrasonic nextSensor(8, 9);

//Cria a variavel para armazenar o valor do sensor
unsigned int volumeValue;
unsigned int rateValue;
unsigned int jumpValue;
unsigned int nextValue;

unsigned long tempoAnterior; //Variavel para o blink

int musicaAtual;

// Função nativa do arduino que serve para definir como o arduino irá iniciar (As alterações são feitas pelo loop())
void setup() {
  Serial.begin(9600); //Defina a taxa de frequencia para transmissão da informação Serial (Usamos isso para nos comunicar com o processing)

  lcd.init(); //Inicia o Display LCD
  lcd.clear(); //Limpa o display LCD
  lcd.backlight(); //Ativa a luz de fundo do LCD

  lcd.setCursor(0, 1); // Define o "ponteiro" de escrita do LCD para linha - 0 Coluna - 1
  lcd.print("Artista: CAMALEOA"); // Escreve a frase no LCD no local onde está seu "ponteiro"
  lcd.setCursor(0, 2);
  lcd.print("Faixa: 3 POR 10");
  

}

// Função nativa do arduino que cria um loop infinito
void loop() {

  lcd.display(); //Sempre que iniciar o loop vai ligar o Display

  musicaAtual = lerSerial(); //Função que lê as informações passadas do processing para o arduino via Serial 
  telas(musicaAtual); //Vai mostrar qual a musica está tocando no momento de acordo com a informação Serial

  // Atribui os valores lidos (.read) dos sensores para as variaveis...
  volumeValue = volumeSensor.read();
  rateValue = rateSensor.read();
  jumpValue = jumpSensor.read();
  nextValue = nextSensor.read();

  if (millis() - tempoAnterior >= 2000){ // Um temporizador, ou seja, essa condição só será verdadeira a cada 2000 milisegundos (2 segundos)
    tempoAnterior = millis();
    // ...Essas variaveis serão printadas no monitos Serial e serão lidas pelo processing
    Serial.print(volumeValue);
    Serial.print(";");
    Serial.print(rateValue);
    Serial.print(";");
    Serial.print(jumpValue);
    Serial.print(";");
    Serial.println(nextValue);

  }
  
}

// Função que lê a informação serial enviada pelo processing
int lerSerial(){
  int leitura; // Declara a variavel de leitura
  if (Serial.available() > 0){ // SE existir uma comunicação serial...
    leitura = Serial.read(); // A variavel "leitura" irá receber esse valor
  }
  return leitura; // Irá retornar o valor de leitura (na linha 51 esse valor é salvo na variavel "musicaAtual")
}

// Função que vai mostrar no lcd cada musica de acordo com a leitura Serial (Na linha 52)
void telas(int musica){
  switch (musica){
    case 0:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Artista: CAMALEOA");
      lcd.setCursor(0,2);
      lcd.print("Faixa: 3 POR 10");
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Artista: CAMALEOA");
      lcd.setCursor(0,2);
      lcd.print("Faixa: MIRAGEM");
  }
}
