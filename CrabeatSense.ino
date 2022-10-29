#include <Ultrasonic.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define col 20
#define lin 4
#define ende 0x27

LiquidCrystal_I2C lcd(ende, col, lin);

Ultrasonic volumeSensor(12, 13);
Ultrasonic rateSensor(4, 5);
Ultrasonic jumpSensor(6, 7);
Ultrasonic nextSensor(8, 9);

unsigned int volumeValue;
unsigned int rateValue;
unsigned int jumpValue;
unsigned int nextValue;

unsigned long previousMillis = 0; //Variavel para o blink
const  long interval == 2000;

int musica = 1;

void setup() {
  Serial.begin(9600);

  lcd.init();
  lcd.clear();
  lcd.backlight();

  lcd.setCursor(0, 1);
  lcd.print("Artista: CAMALEOA");
  lcd.setCursor(0, 2);
  lcd.print("Faixa: MIRAGEM");
  

}

void loop() {

  unsigned long currentMillis = millis();

  lcd.display();

  
  volumeValue = volumeSensor.read();
  rateValue = rateSensor.read();
  jumpValue = jumpSensor.read();
  nextValue = nextSensor.read();

  if (currentMillis - previousMillis >= interval){
    previousMillis = currentMillis;

    if (nextValue <= 10){
      if (musica == 1){
        musica = 2;
        lcd.clear();
  
        lcd.setCursor(0, 1);
        lcd.print("Artista: CAMALEOA");
        lcd.setCursor(0, 2);
        lcd.print("Faixa: 3 POR 10");
    }else{
      musica = 1;
      lcd.clear();
    
      lcd.setCursor(0, 1);
      lcd.print("Artista: CAMALEOA");
      lcd.setCursor(0, 2);
      lcd.print("Faixa: MIRAGEM");
    }
    }
  }

  Serial.print(volumeValue);
  Serial.print(";");
  Serial.print(rateValue);
  Serial.print(";");
  Serial.print(jumpValue);
  Serial.print(";");
  Serial.println(nextValue);

  delay(300);
}
