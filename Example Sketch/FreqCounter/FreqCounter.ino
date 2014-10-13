
/*
 FreqCounter library from:
 
  Martin Nawrath KHM LAB3
 Kunsthochschule f¸r Medien Kˆln
 Academy of Media Arts
 http://www.khm.de
 http://interface.khm.de/index.php/labor/experimente/	
 */
#include <FreqCounter.h>

// Frequency counter input pin
// Defined in FreqCounter.h
//#define FC 5

// Pins to drive Segment Shift Register
#define SR_DATA A0
#define SR_CLK A1

// Display digit pins
#define DIGIT_1 4
#define DIGIT_2 6
#define DIGIT_3 7
#define DIGIT_4 8
#define DIGIT_5 9
#define DIGIT_6 10
#define DIGIT_7 11
#define DIGIT_8 12

// Gate LED
#define GATE_LED 13

// This sets the delay time for frame rate
// The value is repeated for each of the digits on the display so 
//   frame rate = 1 / (8 * DIGIT_TIME(uS)) -> 125 Hz
#define DIGIT_TIME 1000

// Character generator for 7-segment displays
//  PC = {B,A,E,C,G,Dp,D,F}
static uint8_t chargen[] = {
  0b11110011,  // 0  '0'
  0b10010000,  // 1  '1'
  0b11101010,  // 2  '2'
  0b11011010,  // 3  '3'
  0b10011001,  // 4  '4'
  0b01011011,  // 5  '5'
  0b01111011,  // 6  '6'
  0b11010000,  // 7  '7'
  0b11111011,  // 8  '8'
  0b11011011,  // 9  '9'
  0b11111001,  // 10  'A'
  0b00111011,  // 11  'B'
  0b01100011,  // 12  'C'
  0b10111010,  // 13  'D'
  0b01101011,  // 14  'E'
  0b01101001,  // 15  'F'
  0b00000000,  // 16  " "
};

unsigned long frq;
unsigned long num = 0;
int cnt;
int DispBCD = 0;
boolean leadzero = true;

void setup() {
  pinMode(GATE_LED, OUTPUT);

  Serial.begin(115200);        // connect to the serial port

  Serial.println("Frequency Counter");

  pinMode(SR_DATA, OUTPUT);
  pinMode(SR_CLK, OUTPUT);

  // set up the digit control pins
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);
  pinMode(DIGIT_5, OUTPUT);
  pinMode(DIGIT_6, OUTPUT);
  pinMode(DIGIT_7, OUTPUT);
  pinMode(DIGIT_8, OUTPUT);

  // Set up to take a frequency sample (to kick things off)
  FreqCounter::f_comp=162;   // Cal Value / Calibrate with professional Freq Counter
  FreqCounter::start(1000);  // 100 ms Gate Time
}



void loop() {

  if(FreqCounter::f_ready != 0) {  // if a new value is available
    frq=FreqCounter::f_freq;       // get the value
    Serial.print(cnt++);
    Serial.print("  Freq: ");
    Serial.println(frq);
    
    // then set up to take the next measurement
    FreqCounter::f_comp=162;   // Cal Value / Calibrate with professional Freq Counter
    FreqCounter::start(1000);  // 100 ms Gate Time
  }

  // Convert the binary value into decimal digits
  // then multiplex the display using the digits
  num = frq;
  leadzero = true;
  
  DispBCD = 0;
  if(leadzero && num<10000000)DispBCD = 16;
  while(num >= 10000000) { DispBCD++; num-=10000000; leadzero=false; }
  ShiftOut(chargen[DispBCD]);
  digitalWrite(DIGIT_1, LOW);
  delayMicroseconds(DIGIT_TIME);
  digitalWrite(DIGIT_1, HIGH);

  DispBCD = 0;
  if(leadzero && num<1000000)DispBCD = 16;
  while(num >= 1000000) { DispBCD++; num-=1000000; leadzero=false; }
  ShiftOut(chargen[DispBCD]);
  digitalWrite(DIGIT_2, LOW);
  delayMicroseconds(DIGIT_TIME);
  digitalWrite(DIGIT_2, HIGH);

  DispBCD = 0;
  if(leadzero && num<100000)DispBCD = 16;
  while(num >= 100000)  { DispBCD++; num-=100000; leadzero=false; }
  ShiftOut(chargen[DispBCD]);
  digitalWrite(DIGIT_3, LOW);
  delayMicroseconds(DIGIT_TIME);
  digitalWrite(DIGIT_3, HIGH);

  DispBCD = 0;
  if(leadzero && num<10000)DispBCD = 16;
  while(num >= 10000) { DispBCD++; num-=10000; leadzero=false; }
  ShiftOut(chargen[DispBCD]);
  digitalWrite(DIGIT_4, LOW);
  delayMicroseconds(DIGIT_TIME);
  digitalWrite(DIGIT_4, HIGH);

  DispBCD = 0;
  if(leadzero && num<1000)DispBCD = 16;
  while(num >= 1000)  { DispBCD++; num-=1000; leadzero=false; }
  ShiftOut(chargen[DispBCD]);
  digitalWrite(DIGIT_5, LOW);
  delayMicroseconds(DIGIT_TIME);
  digitalWrite(DIGIT_5, HIGH);

  DispBCD = 0;
  if(leadzero && num<100)DispBCD = 16;
  while(num >= 100) { DispBCD++; num-=100; leadzero=false; }
  ShiftOut(chargen[DispBCD]);
  digitalWrite(DIGIT_6, LOW);
  delayMicroseconds(DIGIT_TIME);
  digitalWrite(DIGIT_6, HIGH);

  DispBCD = 0;
  if(leadzero && num<10)DispBCD = 16;
  while(num >= 10)  { DispBCD++; num-=10; leadzero=false; }
  ShiftOut(chargen[DispBCD]);
  digitalWrite(DIGIT_7, LOW);
  delayMicroseconds(DIGIT_TIME);
  digitalWrite(DIGIT_7, HIGH);

  ShiftOut(chargen[num]);
  digitalWrite(DIGIT_8, LOW);
  delayMicroseconds(DIGIT_TIME);
  digitalWrite(DIGIT_8, HIGH);
}  

//-=|=-=|=-=|=-=|=-=|=-=|=-=|=-=|=-=|=-=|=-=|=-=|=-=|=-=|=-=|=-=|
void ShiftOut(uint8_t data) {
  digitalWrite(SR_DATA, (data & 0x80));
  digitalWrite(SR_CLK, LOW);
  digitalWrite(SR_CLK, HIGH);
  digitalWrite(SR_DATA, (data & 0x40));
  digitalWrite(SR_CLK, LOW);
  digitalWrite(SR_CLK, HIGH);
  digitalWrite(SR_DATA, (data & 0x20));
  digitalWrite(SR_CLK, LOW);
  digitalWrite(SR_CLK, HIGH);
  digitalWrite(SR_DATA, (data & 0x10));
  digitalWrite(SR_CLK, LOW);
  digitalWrite(SR_CLK, HIGH);
  digitalWrite(SR_DATA, (data & 0x08));
  digitalWrite(SR_CLK, LOW);
  digitalWrite(SR_CLK, HIGH);
  digitalWrite(SR_DATA, (data & 0x04));
  digitalWrite(SR_CLK, LOW);
  digitalWrite(SR_CLK, HIGH);
  digitalWrite(SR_DATA, (data & 0x02));
  digitalWrite(SR_CLK, LOW);
  digitalWrite(SR_CLK, HIGH);
  digitalWrite(SR_DATA, (data & 0x01));
  digitalWrite(SR_CLK, LOW);
  digitalWrite(SR_CLK, HIGH);
}



