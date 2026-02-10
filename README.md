# Robô Mamute com Arduino UNO (L298N, HC-05, HC-SR04, Sensores de Linha)

Este repositório contém três projetos didáticos para o **robô Mamute** baseado em **Arduino UNO**, utilizando:

- Ponte H **L298N** para controle dos motores
- **Sensores de linha infravermelho** (3 módulos digitais)
- **Sensor ultrassônico HC-SR04** para detecção de obstáculos
- **Módulo Bluetooth HC-05** para controle remoto via smartphone

Os três modos de operação são:

1. **Seguidor de linha**
2. **Desvia-obstáculo**
3. **Controle por Bluetooth**

---

## 1. Hardware Utilizado

- 1 × Arduino UNO R3 (ou compatível)
- 1 × Módulo Ponte H L298N
- 2 × Motores DC com caixa de redução (chassi do robô Mamute)
- 3 × Sensores de linha IR digitais (esquerda, centro, direita)
- 1 × Sensor ultrassônico HC-SR04
- 1 × Módulo Bluetooth HC-05
- 1 × Suporte de baterias (7–12 V) + bateria(s)
- Protoboard e jumpers macho/macho, macho/fêmea
- Chassi do robô Mamute

---

## 2. Ligações Elétricas (Resumo)

### 2.1. Arduino ↔ L298N ↔ Motores

| L298N | Arduino UNO | Função                    |
|-------|-------------|---------------------------|
| ENA   | D5 (PWM)    | Enable motor A (esquerdo) |
| IN1   | D6          | Motor A entrada 1        |
| IN2   | D7          | Motor A entrada 2        |
| IN3   | D8          | Motor B entrada 1        |
| IN4   | D9          | Motor B entrada 2        |
| ENB   | D10 (PWM)   | Enable motor B (direito) |

- Motor esquerdo: OUT1 e OUT2 do L298N  
- Motor direito: OUT3 e OUT4 do L298N  

**Alimentação:**

- Bateria (7–12 V) → 12V da L298N  
- GND da bateria → GND da L298N  
- GND da L298N → GND do Arduino  
- (Opcional) 5V da L298N → 5V do Arduino, com o jumper de 5V da L298N habilitado  
  - **Nunca** use ao mesmo tempo USB + 5V da L298N no Arduino.

### 2.2. Sensores de Linha

| Sensor              | Pino Arduino |
|---------------------|-------------|
| Linha esquerda (OUT)| A0          |
| Linha centro (OUT)  | A1          |
| Linha direita (OUT) | A2          |

- Todos os VCC dos sensores → 5V  
- Todos os GND → GND  

### 2.3. Sensor Ultrassônico HC-SR04

| Pino HC-SR04 | Pino Arduino |
|--------------|-------------|
| VCC          | 5V          |
| GND          | GND         |
| TRIG         | D11         |
| ECHO         | D12         |

### 2.4. Módulo Bluetooth HC-05

Usando a biblioteca `SoftwareSerial`:

| Pino HC-05 | Pino Arduino | Observação                          |
|------------|--------------|-------------------------------------|
| VCC        | 5V           |                                     |
| GND        | GND          |                                     |
| TXD        | D2           | RX do SoftwareSerial                |
| RXD        | D3           | TX do SoftwareSerial (via divisor)  |

> Recomenda-se um divisor de tensão (por exemplo 2 kΩ e 1 kΩ) entre D3 e RXD para reduzir 5 V → ~3,3 V.

---

## 3. Estrutura do Repositório

```text
seguidor-linha/
  seguidor_linha.ino       # Código do modo seguidor de linha

desvia-obstaculo/
  desvia_obstaculo.ino     # Código do modo desvia-obstáculo (HC-SR04)

controle-bluetooth/
  controle_bluetooth.ino   # Código do modo controle por Bluetooth (HC-05)

README.md
