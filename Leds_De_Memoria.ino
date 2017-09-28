const byte btn1 = 40, btn2 = 41 , btn3 = 42 , btn4 = 43 , btn5 = 44 , btn6 = 45 , btn7 = 46 , btn8 = 47 , btn9 = 48 ; // declara a porta dos botoes
const byte led1 = 30 , led2 = 31 , led3 = 32 , led4 = 33 , led5 = 34 , led6 = 35 , led7 = 36 , led8 = 37 , led9 = 29 ; // declara portas do LEDs
const byte ledVermelho = 28 , ledVerde = 27;
const int tempoMostraNivel = 1500; // tempo que os LEDs ficam acessos entre os níveis

int ordemLED[15] = {};  // vetores usados na comparação da sequência 
int ordemBT[15] = {}; 
int led , btn = 0; // índice de LEDs
int tempoLeituraBot = 500, tempoJogada = 1000;
bool konami = 0; // "konami code"

byte contadorVetor;
byte nivelDoJogo = 9; // nivel inicial do jogo
byte certo = 0;

bool start = 0; // programa rodando ou não

void setup() {                                   // inicializa portas como entradas ou saídas 
  for (byte cont = 27; cont <= 37 ; cont++) {
    pinMode(cont, OUTPUT);
  }
  for (byte cont = 40; cont <= 48; cont++) {
    pinMode(cont, INPUT);
  }
  for (byte i = 29; i < 38; i++) {
    digitalWrite(i, HIGH);
  }
}

void loop() {                           
  while (start == 1) {               // programa rodando
    digitalWrite (ledVerde, HIGH);   // piscando LEDs para mostrar nível
    mostraNivel(nivelDoJogo);
    if (digitalRead(btn2)) {   // código para debugar
      konami = 1;
    }
    digitalWrite (ledVerde, LOW);
    delay(2000);                             // intervalo até o nível começar
    
    for (byte i = 0; i <= nivelDoJogo + 2; i++) {                       // gera nível aleatóriamente
      led = random(29, 38);
      ordemLED[i] = led;                    // salva a sequencia no vetor 1
      digitalWrite(led, HIGH);
      delay(tempoJogada);
      digitalWrite(led, LOW);
      delay(tempoJogada);
    }

    while (contadorVetor <= nivelDoJogo + 2) {    // le sequencia digitada e salva no vetor 2
      bool bot1 = digitalRead(btn1);
      bool bot2 = digitalRead(btn2);
      bool bot3 = digitalRead(btn3);
      bool bot4 = digitalRead(btn4);
      bool bot5 = digitalRead(btn5);
      bool bot6 = digitalRead(btn6);
      bool bot7 = digitalRead(btn7);
      bool bot8 = digitalRead(btn8);
      bool bot9 = digitalRead(btn9);

      if (bot1 == HIGH) {
        digitalWrite(led1, HIGH);
        ordemBT[contadorVetor] = 30;
        contadorVetor++;
        delay(tempoLeituraBot);
        digitalWrite(led1, LOW);      // confirmação de leitura
      }
      if (bot2 == HIGH) {
        digitalWrite(led2, HIGH);
        ordemBT[contadorVetor] = 31;
        contadorVetor++;
        delay(tempoLeituraBot);
        digitalWrite(led2, LOW);
      }
      if (bot3 == HIGH) {
        digitalWrite(led3, HIGH);
        ordemBT[contadorVetor] = 32;
        contadorVetor++;
        delay(tempoLeituraBot);
        digitalWrite(led3, LOW);
      }
      if (bot4 == HIGH) {
        digitalWrite(led4, HIGH);
        ordemBT[contadorVetor] = 33;
        contadorVetor++;
        delay(tempoLeituraBot);
        digitalWrite(led4, LOW);
      }
      if (bot5 == HIGH) {
        digitalWrite(led5, HIGH);
        ordemBT[contadorVetor] = 34;
        contadorVetor++;
        delay(tempoLeituraBot);
        digitalWrite(led5, LOW);
      }
      if (bot6 == HIGH) {
        digitalWrite(led6, HIGH);
        ordemBT[contadorVetor] = 35;
        contadorVetor++;
        delay(tempoLeituraBot);
        digitalWrite(led6, LOW);
      }
      if (bot7 == HIGH) {
        digitalWrite(led7, HIGH);
        ordemBT[contadorVetor] = 36;
        contadorVetor++;
        delay(tempoLeituraBot);
        digitalWrite(led7, LOW);
      }
      if (bot8 == HIGH) {
        digitalWrite(led8, HIGH);
        ordemBT[contadorVetor] = 37;
        contadorVetor++;
        delay(tempoLeituraBot);
        digitalWrite(led8, LOW);
      }
      if (bot9 == HIGH) {
        digitalWrite(led9, HIGH);
        ordemBT[contadorVetor] = 29;
        contadorVetor++;
        delay(tempoLeituraBot);
        digitalWrite(led9, LOW);
      }
    }
    contadorVetor = 0;                      // zera o índice do vetor 

    for (int i = 0; i <= nivelDoJogo + 2; i++) {        // compara o vetor digitado com o vetor desejado
      if (ordemLED[i] == ordemBT[i]) {
        certo++;
      }
    }

    if (certo == nivelDoJogo + 3 || konami == 1) {    // confirma se todos os digitos estão certo ou seu codigo esta ativo
      nivelDoJogo++;                          // aumenta nível do jogo
      konami =0;                              // desativa código
      if (nivelDoJogo == 10) {
        ganhou ();
      }
      tempoJogada = tempoJogada - 100;
    } else {                                        //  caso o jogador erre, tal função inicia
      nivelDoJogo = 0;
      tempoJogada = 1000;
      digitalWrite(ledVermelho, HIGH);
      delay(2000);
      digitalWrite(ledVermelho, LOW);
      start = 0;                      // reinicia o jogo
      for (byte i = 29; i < 38; i++) {
        digitalWrite(i, HIGH);
      }
    }
    certo = 0;                // zera a variável 
  }
  if (digitalRead(btn1)) {                // inicia o jogo após o botão ser pressionado
    start = 1;
    for (byte i = 29; i < 38; i++) {
      digitalWrite(i, LOW);
    }
  }
}

void mostraNivel(byte nivel) {                  // indica o nível atual com os LEDs
  switch (nivel) {
    case 0:
      delay(tempoMostraNivel);
      break;

    case 1:
      digitalWrite(led1, HIGH);
      delay(tempoMostraNivel);
      digitalWrite(led1, LOW);
      delay(500);
      break;

    case 2:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      delay(tempoMostraNivel);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      break;

    case 3:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      delay(tempoMostraNivel);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      break;

    case 4:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      delay(tempoMostraNivel);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      break;

    case 5:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      delay(tempoMostraNivel);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      break;

    case 6:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      delay(tempoMostraNivel);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      break;

    case 7:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, HIGH);
      delay(tempoMostraNivel);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      break;

    case 8:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, HIGH);
      digitalWrite(led8, HIGH);
      delay(tempoMostraNivel);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      break;

    case 9:
      digitalWrite(led1, HIGH);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, HIGH);
      digitalWrite(led5, HIGH);
      digitalWrite(led6, HIGH);
      digitalWrite(led7, HIGH);
      digitalWrite(led8, HIGH);
      digitalWrite(led9, HIGH);
      delay(tempoMostraNivel);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);
      digitalWrite(led5, LOW);
      digitalWrite(led6, LOW);
      digitalWrite(led7, LOW);
      digitalWrite(led8, LOW);
      digitalWrite(led9, LOW);
      break;
  }
}

void ganhou() {                         // função quando o jogador ganha o jogo por completo
  for (byte i = 29; i < 38; i++) {
    digitalWrite(i, HIGH);
  }
  delay(1000);
  for (byte i = 29; i < 38; i++) {
    digitalWrite(i, LOW);
  }
  delay(1000);
  for (byte i = 29; i < 38; i++) {
    digitalWrite(i, HIGH);
  }
  delay(1000);
  for (byte i = 29; i < 38; i++) {
    digitalWrite(i, LOW);
  }
  delay(1000);
  start = 0;
  nivelDoJogo = 0;
  for (byte i = 29; i < 38; i++) {
    digitalWrite(i, HIGH);
  }
}


