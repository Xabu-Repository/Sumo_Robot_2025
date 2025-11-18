// DEFINIÇÃO -- SENSORES DE OBSTÁCULO
const int sensorDir  = A4;  
const int sensorMeio = A5;   
const int sensorEsq  = A6;   

// DEFINIÇÃO -- SENSORES DE LINHA
const int linhaDir = A0;     
const int linhaEsq = A3;     

// DEFINIÇÃO -- LIMITES DE LINHA
int limiteLinha = 300;      

// DEFINIÇÃO -- MOTORES
const int IN1 = 9;   
const int IN2 = 10;
const int IN3 = 3;   
const int IN4 = 7;
const int ENA = A2;
const int ENB = A1;

// DEFINIÇÃO -- LIMITES DE OBSTACULO
int limite = 300;

// DEFINIÇÃO -- BUZZER 
const int botaoStart = 4;
const int buzzer = 5;       
bool combateAtivo = false;   


void setup() {
  Serial.begin(9600);

  pinMode(sensorDir, INPUT);
  pinMode(sensorMeio, INPUT);
  pinMode(sensorEsq, INPUT);

  pinMode(linhaDir, INPUT);
  pinMode(linhaEsq, INPUT);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(botaoStart, INPUT_PULLUP);
  pinMode(buzzer, OUTPUT);

  parar(); 
}

void frente() {
  analogWrite(IN1, 255);
  analogWrite(IN2, 0);
  analogWrite(IN3, 255);
  analogWrite(IN4, 0);
}

void tras() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 255);
  analogWrite(IN3, 0);
  analogWrite(IN4, 255);
}

void direita() {
  analogWrite(IN1, 255);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 255);
}

void esquerda() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 255);
  analogWrite(IN3, 255);
  analogWrite(IN4, 0);
}

void parar() {
  analogWrite(IN1, 0);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, 0);
}

void procurar() {
  direita();  // PODE AJUSTAR DEPOIS
}

void loop() {

  // ---- Sensores Sharp (obstáculo) ----
  int valorDir  = analogRead(sensorDir);
  int valorMeio = analogRead(sensorMeio);
  int valorEsq  = analogRead(sensorEsq);

  // ---- Sensores de Linha (QRE) ----
  int linhaD = analogRead(linhaDir);
  int linhaE = analogRead(linhaEsq);

  // --- Iniciar com botão ---
  if (!combateAtivo) {
    if (digitalRead(botaoStart) == LOW) {
        parar();
        delay(5000);
        tone(buzzer, 1000, 300);
        combateAtivo = true;
    }
    return;
  }

  // =====================================================
  //  PRIMEIRO: Proteção contra cair da arena
  // =====================================================
  if (linhaD < limiteLinha || linhaE < limiteLinha) {
    tras();
    delay(300);

    // se linha no lado direito → vire para a esquerda
    if (linhaD < limiteLinha) {
      esquerda();
      delay(250);
    }

    // se linha no lado esquerdo → vire para a direita
    if (linhaE < limiteLinha) {
      direita();
      delay(250);
    }

    return;  
  }

  // =====================================================
  //  SEGUNDO: Lógica de ataque (sensores Sharp)
  // =====================================================

  // Inimigo no meio → ataque direto
  if (valorMeio < limite) {
    frente();
  }
  // Inimigo à direita
  else if (valorDir < limite) {
    direita();
  }
  // Inimigo à esquerda
  else if (valorEsq < limite) {
    esquerda();
  }
  // Nada detectado → girar procurando
  else {
    procurar();
  }
}