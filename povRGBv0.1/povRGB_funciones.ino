void setup_povRGB() {
  //port/pin assignments- set all pins to output- more info here: http://www.arduino.cc/en/Reference/PortManipulation

  DDRD = 0xFF;//port d- digital pins 0-7

  //para los pines que manejan el color
  pinMode (pinR, OUTPUT);
  pinMode (pinG, OUTPUT);
  pinMode (pinB, OUTPUT);

  //FLASHADAS EN EL SETUP PARA PROBAR COSAS
  colorSetup( 'W');
  patronInicio();
  colorSetup( 'R');
  patronInicio();
  colorSetup( 'G');
  patronInicio();
  colorSetup( 'B');
  patronInicio();
}

//FUNCIONES-------------------------------------------------------------------------------------
void sendToWand(const boolean letterArray[]) { //function to get array data

  //una funcion para mandar los colores en String asociado

  for (t = 0; t < anchoLetra; t++) { //for each time step
    // l es la fila del array

    //PINES 0-7 D
    for (l = 0; l < altoLetra; l++) { //for next eight rows of data
      data2 = data2 << 1;//bitwise shift left
      data2 |= pgm_read_byte_near(letterArray + (l * anchoLetra + t)); //add next value from dataset
    }

    //SET PINS:
    PORTD = data2; //0-7
    if (invertir == true) {
      PORTD = PORTD ^ B11111111;
    }
    delay(refreshrate);
    //clear data storage
    data2 = 0;
  }
}

void sendDrawToWand(const boolean letterArray[], String colorDibujo) { //function to get array data

  //una funcion para mandar los colores en String asociado

  for (t = 0; t < anchoLetra; t++) { //for each time step
    // l es la fila del array

    //coloreo segun su String asociado, falta recibir String
    colorSetup(colorDibujo.charAt(t));

    //PINES 0-7 D
    for (l = 0; l < altoLetra; l++) { //for next eight rows of data
      data2 = data2 << 1;//bitwise shift left
      data2 |= pgm_read_byte_near(letterArray + (l * anchoLetra + t)); //add next value from dataset
    }

    //SET PINS:
    PORTD = data2; //0-7
    delay(refreshrate);
    //clear data storage
    data2 = 0;
  }
}

//funcion para pasarle los colores con las letras W,R,G,B,Y,C,M
void colorSetup(char _n) { //que no se llama mas n
  if  ( _n == 'W') {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, HIGH);
  }
  else if ( _n == 'R') {
    digitalWrite(pinB, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
  }
  else if ( _n == 'G' ) {
    digitalWrite(pinB, LOW);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, LOW);
  }
  else if  ( _n == 'B' ) {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, LOW);
  }
  else if ( _n == 'Y') {
    digitalWrite(pinB, LOW);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, HIGH);
  }
  else if ( _n == 'C' ) {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, LOW);
  }
  else if  ( _n == 'M' ) {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
  }
  else if  ( _n == 'M' ) {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
  }
  else if  ( _n == ' ') {
    digitalWrite(pinB, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, LOW);
  }
}

void patronInicio() {

  //run intialization so we know device is working- leds should light up in order from top of wand to bottom
  for (byte j = 0; j < altoLetra; j++) { //for each time step

    for (byte i = 0; i < altoLetra; i++) { //for next eight rows of data
      data2 = data2 << 1;//bitwise shift left
      data2 |= load[(i * altoLetra + j)]; //add next value from dataset
    }

    PORTD = data2;

    delay(delayInicio);
  }
  //clear data storage
  data2 = 0;
  //clear ports- set all arduino pins to 0Volts
  PORTD = data2;

}
void apagarLEDs(int tiempo) {
  if (invertir == false) {
    PORTD = 0;
  }
  if (invertir == true) {
    PORTD = B11111111;
  }

  delay(refreshrate * tiempo);
}

void loop_povRGB() {

  //space at beginning of text
  //PORTD = 0;// aca apaga todo el PORTD
  apagarLEDs(3);

  for (n = 0; n < dimtext; n++) { //go through each character of povtext and call function sendToWand to display letter

    ascii = int(povtext.charAt(n));
    letraActual = povtext.charAt(n);

    //acá aplico el color, colores: WRGBYCM
    colorSetup(povtext_color.charAt(n));

    if (letraActual == 'A') {
      sendToWand(letterA);
    }
    else if (letraActual == 'B') {
      sendToWand(letterB);
    }
    else if (letraActual == 'C') {
      sendToWand(letterC);
    }
    else if (letraActual == 'D') {
      sendToWand(letterD);
    }
    else if (letraActual == 'E') {
      sendToWand(letterE);
    }
    else if (letraActual == 'F') {
      sendToWand(letterF);
    }
    else if (letraActual == 'G') {
      sendToWand(letterG);
    }
    else if (letraActual == 'H') {
      sendToWand(letterH);
    }
    else if (letraActual == 'I') {
      sendToWand(letterI);
    }
    else if (letraActual == 'J') {
      sendToWand(letterJ);
    }
    else if (letraActual == 'K') {
      sendToWand(letterK);
    }
    else if (letraActual == 'L') {
      sendToWand(letterL);
    }
    else if (letraActual == 'M') {
      sendToWand(letterM);
    }
    else if (letraActual == 'N') {
      sendToWand(letterN);
    }
    else if (letraActual == 'O') {
      sendToWand(letterO);
    }
    else if (letraActual == 'P') {
      sendToWand(letterP);
    }
    else if (letraActual == 'Q') {
      sendToWand(letterQ);
    }
    else if (letraActual == 'R') {
      sendToWand(letterR);
    }
    else if (letraActual == 'S') {
      sendToWand(letterS);
    }
    else if (letraActual == 'T') {
      sendToWand(letterT);
    }
    else if (letraActual == 'U') {
      sendToWand(letterU);
    }
    else if (letraActual == 'V') {
      sendToWand(letterV);
    }
    else if (letraActual == 'W') {
      sendToWand(letterW);
    }
    else if (letraActual == 'X') {
      sendToWand(letterX);
    }
    else if (letraActual == 'Y') {
      sendToWand(letterY);
    }
    else if (letraActual == 'Z') {
      sendToWand(letterZ);
    }
    else if (letraActual == '!') {
      sendToWand(letter33);
    }
    else if (letraActual == '0') {
      sendToWand(letter0);
    }
    else if (letraActual == '1') {
      sendToWand(letter1);
    }
    else if (letraActual == '2') {
      sendToWand(letter2);
    }
    else if (letraActual == '3') {
      sendToWand(letter3);
    }
    else if (letraActual == '4') {
      sendToWand(letter4);
    }
    else if (letraActual == '5') {
      sendToWand(letter5);
    }
    else if (letraActual == '6') {
      sendToWand(letter6);
    }
    else if (letraActual == '7') {
      sendToWand(letter7);
    }
    else if (letraActual == '8') {
      sendToWand(letter8);
    }
    else if (letraActual == '9') {
      sendToWand(letter9);
    }
    else if (letraActual == ' ') {
      //PORTD = 0;
      apagarLEDs(3); //off for 3 times
    } else if ( 96 > ascii < 123) {//letras minusculas 97 - 122

      if (letraActual == 'a') {
        sendDrawToWand(dibujo_a, dibujo_a_color);
      }
      else if (letraActual == 'b') {
        sendDrawToWand(dibujo_b, dibujo_b_color);
      }
    }

    //space between each character
    //PORTD = 0 ;//apaga el PORTD
    apagarLEDs(1);
  }

  //space at end of text
  apagarLEDs(3);

}
