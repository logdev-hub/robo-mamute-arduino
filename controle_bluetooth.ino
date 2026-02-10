// ----------------------------------------------------------
// Robô Mamute - Modo Controle via Bluetooth
// Placa: Arduino UNO
// Driver de motor: L298N
// Módulo: HC-05 (SoftwareSerial nos pinos 2 e 3)
// ----------------------------------------------------------

#include <SoftwareSerial.h>

// RX do Arduino (pino que RECEBE do HC-05) -> ligado ao TXD do HC-05
// TX do Arduino (pino que ENVIA para o HC-05) -> ligado ao RXD do HC-05 (via divisor de tensão)
SoftwareSerial bt(2, 3); // (RX, TX)

// ------------------------ Pinos Motores -------------------
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 7;

const int IN3 = 8;
const int IN4 = 9;
const int ENB = 10;

// Velocidade padrão
int velocidade = 180;

void setup() {
  // Motores
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Comunicação Serial via USB (debug) e via Bluetooth
  Serial.begin(9600);
  bt.begin(9600); // Baudrate padrão do HC-05 (geralmente 9600)

  parar();

  Serial.println("Robô Mamute - Controle Bluetooth iniciado.");
  Serial.println("Comandos: F=frente, B=tras, L=esq, R=dir, S=stop.");
}

void loop() {
  // Se chegar dado do Bluetooth
  if (bt.available() > 0) {
    char comando = bt.read();
    Serial.print("Comando recebido: ");
    Serial.println(comando);

    processarComando(comando);
  }

  // Opcional: ler também da Serial USB (para testar pelo PC)
  if (Serial.available() > 0) {
    char comandoPC = Serial.read();
    processarComando(comandoPC);
  }
}

// ------------------------ Processamento de Comandos -------

void processarComando(char c) {
  switch (c) {
    case 'F':  // Frente
    case 'f':
      frente(velocidade);
      break;

    case 'B':  // Trás
    case 'b':
      tras(velocidade);
      break;

    case 'L':  // Esquerda
    case 'l':
      virarEsquerda(velocidade);
      break;

    case 'R':  // Direita
    case 'r':
      virarDireita(velocidade);
      break;

    case 'S':  // Stop
    case 's':
      parar();
      break;

    case '+':  // Aumenta velocidade
      velocidade += 10;
      if (velocidade > 255) velocidade = 255;
      Serial.print("Velocidade: ");
      Serial.println(velocidade);
      break;

    case '-':  // Diminui velocidade
      velocidade -= 10;
      if (velocidade < 0) velocidade = 0;
      Serial.print("Velocidade: ");
      Serial.println(velocidade);
      break;

    default:
      // Comando desconhecido -> opcionalmente parar
      // parar();
      break;
  }
}

// ------------------------ Funções de Movimento ------------

void frente(int vel) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void tras(int vel) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void virarEsquerda(int vel) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void virarDireita(int vel) {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void parar() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
