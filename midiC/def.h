#define nBotao 4
byte botaoPin[nBotao] = {6,7,3,4}; // {3,4,6,7};
bool botaoEstado[nBotao];
bool botaoEstadoP[nBotao];
unsigned long botaoTempo[nBotao];
byte botaoFlag[nBotao] = {1,1,1,1};
bool noteOnFlag[nBotao] = {false};
byte midiBotaoCC[nBotao] = {20, 30, 40, 50};
byte midiBotaoCC_Origi[nBotao] = {20, 30, 40, 50};


#define nBotaoFunc 2
byte botaoFuncPin[nBotaoFunc] = {5,2};
bool botaoFuncEstado[nBotaoFunc];
bool botaoFuncEstadoP[nBotaoFunc];
unsigned long botaoFuncTempo[nBotaoFunc];
byte botaoFuncFlag[nBotaoFunc] = {1,1};
bool noteOnFuncFlag[nBotaoFunc] = {false, false};
bool botaoFuncPressionados;
unsigned long botaoFuncTempoPressionado;

bool flagBancoPreset = false;


#define dataPin 10
#define latchPin 16
#define clockPin 14

byte anodoByte = 0b11111111;
byte catodoByte = 0b00000000;
byte ledsByte = 0b00000000;
#define todosBitsUm 0xFF

byte midiChannel = 0x02;



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
 const byte letraAnod[5] = {
  0b10001000,
  0b11100000,
  0b10110001,
  0b11000010,
  0b10110000



 };
#define nMaxBancos 4
#define nMaxPreset 3
byte contadorBanco;
byte contadorPreset;


 #define battPin A2
 byte battVida;
 unsigned long battTempo;
