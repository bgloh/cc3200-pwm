
// PWM + GPIO_PIN Interrupt
#include "pwm.h"
#define TIMER_BASE TIMERA2_BASE
#define TIMER TIMER_B

// CREAT PWM FROM TIMERA2 TIMER_B
Timer timerA2PWM(TIMER_BASE,TIMER,INVERSION_YES);

void setup()
{
  // put your setup code here, to run once:
  setupPWM_Timer();
  Serial.begin(9600);
  
  // pin interrupt for digial output
  pinMode(5,INPUT);  // GPIO pin
  pinMode(8,OUTPUT); // GPIO pin
 // attachInterrupt(5,pinISR, RISING);
 
}

void loop()
{
  // put your main code here, to run repeatedly:
  static unsigned char i;
  unsigned long count, regVal;
  i++;
 // count = timerA2PWM.getMatchSetValue();
 // regVal = timerA2PWM.readRegister(TIMERA2_BASE,0x08);
 // Serial.print("configuration: ");
 // Serial.println(regVal);
 // delay(2000);
}

void setupPWM_Timer()
{
  timerA2PWM.pinMuxAndPeripheralClockConfigure(PRCM_TIMERA2, PIN_64, PIN_MODE_3);
  timerA2PWM.configure( TIMER_CFG_SPLIT_PAIR | TIMER_CFG_B_PWM ); // half width, PWM
  timerA2PWM.setInterrupt(TIMER_CAPB_EVENT, TIMER_EVENT_NEG_EDGE, pwmISR);
  timerA2PWM.setPeriod(10.0);   //    period in milisecond
  timerA2PWM.setDuty(2.5);     //     duty in milisecond
  timerA2PWM.enable();         //     enable timer
}
void pwmISR()
{
  static int i,k, data;
  unsigned long ulstatus;
  i++; 
  // clear interrupt flag
  ulstatus = timerA2PWM.intStatus(TIMER_BASE);
  timerA2PWM.intClear(TIMER_BASE, ulstatus);
  pinISR();
}

void pinISR()
{
  static char data = 0;
  int val;
  data ^=1;  // toggle output
  digitalWrite(8,data); // pulse output
  val = analogRead(A3); // adc   
}

