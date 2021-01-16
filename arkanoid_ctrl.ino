// vediamo se riesco a fare andare il controller di arkanoid
// Queto esempio l'ho preso da lafvin dove con il rotary cerca di controllare un motore
// A me invece interessa mouvere il mouse solo in orizzontale.
#include <Mouse.h>

// mouse
const int posXMax = 1023;
const int posXMin = 0;
const int mouseStep = 10;
int posX = posXMax / 2;


// encoder
const int PinCLK = 2; // Generating interrupts using CLK signal
const int PinDT = 3;  // Reading DT signal
const int PinSW = 4;  // Reading Push Button switch

volatile boolean TurnDetected;      // need volatile for Interrupts
volatile boolean rotationdirection; // CW or CCW rotation

int PrevPosition; // Previous Rotary position Value to check accuracy
int RotaryPosition = 0;

// Interrupt routine runs if CLK goes from HIGH to LOW
void isr()
{
  delay(4); // delay for Debouncing
  if (digitalRead(PinCLK))
    rotationdirection = !digitalRead(PinDT);
  else
    rotationdirection = digitalRead(PinDT);
    
  TurnDetected = true;
}

void setup()
{
  Serial.begin(9600);
  pinMode(PinCLK, INPUT);
  pinMode(PinDT, INPUT);
  pinMode(PinSW, INPUT);

  digitalWrite(PinSW, HIGH);
  attachInterrupt(0, isr, FALLING);
  
  Mouse.begin(); //Init mouse emulation

  Serial.println("Setup serial communication");
}

void loop()
{
  if (!(digitalRead(PinSW)))
  {
    // non capisco questo pezzo di reset
    if (RotaryPosition != 0)
    {
      RotaryPosition = 0;
      Serial.println("Reset position to zero");
    }
  }

  if (TurnDetected)
  {
    // isr was raised
    PrevPosition = RotaryPosition;
    if (rotationdirection)
    {
      RotaryPosition = RotaryPosition - 1;
      // Move mouse A-CW
      posX -= mouseStep;
      if (posX < posXMin){
        posX = posXMin;
      }
      Serial.println("Mouve A-CW");
    }
    else
    {
      RotaryPosition = RotaryPosition + 1;
      // Move mouse CW
      posX += mouseStep;
      if (posX > posXMax){
        posX = posXMax;
      }
      Serial.println("Mouve CW");
    }
    Serial.println(RotaryPosition);
    
    Mouse.move(posX,0,0);  
    
    TurnDetected = false;
  }
}
