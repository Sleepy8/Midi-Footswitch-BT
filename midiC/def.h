#define nBotao 4
byte botaoPin[nBotao] = {6,7,3,4}; // {3,4,6,7};
bool botaoEstado[nBotao];
bool botaoEstadoP[nBotao];
unsigned long botaoTempo[nBotao];
byte botaoFlag[nBotao] = {1,1,1,1};
bool noteOnFlag[nBotao] = {false};
byte midiBotao[nBotao] = {20, 21, 22, 23};


#define nBotaoFunc 2
byte botaoFuncPin[nBotaoFunc] = {2,5};
bool botaoFuncEstado[nBotaoFunc];
bool botaoFuncEstadoP[nBotaoFunc];
//unsigned long botaoTempo[nBotaoFunc];
// byte botaoFlag[nBotaoFunc] = {1,1,1,1};
// bool noteOnFlag[nBotaoFunc] = {false};



#define dataPin 10
#define latchPin 16
#define clockPin 14

byte anodoByte = 0b11111111;
byte catodoByte = 0b00000000;
byte ledsByte = 0b00000000;
#define todosBitsUm 0xFF

byte midiChannel = 0;



const byte numAnod[10] = {
   0b10000001,
   0b11001111,
   0b10010010,
   0b10000110,
   0b11001100,
   0b10100100,
   0b10100000,
   0b10001111,
   0b10000000,
   0b10001100,
 };

 #define battPin A2
 unsigned long battEstado;
