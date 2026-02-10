# 🤖 Robô Mamute com Arduino UNO

Robô didático baseado em **Arduino UNO**, utilizando:

- Ponte H **L298N** para controle dos motores DC  
- **Sensores de linha infravermelho** (3 módulos digitais) para seguir trajetos em linha  
- **Sensor ultrassônico HC-SR04** para desvio de obstáculos  
- **Módulo Bluetooth HC-05** para controle remoto via smartphone  

Este repositório contém **três modos de operação** para o robô Mamute:

1. 🧭 Seguidor de linha  
2. 🚧 Desvia-obstáculo  
3. 📱 Controle por Bluetooth  

---

## 📚 Sumário

- [🎯 Objetivo do Projeto](#-objetivo-do-projeto)
- [🧩 Hardware Utilizado](#-hardware-utilizado)
- [🔌 Ligações Elétricas (Base Comum)](#-ligações-elétricas-base-comum)
  - [Arduino ↔ L298N ↔ Motores](#arduino--l298n--motores)
  - [Sensores de Linha](#sensores-de-linha)
  - [Sensor Ultrassônico HC-SR04](#sensor-ultrassônico-hc-sr04)
  - [Módulo Bluetooth HC-05](#módulo-bluetooth-hc-05)
- [📁 Estrutura do Repositório](#-estrutura-do-repositório)
- [🧭 Projeto 1 – Seguidor de Linha](#-projeto-1--seguidor-de-linha)
  - [Descrição](#descrição)
  - [Funcionamento](#funcionamento)
  - [Passo a passo](#passo-a-passo)
  - [Código-fonte](#código-fonte)
- [🚧 Projeto 2 – Robô Desvia-Obstáculo](#-projeto-2--robô-desvia-obstáculo)
  - [Descrição](#descrição-1)
  - [Funcionamento](#funcionamento-1)
  - [Passo a passo](#passo-a-passo-1)
  - [Código-fonte](#código-fonte-1)
- [📱 Projeto 3 – Robô Controlado por Bluetooth](#-projeto-3--robô-controlado-por-bluetooth)
  - [Descrição](#descrição-2)
  - [Funcionamento](#funcionamento-2)
  - [Passo a passo](#passo-a-passo-2)
  - [Código-fonte](#código-fonte-2)
- [🛠 Dicas de Ajustes e Extensões](#-dicas-de-ajustes-e-extensões)
- [📜 Licença](#-licença)
- [👨‍🏫 Créditos](#-créditos)

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

## 🎯 Objetivo do Projeto

Este projeto foi criado para uso em aulas de **robótica e Arduino**, permitindo que estudantes explorem conceitos de eletrônica básica, sensores, atuadores e comunicação sem fio de forma prática e visual.  
Cada modo de operação é um projeto independente, mas todos compartilham a mesma base de hardware para facilitar a montagem em sala de aula.

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

## 🧩 Hardware Utilizado

- 1 × Arduino **UNO R3** (ou compatível)  
- 1 × Módulo **Ponte H L298N**  
- 2 × Motores DC com caixa de redução (chassi do robô Mamute)  
- 3 × Sensores de linha IR digitais (esquerda, centro, direita)  
- 1 × Sensor ultrassônico **HC-SR04**  
- 1 × Módulo Bluetooth **HC-05**  
- 1 × Suporte de baterias (7–12 V) + baterias  
- Protoboard e jumpers macho/macho, macho/fêmea  
- Chassi do robô Mamute (similar a kits de carro robô 2WD/4WD)  

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

## 🔌 Ligações Elétricas (Base Comum)

Esta seção descreve a **base comum de hardware** usada pelos três projetos, combinando Arduino UNO, L298N e um chassi de robô com motores DC.  
A partir dela, cada modo adiciona apenas os sensores necessários (linha, ultrassônico ou Bluetooth).

### Arduino ↔ L298N ↔ Motores

| L298N | Arduino UNO | Função                          |
|-------|-------------|---------------------------------|
| ENA   | D5 (PWM)    | Enable motor A (esquerdo)       |
| IN1   | D6          | Motor A entrada 1               |
| IN2   | D7          | Motor A entrada 2               |
| IN3   | D8          | Motor B entrada 1               |
| IN4   | D9          | Motor B entrada 2               |
| ENB   | D10 (PWM)   | Enable motor B (direito)        |

- **OUT1/OUT2** → motor esquerdo  
- **OUT3/OUT4** → motor direito  

**Alimentação:**

- Bateria (7–12 V) → borne **12V** da L298N  
- GND da bateria → **GND** da L298N  
- GND da L298N → **GND do Arduino** (GND comum)  
- Opcional: 5V da L298N → 5V do Arduino (com jumper 5V da L298N habilitado)  
  - Não usar **USB + 5V externo** ao mesmo tempo no Arduino por segurança elétrica.  

### Sensores de Linha

| Sensor              | Pino Arduino |
|---------------------|-------------|
| Linha esquerda (OUT)| A0          |
| Linha centro (OUT)  | A1          |
| Linha direita (OUT) | A2          |

- VCC de todos os sensores → 5V do Arduino  
- GND de todos os sensores → GND comum  

Sensores de linha IR digitais são amplamente usados para seguir trilhas pretas em fundo branco, comparando leituras dos sensores para decidir a direção do robô.  

### Sensor Ultrassônico HC-SR04

| Pino HC-SR04 | Pino Arduino |
|--------------|-------------|
| VCC          | 5V          |
| GND          | GND         |
| TRIG         | D11         |
| ECHO         | D12         |

O HC-SR04 mede a distância por tempo de voo do som, e é muito utilizado em robôs de desvio de obstáculos com Arduino UNO e L298N.  

### Módulo Bluetooth HC-05

Usando `SoftwareSerial` para não travar a porta Serial principal:

| Pino HC-05 | Pino Arduino | Observação                            |
|------------|--------------|---------------------------------------|
| VCC        | 5V           | Alimentação do módulo                 |
| GND        | GND          | Referência comum                      |
| TXD        | D2           | RX do SoftwareSerial                  |
| RXD        | D3           | TX do SoftwareSerial (via divisor)    |

Projetos de carrinho robô controlado por Bluetooth costumam usar o HC-05 com comandos simples enviados por apps Android, como letras para frente, ré, esquerda e direita.  
É recomendável usar um divisor de tensão simples no pino RXD do HC-05 para reduzir o nível lógico de 5 V para cerca de 3,3 V.  

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---


- [🔗 Ver projeto Seguidor de Linha](#-projeto-1--seguidor-de-linha)  
- [🔗 Ver projeto Desvia-Obstáculo](#-projeto-2--robô-desvia-obstáculo)  
- [🔗 Ver projeto Controle por Bluetooth](#-projeto-3--robô-controlado-por-bluetooth)

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

## 🧭 Projeto 1 – Seguidor de Linha

### Descrição

Neste modo, o robô **segue uma linha** (geralmente preta em fundo branco) utilizando três sensores de linha IR posicionados na parte frontal do chassi.  
É um clássico projeto introdutório de robótica móvel, ideal para ensinar lógica condicional e leitura de sensores digitais.

### Funcionamento

- Sensor central detecta a linha → robô segue em frente.  
- Sensor esquerdo detecta a linha → robô corrige para a esquerda.  
- Sensor direito detecta a linha → robô corrige para a direita.  
- Caso nenhum (ou todos) detectem linha, o robô pode parar ou executar uma estratégia de correção simples, como parar ou procurar a linha.  

### Passo a passo

1. Monte a base: Arduino + L298N + motores + alimentação.  
2. Conecte os 3 sensores de linha conforme a seção de **Sensores de Linha**.  
3. Ajuste, se necessário, o potenciômetro dos módulos de linha para calibrar o limiar de detecção (preto/branco).  
4. Abra a pasta `seguidor-linha/`.  
5. Abra o arquivo `seguidor_linha.ino` no Arduino IDE.  
6. Carregue o código no Arduino UNO.  
7. Monte uma pista com fita isolante preta sobre fundo branco e coloque o robô sobre a linha.  

### Diagrama de ligação (Fritzing)

(em construção ...)

### Código-fonte

- 📂 Ver arquivo: `seguidor-linha/seguidor_linha.ino`

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

## 🚧 Projeto 2 – Robô Desvia-Obstáculo

### Descrição

Neste modo, o robô anda em frente e **desvia automaticamente de obstáculos** usando o sensor ultrassônico HC-SR04 montado na parte frontal.  
É um exemplo típico de robô autônomo que reage ao ambiente com base em medições de distância.

### Funcionamento

- O robô mede constantemente a distância até o objeto à frente usando o HC-SR04.  
- Se a distância for maior que um valor configurado (por exemplo, 20 cm), o robô continua em frente.  
- Se um obstáculo estiver mais perto que o limiar:
  - O robô para.  
  - Dá uma pequena ré para ganhar espaço de manobra.  
  - Vira para um lado (por exemplo, esquerda) por um intervalo de tempo determinado.  
  - Volta a seguir em frente, repetindo o ciclo.  

### Passo a passo

1. Monte a base: Arduino + L298N + motores + alimentação.  
2. Conecte o HC-SR04 conforme a seção **Sensor Ultrassônico HC-SR04**.  
3. Fixe o HC-SR04 na frente do robô, apontado para frente.  
4. Abra a pasta `desvia-obstaculo/`.  
5. Abra o arquivo `desvia_obstaculo.ino` no Arduino IDE.  
6. Carregue o código no Arduino UNO.  
7. Ajuste no código, se necessário:
   - `distanciaSeguraCM` (limiar de detecção em cm).  
   - Tempos de ré (`tempoRe`) e curva (`tempoCurva`) para o seu chassi.  
8. Ligue a alimentação e teste o robô em um ambiente com paredes, caixas ou obstáculos variados.  

### Diagrama de ligação (Fritzing)

```text
(em construção ...)
```

(Insira aqui a imagem correspondente exportada do Fritzing.)

### Código-fonte

- 📂 Ver arquivo: `desvia-obstaculo/desvia_obstaculo.ino`

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

## 📱 Projeto 3 – Robô Controlado por Bluetooth

### Descrição

Neste modo, o robô é controlado via **smartphone** usando o módulo Bluetooth HC-05 e um aplicativo de terminal ou controle Bluetooth.  
Esse tipo de projeto é comum em carrinhos robôs educacionais e mostra, na prática, como integrar comunicação sem fio com controle de motores.  

### Funcionamento

O aplicativo envia caracteres simples que o Arduino interpreta como comandos:

- `F` / `f` → Frente  
- `B` / `b` → Ré  
- `L` / `l` → Esquerda  
- `R` / `r` → Direita  
- `S` / `s` → Parar  
- `+` → Aumentar velocidade  
- `-` → Diminuir velocidade  

Comandos baseados em caracteres são comuns em projetos de robô Bluetooth por serem fáceis de transmitir e interpretar no código Arduino.  

### Passo a passo

1. Monte a base: Arduino + L298N + motores + alimentação.  
2. Conecte o módulo HC-05 conforme a seção **Módulo Bluetooth HC-05**, incluindo o divisor de tensão no RXD.  
3. Abra a pasta `controle-bluetooth/`.  
4. Abra o arquivo `controle_bluetooth.ino` no Arduino IDE.  
5. Carregue o código no Arduino UNO.  
6. No celular:
   - Ative o Bluetooth.  
   - Pareie com o **HC-05** (senha padrão: `1234` ou `0000`).  
   - Abra um app de terminal/controle Bluetooth (por exemplo, um app genérico de "Bluetooth Terminal").  
   - Conecte ao HC-05 e envie os comandos (`F`, `B`, `L`, `R`, `S`, `+`, `-`).  

### Diagrama de ligação (Fritzing)

```text
controle-bluetooth/controle_bluetooth_fritzing.png
```

(em construção ...)

### Código-fonte

- 📂 Ver arquivo: `controle-bluetooth/controle_bluetooth.ino`

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

## 🛠 Dicas de Ajustes e Extensões

### Ajustes Comuns

- **Se o robô "puxa" para um lado:**
  - Ajuste a velocidade de cada motor separadamente no código, alterando os valores de PWM para ENA e ENB.  
  
- **Se os sensores de linha estiverem invertidos (linha = HIGH em vez de LOW):**
  - Ajuste a lógica no código do seguidor de linha, invertendo a condição de detecção.  
  
- **Se o Bluetooth não conectar:**
  - Verifique o baud rate configurado (em geral `9600` para HC-05).  
  - Confirme se o divisor de tensão no RXD está corretamente montado.  

### Extensões Sugeridas

- Implementar um controle de **PID simples** no seguidor de linha para tornar o movimento mais suave.  
- Combinar Bluetooth com modo autônomo (ex.: comando no app para trocar o modo de operação).  
- Enviar leituras de sensores em tempo real via Bluetooth para o celular (telemetria básica).  
- Usar um sensor de distância duplo para detecção de obstáculos mais precisa.  
- Integrar um servo motor para rotacionar o sensor ultrassônico e mapear o ambiente.  

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

## 📜 Licença

Este projeto é disponibilizado sob a licença **MIT**.

Você é livre para:
- Usar, copiar, modificar e distribuir este projeto  
- Usar em projetos comerciais ou educacionais  

Sob a condição de:
- Incluir o aviso de copyright e licença em cópias ou partes substanciais do código  

Para mais informações, consulte o arquivo LICENSE (se presente) ou acesse: https://opensource.org/licenses/MIT

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

## 👨‍🏫 Créditos

Projeto didático desenvolvido para uso em atividades educacionais de robótica, programação e automação com o **robô Mamute** e **Arduino UNO**.  

**Inspirado em:**
- Projetos de carros robôs com Arduino na Arduino Project Hub  
- Documentação oficial do Arduino UNO e módulos periféricos  
- Comunidade maker e educacional mundial  

**Componentes utilizados:**
- Arduino UNO (Arduino CC)  
- L298N Motor Driver (Disponível em kits robóticos diversos)  
- HC-SR04 Ultrasonic Sensor  
- HC-05 Bluetooth Module  
- Sensores de Linha Infravermelhos (IR)  

**Desenvolvido com fins educacionais por:**
Leandro Pereira
---

## 📞 Suporte e Contribuições

Se encontrar problemas ou quiser contribuir com melhorias:

1. Abra uma **Issue** no repositório descrevendo o problema.  
2. Envie um **Pull Request** com suas melhorias.  
3. Compartilhe sugestões e ideias para extensões do projeto.  

---

## 🔗 Links Úteis

- [Arduino Official Site](https://www.arduino.cc)  
 

[⬆️ Voltar ao topo](#-robô-mamute-com-arduino-uno)

---

**Última atualização:** Fevereiro de 2026  
**Versão:** 1.0  
