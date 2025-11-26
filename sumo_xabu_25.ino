// ============================================================================== // 
// ===================== CONFIGURAÇÕES DE VARIÁVEIS ============================= //
// ============================================================================== //

// Definindo pinos dos motores
const int IN1 = 9;
const int IN2 = 10;
const int IN3 = 3;
const int IN4 = 11;
const int ENA = 6; // PWM
const int ENB = 5; // PWM

// Definindo pinos dos sensores de linha
const int SL_Direita = A0;
const int SL_Esquerda = A3;

// Definindo pinos dos sensores de obstáculo
const int SO_Esquerda = A6;
const int SO_Meio = A5;
const int SO_Direita = A4;

const int buzzer = 2;
const int frequencia = 1000;
const int duracao_apito = 500;

// Definindo velocidade
const int velocidade_padrao = 200;
const int velocidade_re = 220;
const int velocidade_curva = 250;
const int velocidade_acaba_com_tudo = 255;
const int velocidade_brusca = 230;

// ============================================================================== // 
// ===================== CONFIGURAÇÕES DO SETUP (Buzzer Adicionado) ================================= //
// ============================================================================== //

void setup() {

// Configurando setup dos motores
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

// Configurando setup dos sensores de linha
  pinMode(SL_Direita, INPUT);
  pinMode(SL_Esquerda, INPUT);

// Configurando setup dos sensores de obstáculo
  pinMode(SO_Esquerda, INPUT);
  pinMode(SO_Meio, INPUT);
  pinMode(SO_Direita, INPUT);

  pinMode(buzzer, OUTPUT);

// Iniciando SERIAL BEGIN (conexão do arduino com o computador via USB)
  Serial.begin(9600);
  
  tone(buzzer, 500, 500);
  delay(1000);
  
  for (int i = 0; i < 4; i++) {
    tone(buzzer, frequencia, 100); 
    delay(1000); 
  }
  
  tone(buzzer, 2000, 500);
  
  noTone(buzzer); 
}

// ============================================================================== // 
// ===================== CONFIGURAÇÕES DAS FUNÇÕES ============================== //
// ============================================================================== //

void andar_frente() 
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidade_padrao);
  analogWrite(ENB, velocidade_padrao);
}

void dar_re()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidade_re);
  analogWrite(ENB, velocidade_re);
  delay(700);
}

void virar_esquerda_brusca()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); 
  analogWrite(ENA, velocidade_brusca);
  analogWrite(ENB, velocidade_brusca);
  delay(200);
}

void virar_direita_brusca()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velocidade_brusca);
  analogWrite(ENB, velocidade_brusca);
  delay(200);
}

void virar_esquerda()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, velocidade_curva);
  delay(300);
}

void virar_direita()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidade_curva);
  analogWrite(ENB, 0);
  delay(300);
}

void parar()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void identifica_linha()
{
  int valor_esquerda_linha = analogRead(SL_Esquerda);
  int valor_direita_linha = analogRead(SL_Direita);

  if (valor_esquerda_linha < 300)
  {
    dar_re();
    virar_direita();
  }
  else if (valor_direita_linha < 300)
  {
    dar_re();
    virar_esquerda();
  }
  else 
  {
    andar_frente();
  }
}

void atacar()
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velocidade_acaba_com_tudo);
  analogWrite(ENB, velocidade_acaba_com_tudo);
}

void identifica_adversario()
{
  int valor_esquerda_obs = analogRead(SO_Esquerda);
  int valor_meio_obs = analogRead(SO_Meio);
  int valor_direita_obs = analogRead(SO_Direita);
  
  if (valor_meio_obs > 300)
  {
    atacar();
  }

  else if (valor_direita_obs >= 450)
  {
    virar_esquerda_brusca();
  }
  else if (valor_esquerda_obs >= 450)
  {
    virar_direita_brusca();
  }
  else if (valor_esquerda_obs > 300)
  {
    virar_esquerda();
  }
  else if (valor_direita_obs > 300)
  {
    virar_direita();
  }
  else 
  {
    andar_frente();
  }
}

// ============================================================================== // 
// ===================== CONFIGURAÇÕES DO LOOP ================================== //
// ============================================================================== //

void loop() {
  identifica_adversario();
  identifica_linha();
}