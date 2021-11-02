#include <Keyboard.h>
#include <Mouse.h>

const int Wbutton = 6;
const int Sbutton = 8;
const int Dbutton = 7;
const int Abutton = 9;
const int xbutton = 16;
const int circlebutton = 14;
const int trianglebutton = 15;
const int squarebutton = 10;
const int R1button = 3;
const int L1button = 2;
const int joystickVRx1 = A0;
const int joystickVRy1 = A1;
const int joystickVRx2 = A2;
const int joystickVRy2 = A3;
const int joystickButton1 = 5;
const int joystickButton2 = 4;
const int mouseVelocity = 20;
const int joystickCenter = mouseVelocity/2;
const int FPS = 120;

unsigned long lastTime = 5;

//Control de las "flechas" del mando (w, a, s, d)
void wasdButtonsControl(int wbutton, int abutton, int sbutton, int dbutton);
//Control de los botones equis, circulo, triángulo y cuadrado
void playStationButtonsControl(int x, int circle, int triangle, int square);
//Control del joystick que mueve los personajes (joystick izquierdo)
void joystickMovementControl(int joystickvrx, int joysticvry);
//Control del joystick que mueve la cámara (joystick derecho);
void mouseMovementControl(int joystickvrx, int joystickvry, int mousevelocity, 
                          int joysticktolerance, int joystickCenter);
//Control de los botones L1 y R1                       
void mouseClicksControl(int leftClick, int rightClick);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(Wbutton, INPUT_PULLUP);
  pinMode(Abutton, INPUT_PULLUP);
  pinMode(Sbutton, INPUT_PULLUP);
  pinMode(Dbutton, INPUT_PULLUP);
  pinMode(xbutton, INPUT_PULLUP);
  pinMode(circlebutton, INPUT_PULLUP);
  pinMode(trianglebutton, INPUT_PULLUP);
  pinMode(squarebutton, INPUT_PULLUP);
  pinMode(R1button, INPUT_PULLUP);
  pinMode(L1button, INPUT_PULLUP);
  pinMode(joystickButton1, INPUT_PULLUP);
  pinMode(joystickButton2, INPUT_PULLUP);

  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if((millis()-lastTime) > 5){
    wasdButtonsControl(Wbutton, Abutton, Sbutton, Dbutton);
    playStationButtonsControl(xbutton, circlebutton, trianglebutton, squarebutton);
    joystickMovementControl(joystickVRx1, joystickVRy1, joystickButton1);
    mouseMovementControl(joystickVRx2, joystickVRy2, mouseVelocity, joystickCenter);
    mouseClicksControl(R1button, L1button);
    lastTime = millis();
  }
  Keyboard.releaseAll();
}

void wasdButtonsControl(int wbutton, int abutton, int sbutton, int dbutton){
  if(!digitalRead(abutton)){
    Keyboard.press('a');
  } 

  if(!digitalRead(wbutton)){
    Keyboard.press('w');
  }
  
  if(!digitalRead(sbutton)){
    Keyboard.press('s');
  }

  if(!digitalRead(dbutton)){
    Keyboard.press('d');
  }
}

void playStationButtonsControl(int x, int circle, int triangle, int square){
  if(!digitalRead(x)){
    Keyboard.press(' ');
  }

  if(!digitalRead(square)){
    Keyboard.press('r');
  }

  if(!digitalRead(triangle)){
    Keyboard.press('2');
  }
}

void joystickMovementControl(int joystickvrx, int joystickvry, int joystickbutton){
  int VRxlecture = analogRead(joystickvrx);
  int VRylecture = analogRead(joystickvry);
  
  //CONTROL DEL EJE Y (Hacia delante o hacia atrás)
  if((VRylecture > 550) && !digitalRead(joystickbutton)){
    Keyboard.press('W');
  }
  
  if(VRylecture > 600 && digitalRead(joystickbutton)){
    Keyboard.press('w');
  }

  if(VRylecture < 400 && !digitalRead(joystickbutton)){
    Keyboard.press('S');
  }

  if(VRylecture < 400 && digitalRead(joystickbutton)){
    Keyboard.press('s');
  }

  //CONTROL DEL EJE X (Izquierda o derecha)
  
  if(VRxlecture > 600 && !digitalRead(joystickbutton)){
    Keyboard.press('D');
  }
  
  if(VRxlecture > 600 && digitalRead(joystickbutton)){
    Keyboard.press('d');
  }
  
  if(VRxlecture < 400 && !digitalRead(joystickbutton)){
    Keyboard.release('A');
  }

  if(VRxlecture < 400 && digitalRead(joystickbutton)){
    Keyboard.release('a');
  }
  
}

void mouseMovementControl(int joystickvrx, int joystickvry, int mousevelocity, 
                          int joystickcenter){
  int VRxlecture = analogRead(joystickvrx);
  int VRylecture = analogRead(joystickvry);

  int xMove = 0;
  int yMove = 0;
  
  //Comprueba si hay algún error en la lectura
  if(VRxlecture>=0 && VRxlecture<=1024 && VRylecture>=0 && VRylecture<=1024){
    if(VRxlecture<450 || VRxlecture>550){
      xMove = map(VRxlecture, 1024, 0, 0, mousevelocity);
      xMove = xMove - joystickcenter;
    }
    
    if(VRylecture<450 || VRylecture>550){
      yMove = map(VRylecture, 1024, 0, 0, mousevelocity);
      yMove = yMove - joystickcenter;
    }
    
    //El tercer argumento es el scroll
    Mouse.move(xMove, yMove, 0);
  }
}

void mouseClicksControl(int leftClick, int rightClick){
  if(!digitalRead(leftClick)){
    Mouse.press(MOUSE_LEFT);
  }
  else{
    Mouse.release(MOUSE_LEFT);
  }

  if(!digitalRead(rightClick)){
    Mouse.press(MOUSE_RIGHT);
  }
  else{
    Mouse.release(MOUSE_RIGHT);
  }
}
