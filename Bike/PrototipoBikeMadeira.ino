 //Incluindo biblioteca Ultrasonic.h
#include "Ultrasonic.h"

//criando objeto ultrasonic e definindo as portas digitais
//do Trigger - 4 - e Echo - 3
Ultrasonic ultrasonic(4, 3);

//Declaração das constantes referentes aos pinos digitais.
const int rgbR = 5;
const int rgbG = 6;
const int rgbB = 7;
const int ledTras1 = 8;
const int ledTras2 = 9;
const int ledTras3 = 10;
const int ledFrente1 = 11;
const int ledFrente2 = 12;
const int ledVermelho1 = 53;
const int ledVermelho2 = 52;
const int ledLaranja = 51;
const int ledAmarelo = 50;
const int ledBaixo1 = 22;
const int ledBaixo2 = 49;
//const int pinBotao = 47;

int sensor = 0;      //Pino analógico em que o sensor está conectado.
int valorSensor = 0; //Usada para ler o valor do sensor em tempo real.
long microsec = 0;
float distanciaCM = 0;

int var = 0;       // valor instantaneo enviado pelo botão
int var2 = 0;     // valor guardado
int estadoBotao = 0;
char readBluetooth;//Variável que irá receber o valor enviado do celular para o bluetooth

void setup() {
  Serial.begin(9600); //Inicializando o serial monitor

  //Definindo pinos digitais
  pinMode(rgbR, OUTPUT);
  pinMode(rgbG, OUTPUT);
  pinMode(rgbB, OUTPUT);
  pinMode(ledTras1, OUTPUT);
  pinMode(ledTras2, OUTPUT);
  pinMode(ledTras3, OUTPUT);
  pinMode(ledFrente1, OUTPUT);
  pinMode(ledFrente2, OUTPUT);
  pinMode(ledVermelho1, OUTPUT);
  pinMode(ledVermelho2, OUTPUT);
  pinMode(ledLaranja, OUTPUT);
  pinMode(ledAmarelo, OUTPUT);
  pinMode(ledBaixo1, OUTPUT);
  pinMode(ledBaixo2, OUTPUT);
}


void loop() {
  lerSensorLum();
  verificaDistancia();
  readBluetooth = Serial.read();  //Valor lido na Serial será guardado na variável readBluetooth
  ler(readBluetooth);
  Serial.println(distanciaCM);
  delay(25);
}

void ler(char valor) {
  
      switch (valor) {
        case 'a':
          //ativa barra luminosidade (desativa o uso do sensor de luminosidade)
          digitalWrite(ledBaixo1, HIGH);
          digitalWrite(ledBaixo2, HIGH);
          break;
        case 'x':
          //desativa barra luminosidade (ativa o uso do sensor de luminosidade)
          digitalWrite(ledBaixo1, LOW);
          digitalWrite(ledBaixo2, LOW);
          break;
      }
}

void lerSensorLum() {
  //Lendo o valor do sensor de luminosidade.
  valorSensor = analogRead(sensor);

  //Valores da luminosidade podem ser alterados conforme necessidade.

  //Luminosidade baixa.
  if (valorSensor < 750) {
    acenderLedsLum();
  } else {
    apagarLedsLum();
  }
}

void verificaDistancia() {

  //desligaAlerta();                //Desliga a alerta

  //lendo sensor ultra-sônico
  distanciaCM = lerSensorUltra();
  
  //Acendendo o led adequado para a distância lida no sensor
  if (distanciaCM <= 150 && distanciaCM > 110) {
    digitalWrite(ledAmarelo, HIGH);                        //Liga o primeiro Led
    digitalWrite(ledVermelho1, LOW);
    digitalWrite(ledVermelho2, LOW);
    digitalWrite(ledLaranja, LOW);
  }
  else if (distanciaCM <= 110 && distanciaCM > 80) {
    digitalWrite(ledAmarelo, HIGH);                         //Liga o primeiro Led
    digitalWrite(ledLaranja, HIGH);                         //Liga o segundo Led
    digitalWrite(ledVermelho1, LOW);
    digitalWrite(ledVermelho2, LOW);

  }
  else if (distanciaCM <= 80 && distanciaCM >= 50) {
    digitalWrite(ledAmarelo, HIGH);                         //Liga o primeiro Led
    digitalWrite(ledLaranja, HIGH);                         //Liga o segundo Led
    digitalWrite(ledVermelho2, HIGH);                       //Liga o terceiro Led
    digitalWrite(ledVermelho1, LOW);
  }
  else if (distanciaCM < 50 && distanciaCM > 5) {
    //Liga a alerta
    alerta();
  } else {
    desligaAlerta();
  }
}

//Leitura do sensor
float lerSensorUltra() {
  //Lendo o sensor
  microsec = ultrasonic.timing();
  //Serial.print("OK:");
  //Serial.println(ultrasonic.convert(microsec, Ultrasonic::CM));
  //Convertendo a distância em CM
  return ultrasonic.convert(microsec, Ultrasonic::CM);
}

//Metodo que faz alerta
void alerta() {
  ligaAlerta();
  delay(200);
  desligaAlerta();
  delay(200);
  lerSensorUltra();
}

//Acende os leds superiores
void ligaAlerta() {
  digitalWrite(ledVermelho1, HIGH);
  digitalWrite(ledVermelho2, HIGH);
  digitalWrite(ledLaranja, HIGH);
  digitalWrite(ledAmarelo, HIGH);

}

//Apaga os leds superiores
void desligaAlerta() {
  digitalWrite(ledVermelho1, LOW);
  digitalWrite(ledVermelho2, LOW);
  digitalWrite(ledLaranja, LOW);
  digitalWrite(ledAmarelo, LOW);
}

//Acende os leds da bicicleta
void acenderLedsLum() {
  digitalWrite(ledFrente1, HIGH);
  digitalWrite(ledFrente2, HIGH);
  digitalWrite(ledTras1, HIGH);
  digitalWrite(ledTras2, HIGH);
  digitalWrite(ledTras3, HIGH);
  analogWrite(rgbR, 255);
  analogWrite(rgbG, 255);
  analogWrite(rgbB, 255);
}

//Apaga os leds da bicicleta
void apagarLedsLum() {
  digitalWrite(ledFrente1, LOW);
  digitalWrite(ledFrente2, LOW);
  digitalWrite(ledTras1, LOW);
  digitalWrite(ledTras2, LOW);
  digitalWrite(ledTras3, LOW);
  analogWrite(rgbR, 0);
  analogWrite(rgbG, 0);
  analogWrite(rgbB, 0);
}

