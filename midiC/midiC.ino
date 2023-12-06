#include <ResponsiveAnalogRead.h>
#include <MIDIUSB.h>
#include <SoftwareSerial.h>
#include "def.h"


SoftwareSerial bluetSerial(8, 9);
ResponsiveAnalogRead ResponsiveBatt(battPin, true, 0.02);




void setup() {
  Serial.begin(9600);
  bluetSerial.begin(9600);


  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  for (byte i = 0; i < nBotao; i++) {
    pinMode(botaoPin[i], INPUT_PULLUP);
  }
  for (byte i = 0; i < nBotaoFunc; i++) {
    pinMode(botaoFuncPin[i], INPUT_PULLUP);
  }

  for (byte i = 0; i < nPot; i++) {
    responsivePot[i] = ResponsiveAnalogRead(potPin[i], true, 0.02);
    responsivePot[i].setAnalogResolution(1023);  // define a resolução
  };


  anodoByte = letraAnod[0];
  catodoByte = numAnod[0];
  bancoPresetSelecionado();
  ledsAtualizar();
}

void loop() {

  // ---------- bateria ----
  ResponsiveBatt.update();
  battEstado = ResponsiveBatt.getValue();
  battVida = map(battEstado, 614, 859, 0, 100);
  if (millis() - battTempo >= 1000) {

    if (battVida >= 0 && battVida <= 25) {
      bitWrite(ledsByte, 0, 0);
      bitWrite(ledsByte, 1, 0);
      bitWrite(ledsByte, 2, 1);
      ledsAtualizar();
    } else if (battVida > 25 && battVida <= 65) {
      bitWrite(ledsByte, 0, 0);
      bitWrite(ledsByte, 1, 1);
      bitWrite(ledsByte, 2, 0);
      ledsAtualizar();
    } else if (battVida > 65) {
      bitWrite(ledsByte, 0, 1);
      bitWrite(ledsByte, 1, 0);
      bitWrite(ledsByte, 2, 0);
      ledsAtualizar();
    } else if(battVida >= 99){
      bitWrite(ledsByte, 0, 1);
      bitWrite(ledsByte, 1, 1);
      bitWrite(ledsByte, 2, 1);
      ledsAtualizar();
    }
    battTempo = millis();
    Serial.println(battEstado);
  };



  // ---- botoes ---
  for (byte i = 0; i < nBotao; i++) {
    botaoEstado[i] = digitalRead(botaoPin[i]);            // botaoEstado guarda o estado do botao (HIGH ou LOW)
    if ((millis() - botaoTempo[i]) > 75) {                // faz o debounce do botao ao fazer com que o botao so possa ser pressionado com um intervalo de 75 ms
      if (botaoEstado[i] == 0 && botaoEstadoP[i] == 1) {  // se o estado do botao for diferente do do anterior faz o codigo abaixo ( serve para nao repetir o sinal duas vezes
        botaoTempo[i] = millis();                         // reseta o tempo do botao

        if (botaoEstado[i] == 0 && botaoEstadoP[i] == 1) { // botao apertado

          botaoFlag[i] = botaoFlag[i] + 1;  // se o botao for apertado incrementa a flag ( para fazer duas funções )
          if (botaoFlag[i] > 2) {
            botaoFlag[i] = 1;
          }
          //Serial.print("botao: ");              //  <<< funções aqui
         // Serial.println(i);
         
        }
      } else if (botaoEstado[i] == HIGH && botaoEstadoP[i] == LOW) {
        if (millis() - botaoTempo[i] >= 1000) {  // se o botao for pressioando por mais que 1 segundo
         
         mandarPC_usb(midiChannel, midiBotaoPC[i]);
         MidiUSB.flush();
         mandarPC_bt(midiBotaoPC[i], midiChannel);
         LimparLed_Flag();
         ledsAtualizar();
         
          Serial.print("botao :");
          Serial.print(i);
         Serial.println(" segurado por 1 seg");


        }
      }
    }
    botaoEstadoP[i] = botaoEstado[i];  // as variaveis sao sempre iguais menos quando o botao e apertado

    if (botaoFlag[i] == 2 && noteOnFlag[i] == false) {  // quando a flag esta em 2 ou 1 faz coisas diferentes
      noteOnFlag[i] = true;
      mandarCC_usb(midiChannel, midiBotaoCC[i], 0);
      MidiUSB.flush();
      mandarCC_bt(midiBotaoCC[i], 0, midiChannel);


      bitWrite(ledsByte, i + 3, 1);
      ledsAtualizar();
      Serial.print("notaOn: ");
      Serial.println(i);




    } else if (botaoFlag[i] == 1 && noteOnFlag[i] == true) {
      noteOnFlag[i] = false;
      mandarCC_usb(midiChannel, midiBotaoCC[i], 127);
      MidiUSB.flush();
      mandarCC_bt(midiBotaoCC[i], 127, midiChannel);
      
      
      bitWrite(ledsByte, i + 3, 0);  //acende o led correspondente ao botao
      ledsAtualizar();
      Serial.print("notaOff:");
      Serial.println(i);
    }
  }
  // ----------------
  // ----------- botoes func ----------
  for (byte i = 0; i < nBotaoFunc; i++) {
    botaoFuncEstado[i] = digitalRead(botaoFuncPin[i]);
    if (millis() - botaoFuncTempo[i] > 75) {
      if (botaoFuncEstado[i] == 0 && botaoFuncEstadoP[i] == 1) {
        botaoFuncTempo[i] = millis();
        if (botaoFuncEstado[0] == 0 && botaoFuncEstado[1] == 0) {  // se os dois botoes func forem pressionados ao mesmo tempo
          botaoFuncPressionados = millis();
          flagBancoPreset = !flagBancoPreset;
          bancoPresetSelecionado();
        }
        if (botaoFuncEstado[1] == 0 && botaoFuncEstadoP[1] == 1 && flagBancoPreset == true) {  //flagPreset false = banco true = preset
          contadorPreset = contadorPreset - 1;
          if (contadorPreset < 0) {
            contadorPreset = 0;
          }
          catodoByte = numAnod[0];
          AtualizarContadorPreset();
        }

        if (botaoFuncEstado[1] == 0 && botaoFuncEstadoP[1] == 1 && flagBancoPreset == false) {
          ledBank[contadorBanco] = ledsByte;  //salva o estado dos leds quando apertado o botao
          for (byte i = 0; i < nBotao; i++) {
            botaoFlagMatriz[i][contadorBanco] = botaoFlag[i];  // salva a flag botao na matriz
          };
          for (byte i = 0; i < nBotao; i++) {
            noteOnMatriz[i][contadorBanco] = noteOnFlag[i];  // salva a flag botao na matriz
          };
          contadorBanco = contadorBanco - 1;


          AtualizarContador();
        }
        if (botaoFuncEstado[0] == 0 && botaoFuncEstadoP[0] == 1 && flagBancoPreset == false) {

          ledBank[contadorBanco] = ledsByte;
          for (byte i = 0; i < nBotao; i++) {
            botaoFlagMatriz[i][contadorBanco] = botaoFlag[i];
          };
          for (byte i = 0; i < nBotao; i++) {
            noteOnMatriz[i][contadorBanco] = noteOnFlag[i];  // salva a flag botao na matriz
          };
          contadorBanco = contadorBanco + 1;
          if (contadorBanco > nMaxBancos) {
            contadorBanco = 0;
          }

          AtualizarContador();
        }
        if (botaoFuncEstado[0] == 0 && botaoFuncEstadoP[0] == 1 && flagBancoPreset == true) {

          contadorPreset = contadorPreset + 1;
          if (contadorPreset > nMaxPreset) {
            contadorPreset = 0;
          }
          catodoByte = numAnod[0];
          AtualizarContadorPreset();
        }
      }
    }
    botaoFuncEstadoP[i] = botaoFuncEstado[i];
  }
  //0------------------
  // -------------- pots -------------
//   for (byte i = 0; i < nPot; i++) {
    
    
//     //responsivePot[i].update(analogRead(potPin[i]));

//     //potEstado[i] = responsivePot[i].getValue();
//     potEstado[i] = analogRead(potPin[i]);
    
//     potMap[i] = map(potEstado[i], 0, 1023, 0, 127);  // mapeia o valor maximo e minimo para se adequar ao data midi

//     int potVar = abs(potEstado[i] - potEstadoP[i]);  // armazena a variação do potenciometro
//     if (potVar > 30) {
//       tempoPerdidoPot[i] = millis();
//     }
//     potTempo[i] = millis() - tempoPerdidoPot[i];
//     if (potTempo[i] > 100) { //300
//       if (potMap[i] != potMapP[i]) {
//         mandarCC_usb(midiChannel, notaPotCC[i], potMap[i]);
//         MidiUSB.flush();
        
//         mandarCC_bt(notaPotCC[i], potMap[i], midiChannel);
//         //Serial.println(potMap[i]);
        
//       }
//     }
//     potEstadoP[i] = potEstado[i];
//     potMapP[i] = potMap[i];
//   }

  for(byte i = 0; i < nPot; i ++){
   responsivePot[i].update();
   potMap[i] = map(responsivePot[i].getValue(), 0, 1023, 0, 127);
    if(responsivePot[i].hasChanged()){
      if(potMap[i] != potEstadoP[i]){
        mandarCC_usb(midiChannel, notaPotCC[i], potMap[i]);
        MidiUSB.flush();
        mandarCC_bt(notaPotCC[i], potMap[i], midiChannel);
        delay(10);
      }
    }
    potEstadoP[i] = potMap[i];
  }
}


