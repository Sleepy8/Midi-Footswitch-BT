void ledsAtualizar() {
  digitalWrite(latchPin, LOW);                                      // deixa o pino correspondente ao latch com estado logico baixo
  shiftOut(dataPin, clockPin, LSBFIRST, anodoByte);                 // desloca o byte correspondente ao display anodo para a memoria começando pelo bit menos significativo
  shiftOut(dataPin, clockPin, LSBFIRST, catodoByte ^ todosBitsUm);  // faz a mesma coisa que o de cima porem com um operador XOR para inverter o byte para que exiba corretamente no display catodo
  shiftOut(dataPin, clockPin, LSBFIRST, ledsByte);                  // mesma logica para atualizar os leds do chassi
  digitalWrite(latchPin, HIGH);                                     // deixa o pino latch com estado logico alto para aplicar as mudanças
}
void mandarCC_bt(byte midiNota, byte midiForca, byte midiCanal) {
  bluetSerial.write(0xB0 + midiCanal);  // passa o byte de status midi como Control Change no canal 0
  bluetSerial.write(midiNota);          // passa o byte de data da nota midi desejada
  bluetSerial.write(midiForca);         // passa o byte de valor da força desejada ( 0 À 127
};
void mandarPC_bt(byte midiNota, byte midiCanal) {
  bluetSerial.write(0xC0 + midiCanal);       // passa o byte de status midi como Program Change no canal 0
  bluetSerial.write(midiNota);   // passa o byte de data da nota midi desejada
};
void LimparLed_Flag(){
    for (byte i = 0; i < nBotao; i++) { 
        botaoFlag[i] = 1;
        noteOnFlag[i] = 0; 
        for(byte j = 0; j < nMaxBancos + 1; j++){
          botaoFlagMatriz[i][j] = 1;
          noteOnMatriz[i][j] = 0;

        }
      };
    for(byte i = 0; i < nMaxBancos + 1; i ++){
      ledBank[i] = 0b00000000;
      ledsByte = 0b00000000;
    };

};
void AtualizarContador() {
  switch (contadorBanco) {
    case 0:
      catodoByte = numAnod[0];
      ledsByte = ledBank[0];
      for (byte i = 0; i < nBotao; i++) {  // transforma as flags no estado em que foram deixadas da ultima vez
        botaoFlag[i] = botaoFlagMatriz[i][0];
      }
      for (byte i = 0; i < nBotao; i++) {
        noteOnFlag[i] = noteOnMatriz[i][0]; 
      };
      bancoPresetSelecionado();
      ledsAtualizar();
      for (byte i = 0; i < nBotao; i++) {
       
        midiBotaoCC[i] = midiBotaoCC_Origi[i] + 0; // aumenta a nota CC botao em 1...
        midiBotaoPC[i] = midiBotaoCC[i];
         
      }
      break;
    case 1:
      catodoByte = numAnod[1];
      ledsByte = ledBank[1];
      for (byte i = 0; i < nBotao; i++) {
        botaoFlag[i] = botaoFlagMatriz[i][1];
      };
      for (byte i = 0; i < nBotao; i++) {
        noteOnFlag[i] = noteOnMatriz[i][1];  // salva a flag botao na matriz
      };
      bancoPresetSelecionado();
      ledsAtualizar();
      for (byte i = 0; i < nBotao; i++) {
        midiBotaoCC[i] = midiBotaoCC_Origi[i] + 1;
        midiBotaoPC[i] = midiBotaoCC[i]; 
      }
      break;
    case 2:
      catodoByte = numAnod[2];
      ledsByte = ledBank[2];
      for (byte i = 0; i < nBotao; i++) {
        botaoFlag[i] = botaoFlagMatriz[i][2];
      };
      for (byte i = 0; i < nBotao; i++) {
        noteOnFlag[i] = noteOnMatriz[i][2];  // salva a flag botao na matriz

      };
      bancoPresetSelecionado();
      ledsAtualizar();
      for (byte i = 0; i < nBotao; i++) {
        midiBotaoCC[i] = midiBotaoCC_Origi[i] + 2;
        midiBotaoPC[i] = midiBotaoCC[i];
      }
      break;
    case 3:
      catodoByte = numAnod[3];
      ledsByte = ledBank[3];
      for (byte i = 0; i < nBotao; i++) {
        botaoFlag[i] = botaoFlagMatriz[i][3];
      };
      for (byte i = 0; i < nBotao; i++) {
        noteOnFlag[i] = noteOnMatriz[i][3];  // salva a flag botao na matriz

      };
      bancoPresetSelecionado();
      ledsAtualizar();
      for (byte i = 0; i < nBotao; i++) {
        midiBotaoCC[i] = midiBotaoCC_Origi[i] + 3;
        midiBotaoPC[i] = midiBotaoCC[i];
      }
      break;
    case 4:
      catodoByte = numAnod[4];
      ledsByte = ledBank[4];
      for (byte i = 0; i < nBotao; i++) {
        botaoFlag[i] = botaoFlagMatriz[i][4];
      };
      for (byte i = 0; i < nBotao; i++) {
        noteOnFlag[i] = noteOnMatriz[i][4];  // salva a flag botao na matriz
      };
      bancoPresetSelecionado();
      ledsAtualizar();
      for (byte i = 0; i < nBotao; i++) {
        midiBotaoCC[i] = midiBotaoCC_Origi[i] + 4;
        midiBotaoPC[i] = midiBotaoCC[i];
      }
      break;
    case 5:
      catodoByte = numAnod[5];
      ledsByte = ledBank[5];
      for (byte i = 0; i < nBotao; i++) {
        botaoFlag[i] = botaoFlagMatriz[i][5];
      };
      for (byte i = 0; i < nBotao; i++) {
        noteOnFlag[i] = noteOnMatriz[i][5];  // salva a flag botao na matriz
      };
      bancoPresetSelecionado();
      ledsAtualizar();
      for (byte i = 0; i < nBotao; i++) {
        midiBotaoCC[i] = midiBotaoCC_Origi[i] + 5;
        midiBotaoPC[i] = midiBotaoCC[i];
      }
      
      break;
  };
}
void AtualizarContadorPreset() {
  switch (contadorPreset) {
    case 0:
      anodoByte = letraAnod[0];
      bancoPresetSelecionado();
      ledsAtualizar();
      break;
    case 1:
      anodoByte = letraAnod[1];
      bancoPresetSelecionado();
      ledsAtualizar();
      break;
    case 2:
      anodoByte = letraAnod[2];
      bancoPresetSelecionado();
      ledsAtualizar();
      break;
    case 3:
      anodoByte = letraAnod[3];
      bancoPresetSelecionado();
      ledsAtualizar();
      break;
    case 4:
      anodoByte = letraAnod[4];
      bancoPresetSelecionado();

      ledsAtualizar();
      break;
      anodoByte = letraAnod[5];
      bancoPresetSelecionado();

      ledsAtualizar();
      break;
  };
}
void bancoPresetSelecionado() {
  if (flagBancoPreset == false) {  //modo banco
    bitWrite(anodoByte, 7, 1);
    bitWrite(catodoByte, 7, 0);

   // ledsAtualizar();
  } else {  //modo preset
    bitWrite(anodoByte, 7, 0);
    bitWrite(catodoByte, 7, 1);
    //catodoByte = numAnod[0];
   // ledsAtualizar();
  }
}