/*
  TAREA
  CHECK actualizar a letras chicas
  CHECK borrar todo lo que no sirva:
        -port B y C -> data1 y data3
        -Boton q cambia color
  CHECK-agregar numeros
  CHECK-que los dibujos se guarden en letras minusculas
  CHECK -agregar funcion para colorear por columna
  separar el programa de los datos en dos archivos
  CHECK-agregar boolean para invertir
  CHECK-funcion para dibujar recibe el string
*/

#include <avr/pgmspace.h>//need to store letter arrays in flash memory- or else we run out of space, more info here: http://arduino.cc/en/Reference/PROGMEM

String povtext = "HOLA ab "; //PUT YOUR MESSAGE HERE!!- must be in all caps, spaces are fine, no punctuation
//String povtext = " FOR THE FUN OF IT ";
byte refreshrate = 1;//delay time for pixels to refresh in milliseconds- experiment with different values

//variable para setear los colores del texto
String povtext_color = "WWWW";

boolean invertir = false;

//get length of string povtext
int dimtext = povtext.length();

//array para el patron de inicio
const boolean load[] = {
  1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1
};


//--------------------------------------------------------------------------------------------------------
// REEMPLAZAR AQUI CON LOS DIBUJOS !!

int nDibus = 2;

const boolean dibujo_a[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 1, 0,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 0, 0, 0
};
String dibujo_a_color = { "MMMMMMMM" };

const boolean dibujo_b[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 1, 0,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 0, 0, 0
};
String dibujo_b_color = { "RRRRRRR" };

//------------------------------------------------------------------------------------------------------------------------------------------------------------

//The letters of the alphabet- edit the look of these if you want, just make sure the letters are 8 pixels wide
const boolean letterA[] PROGMEM = {
  0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterB[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterC[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterD[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterE[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterF[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterG[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterH[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterI[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterJ[] PROGMEM = {
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterK[] PROGMEM = {
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 0, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 1, 1, 1, 0,
  1, 1, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterL[] PROGMEM = {
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterM[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 1, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterN[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 0, 0, 1, 1,
  1, 1, 1, 1, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 1, 1, 1, 1,
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterO[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterP[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterQ[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 1, 0, 1, 1,
  1, 1, 0, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterR[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 1, 1, 1, 0,
  1, 1, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterS[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterT[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterU[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterV[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 0, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterW[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 1, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterX[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 0, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterY[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterZ[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter33[] PROGMEM = {//signo de exclamacion !
  0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter0[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter1[] PROGMEM = {
  0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter2[] PROGMEM = {
  0, 0, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter3[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter4[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter5[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter6[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter7[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter8[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter9[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

//incoming data storage
byte data2 = 0;//for portD

//pines a los transistores RGB
const byte pinR = 11;
const byte pinG = 10;
const byte pinB = 9;

//variables
byte n; //variable for loops
byte m; //variable for loops
byte t; //variable for loops
byte l; //variable for loops

int anchoLetra = 7;
int altoLetra = 8;
int ascii;
char letraActual;

int delayInicio = 100;

void setup() {
  setup_povRGB();
}

void loop() {
  loop_povRGB();
}
