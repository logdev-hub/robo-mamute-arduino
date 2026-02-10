// ----------------------------------------------------------
// Robô Mamute - Modo Desvia-Obstáculo
// Placa: Arduino UNO
// Driver de motor: L298N
// Sensor: HC-SR04 (fixo na frente do robô)
// ----------------------------------------------------------

// ------------------------ Pinos Motores -------------------
const int ENA = 5;
const int IN1 = 6;
const int IN2 = 7;

const int IN3 = 8;
const int IN4 = 9;
const int ENB = 10;

// ------------------------ Pinos Ultrassônico -------------
const int TRIG_PIN = 11;
const int ECHO_PIN = 12;

// ------------------------ Parâmetros do robô -------------
int velocidadeFrente   = 180;    // Velocidade para andar em frente
int velocidadeManobra  = 170;    // Velocidade para manobrar
int distanciaSeguraCM  = 20;     // Distância mínima em cm
int tempoRe            = 300;    // Tempo de ré (ms)
int tempoCurva         = 400;    // Tempo da curva (ms)

void setup() {
  // Motores
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Ultrassônico
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.begin(9600);

  parar();
}

void loop() {
  long distancia = medirDistanciaCM();

  Serial.print("Distancia: ");
  Serial.print(distancia);
  Serial.println(" cm");

  if (distancia > 0 && distancia <= distanciaSeguraCM) {
    // Obstáculo muito perto -> manobra
    parar();
    delay(100);

    // Dá uma pequena ré
    tras(velocidadeManobra);
    delay(tempoRe);

    parar();
    delay(100);

    // Vira para a esquerda (poderia alternar ou sortear o lado)
    virarEsquerda(velocidadeManobra);
    delay(tempoCurva);

    parar();
    delay(100);
  } else {
    // Caminho livre -> segue em frente
    frente(velocidadeFrente);
  }

  delay(50);
}

// ------------------------ Medição Ultrassônica ------------

// Mede a distância em centímetros usando o HC-SR04
long medirDistanciaCM() {
  // Garante TRIG em nível baixo
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);

  // Pulso de 10 microssegundos em TRIG
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Mede o tempo do pulso em ECHO
  long duracao = pulseIn(ECHO_PIN, HIGH, 30000UL); // timeout de ~30ms (cerca de 5m)

  if (duracao == 0) {
    // Se der timeout, retorna -1 (sem leitura confiável)
    return -1;
  }

  // Conversão para cm: velocidade do som ~340 m/s
  long distancia = duracao / 58; // Fórmula aproximada: cm = microsegundos / 58

  return distancia;
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
