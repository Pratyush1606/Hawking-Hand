#include <LiquidCrystal.h>

LiquidCrystal lcd(0,1,8,9,10,11);

uint16_t delayTime_1= 300;      //For the time difference between two consecutive pressings of switch 1
uint16_t delayTime_2= 300;      //For the time difference between two consecutive pressings of switch 2

#define interruptPin_1 2
#define interruptPin_2 3

volatile int switch_1 = 0;
volatile int prev_switch_1 = 0;
volatile int index_1;
volatile int switch_2 = 0;
volatile int prev_switch_2 = 0;
volatile int index_2;

void setup() {
  
  lcd.begin(16,2);
  
  //Serial.begin(9600);
  
  pinMode(interruptPin_1,INPUT_PULLUP);
  pinMode(interruptPin_2,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin_1), myisr_1, RISING);
  attachInterrupt(digitalPinToInterrupt(interruptPin_2), myisr_2, RISING);
}

void loop() {

  if(switch_1!=prev_switch_1)
  {
    delay(5*delayTime_1);
    index_1 = switch_1 - prev_switch_1;
    prev_switch_1 = switch_1;
  }
  
  if(switch_2!=prev_switch_2)
  {
    delay(5*delayTime_2);
    index_2 = switch_2 - prev_switch_2;
    prev_switch_2 = switch_2;
  }
  if(index_2>0 and index_1>0)
  {
    printInfo(index_1,index_2);
    index_2 = 0;
  }
}
void printInfo(int index_1,int index_2)
{
  char* a[4] = {" abcde","fghijk","lmnopq","rstuvw"};
  char* b[3] = {"x","y","z"};
  int c[4] = {0,1,2,3};
  int d[6] = {4,5,6,7,8,9};
  if(0<index_1<5)
  {
    lcd.write(a[index_1-1][index_2-1]);
    //Serial.print(a[index_1-1][index_2-1]);
  }
  else if(index_1==5)
  {
    if(index_2<4)
    {
      lcd.write(b[index_2-1]);
      //Serial.print(b[index_2-1]);
    }
    else if(index_2>=4)
    {
      lcd.write(c[index_2-4]);
      //Serial.print(c[index_2-4]);
    }
  }
  else if(index_1==6)
  {
    lcd.write(d[index_2-1]);
    //Serial.print(d[index_2-1]);
  }
  
}




void myisr_1()
{
  switch_1 = switch_1+1;
}

void myisr_2()
{
  switch_2 = switch_2+1;
}