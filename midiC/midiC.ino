#include "def.h"

#include <SoftwareSerial.h>


SoftwareSerial bluetSerial (8, 9);





void setup() {
  Serial.begin(9600);
  bluetSerial.begin(9600);
  

  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  for (byte i = 0; i < nBotao ; i++) {
    pinMode(botaoPin[i], INPUT_PULLUP);
  }
  anodoByte = numAnod[4];
  catodoByte = numAnod[8];
  ledsAtualizar();




}

void loop() {
  // for(int i =0; i < 10; i++){
  //   catodoByte = numAnod[i];
  //   ledsAtualizar();
  //   delay(1000); 
  //   anodoByte = numAnod[i];
  //   ledsAtualizar();
  // }
  // //--- bateria 
  // battEstado = analogRead(battPin);
  // Serial.println(battEstado);
  // delay(1000);


  // ---- botoes ---
  for (byte i = 0; i < nBotao ; i++) {
    botaoEstado[i] = digitalRead(botaoPin[i]);                    // botaoEstado guarda o estado do botao (HIGH ou LOW)
      if ((millis() - botaoTempo[i]) >  75) {                     // faz o debounce do botao ao fazer com que o botao so possa ser pressionado com um intervalo de 75 ms
        if (botaoEstado[i] == 0 && botaoEstadoP[i] == 1){         // se o estado do botao for diferente do do anterior faz o codigo abaixo ( serve para nao repetir o sinal duas vezes
            botaoTempo[i] = millis();                             // reseta o tempo do botao

            if (botaoEstado[i] == 0 && botaoEstadoP[i] == 1){

                botaoFlag[i] = botaoFlag[i] + 1; // se o botao for apertado incrementa a flag ( para fazer duas funções )
                  if(botaoFlag[i] > 2){
                   botaoFlag[i] = 1;
                }
            Serial.print("botao: ");
            Serial.println(i);
          }
        }
        else if (botaoEstado[i] == HIGH && botaoEstadoP[i] == LOW){
           if(millis() - botaoTempo[i] >= 1000){    // se o botao for pressioando por mais que 1 segundo
            Serial.print("botao :");
            Serial.print(i);
            Serial.println(" segurado por 1 seg");
            
          }
        }
        
      }
    botaoEstadoP[i] = botaoEstado[i];  // as variaveis sao sempre iguais menos quando o botao e apertado

     if(botaoFlag[i] == 2 && noteOnFlag[i] == false){  // quando a flag esta em 2 ou 1 faz coisas diferentes
      noteOnFlag[i] = true;
      mandarCC_bt(midiBotao[i], 127);
      

      bitWrite(ledsByte, i + 3, 1);
      ledsAtualizar();
      Serial.print("notaOn: ");
      Serial.println(i);


      

    }else if(botaoFlag[i] == 1 && noteOnFlag[i] == true){
      noteOnFlag[i] = false;
      mandarCC_bt(midiBotao[i], 0);
      bitWrite(ledsByte,i + 3, 0);
      ledsAtualizar();
      Serial.print("notaOff:");
      Serial.println(i);


    }
  }
  // ----------------
  // ----------- botoes func ----------
  for (byte i = 0; i < nBotaoFunc ; i++){
    botaoFuncEstado[i] = digitalRead(botaoFuncPin[i]);
    
  };

  



}
