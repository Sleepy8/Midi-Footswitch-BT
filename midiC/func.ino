void ledsAtualizar(){
  digitalWrite(latchPin, LOW);                                          // deixa o pino correspondente ao latch com estado logico baixo
  shiftOut(dataPin, clockPin, LSBFIRST, anodoByte);                    // desloca o byte correspondente ao display anodo para a memoria começando pelo bit menos significativo
  shiftOut(dataPin, clockPin, LSBFIRST, catodoByte ^ todosBitsUm);    // faz a mesma coisa que o de cima porem com um operador XOR para inverter o byte para que exiba corretamente no display catodo
  shiftOut(dataPin, clockPin, LSBFIRST, ledsByte);                   // mesma logica para atualizar os leds do chassi
  digitalWrite(latchPin, HIGH);                                     // deixa o pino latch com estado logico alto para aplicar as mudanças
}
void mandarCC_bt(byte midiNota, byte midiForca){
  bluetSerial.write(0xB0);             // passa o byte de status midi como Control Change no canal 0
  bluetSerial.write(midiNota);        // passa o byte de data da nota midi desejada
  bluetSerial.write(midiForca);      // passa o byte de valor da força desejada ( 0 À 127
};
void mandarPC_bt(byte midiNota, byte midiForca){
  bluetSerial.write(0xC0);             // passa o byte de status midi como Program Change no canal 0
  bluetSerial.write(midiNota);        // passa o byte de data da nota midi desejada
  bluetSerial.write(midiForca);      // passa o byte de valor da força desejada ( 0 À 127
};
void limparLeds(){
  for (byte i = 3; i < 8; i++){
    bitWrite(ledsByte, i, 0);
  };
  ledsAtualizar();
}