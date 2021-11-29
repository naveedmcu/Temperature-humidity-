void Timer1_init();
void Timer1_ON();
void Timer1_OFF();
void TIMER1_CLEAR_FLAG();
void Timer1_Enable();
void Timer1_Disable();

void Timer1_init()
{
  // Timer1 Registers:
// Prescaler=1:8; TMR1 Preset=3036; Freq=10.00Hz; Period=0.10 s
  PIR1.TMR1IF=0;
  PIE1.TMR1IE=0;
  T1CON.RD16=1;
  IPR1.TMR1IP=1;
  T1CON.T1CKPS1 = 1;// bits 5-4  Prescaler Rate Select bits
  T1CON.T1CKPS0 = 1;//
  T1CON.T1OSCEN = 1;// bit 3 Timer1 Oscillator Enable Control: bit 1=on
  T1CON.T1SYNC  = 1;// bit 2 Timer1 External Clock Input Synchronization Control bit: 1=Do not synchronize external clock input
  T1CON.TMR1CS  = 0;// bit 1 Timer1 Clock Source Select bit: 0=Internal clock (FOSC/4) / 1 = External clock from pin T13CKI (on the rising edge)
  T1CON.TMR1ON  = 0;// bit 0 enables timer
  TMR1H = 0xB;     // preset for timer1 MSB register
  TMR1L = 0xDC;     // preset for timer1 LSB register
}

void timer_reloded()
{
 TMR1H = 0xB;     // preset for timer1 MSB register
 TMR1L = 0xDC;     // preset for timer1 LSB register
}

void Timer1_ON()
{
 T1CON.TMR1ON = 1;
}
void Timer1_OFF()
{
 T1CON.TMR1ON = 0;
}

void Timer1_Enable()
{
 PIE1.TMR1IE=1;
}
void Timer1_Disable()
{
 PIE1.TMR1IE=0;
}

void TIMER1_CLEAR_FLAG()
{
 PIR1.TMR1IF=0;
}

void Enable_intr(){
     INTCON|=(1<<GIEH)|(1<<GIEL);
}

void disable_intr(){
     INTCON&=~(1<<GIEH)|(1<<GIEL);
}