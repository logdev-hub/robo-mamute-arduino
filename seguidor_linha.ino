// ----------------------------------------------------------
// Robô Mamute - Modo Seguidor de Linha
// Placa: Arduino UNO
// Driver de motor: L298N
// Sensores: 3 sensores de linha IR digitais (esq, centro, dir)
// ----------------------------------------------------------

// ------------------------ Pinos Motores -------------------
const int ENA = 5;   // Enable motor A (PWM) - lado esquerdo
const int IN1 = 6;   // IN1 L298N - motor A
const int IN2 = 7;   // IN2 L298N - motor A

const int IN3 = 8;   // IN3 L298N - motor B
const int IN4 = 9;   // IN4 L298N - motor B
const int ENB = 10;  // Enable motor B (PWM) - lado direito

// ------------------------ Pinos Sensores de Linha --------
const int SENSOR_ESQ   = A0;  // Sensor de linha esquerda
const int SENSOR_CENTRO= A1;  // Sensor de linha central
const int SENSOR_DIR   = A2;  // Sensor de linha direita

// Velocidade padrão (0 a 255)
int velocidadeBase = 150;

// Se o sensor retornar LOW sobre a linha preta, use:
const int SINAL_LINHA = LOW;
// Se o seu sensor for invertido (linha = HIGH), troque para:
// const int SINAL_LINHA = HIGH;

void setup() {
  // Configuração dos pinos dos motores
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Configuração dos sensores de linha
  pinMode(SENSOR_ESQ, INPUT);
  pinMode(SENSOR_CENTRO, INPUT);
  pinMode(SENSOR_DIR, INPUT);

  // Opcional: Serial para depuração
  Serial.begin(9600);

  parar();
}

void loop() {
  // Leitura dos sensores
  int leituraEsq    = digitalRead(SENSOR_ESQ);
  int leituraCentro = digitalRead(SENSOR_CENTRO);
  int leituraDir    = digitalRead(SENSOR_DIR);

  // Envie para o monitor serial se quiser depurar
  // Serial.print("E: "); Serial.print(leituraEsq);
  // Serial.print(" C: "); Serial.print(leituraCentro);
  // Serial.print(" D: "); Serial.println(leituraDir);

  bool esqNaLinha    = (leituraEsq    == SINAL_LINHA);
  bool centroNaLinha = (leituraCentro == SINAL_LINHA);
  bool dirNaLinha    = (leituraDir    == SINAL_LINHA);

  // Decisão de movimento
  if (centroNaLinha && !esqNaLinha && !dirNaLinha) {
    // Apenas o centro vê a linha: seguir em frente
    frente(velocidadeBase);
  } 
  else if (esqNaLinha && !centroNaLinha) {
    // Linha mais para o lado esquerdo: virar para a esquerda
    virarEsquerda(velocidadeBase);
  } 
  else if (dirNaLinha && !centroNaLinha) {
    // Linha mais para o lado direito: virar para a direita
    virarDireita(velocidadeBase);
  } 
  else {
    // Caso incerto (nenhum sensor ou todos sobre a linha): parar
    // Aqui você pode implementar alguma correção mais avançada.
    parar();
  }

  delay(10); // pequeno atraso para suavizar a leitura
}

// ------------------------ Funções de Movimento -----------

void frente(int vel) {
  // Motor esquerdo para frente
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Motor direito para frente
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void tras(int vel) {
  // Motor esquerdo para trás
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Motor direito para trás
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void virarEsquerda(int vel) {
  // Motor esquerdo para trás
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  // Motor direito para frente
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, vel);
  analogWrite(ENB, vel);
}

void virarDireita(int vel) {
  // Motor esquerdo para frente
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  // Motor direito para trás
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
