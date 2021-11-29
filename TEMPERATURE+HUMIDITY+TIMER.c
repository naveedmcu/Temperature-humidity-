//*****************************************************************************/
//  DATE 04/MAY/2012
//
//*****************************************************************************/
// LCD module connections
sbit LCD_RS at LATD3_bit;
sbit LCD_EN at LATD2_bit;
sbit LCD_D4 at LATD4_bit;
sbit LCD_D5 at LATD5_bit;
sbit LCD_D6 at LATD6_bit;
sbit LCD_D7 at LATD7_bit;

sbit LCD_RS_Direction at TRISD3_bit;
sbit LCD_EN_Direction at TRISD2_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
// End LCD module connections

sbit relay1 at LATE0_bit;
sbit relay2 at LATE1_bit;
sbit relay3 at LATE2_bit;

char  keypadPort at PORTB;

const code  _max_Temp=1;
const code  _MIN_Temp=0;

const code  _max_Humi=2;
const code  _MIN_Humi=3;

const code  _read_off=0;
const code  _read_on=1;

const code  _save_on=1;
const code  _save_off=0;

const code  _read_on_timer=1;
const code  _read_off_timer=0;

const code  exit=1;

const code low_from_max_set_value=1, hi_from_max_set_value=2,
           low_from_min_set_value=3, hi_from_min_set_value=4,
           equal=5,_min=0,_max=1;

unsigned char msg1[]={"1=TEMP Set"};
unsigned char msg2[]={"2=RH Set"};
unsigned char msg3[]={"3=Timer"};

char back_bit=0;
char uart_rd;
unsigned int HUMI1, new_temp;
float volt1, humidity, new_humidity;
double expo1;
unsigned char Humidity_buff[5], TEXT_COMPARE[4], set_temp[3];
unsigned short key_pad_data, edit_key_pad_data, Digit_position=0;

//double
unsigned char max_temp[5], max_temp1[4], min_temp[5], min_temp1[4];
unsigned char max_humi[5], max_humi1[4], min_humi[5], min_humi1[4];
unsigned char Save_time[9],SAV_Display_time[9];

unsigned char se,hor,mi ,trt[15];
long sec_coverted, on_time, off_time;
long ii=0;
unsigned char password[3], pp=0, exit1=0;

bit on_off;
unsigned char hi_lo=0;

bit on_off_h;
unsigned char hi_lo_h=0;
 
char mode=1;


void cls()
{
 Lcd_Cmd(_LCD_CLEAR);
}

void move_right()
{
 Lcd_Cmd(_LCD_MOVE_CURSOR_RIGHT);
}
void move_left()
{
 Lcd_Cmd(_LCD_MOVE_CURSOR_LEFT);
}

void underline_off()
{
 Lcd_Cmd(_LCD_CURSOR_OFF);
}
void underline_on()
{
 Lcd_Cmd(_LCD_UNDERLINE_ON);
}

unsigned int read_adc()
{
 unsigned int ADC_value;
 ADC_Init();
 ADC_value=ADC_Read(4);
 return ADC_value;
}

double get_humidity()
{
  float humidity_1=0.0;
  char i=0;
/*  HUMI1 = read_adc();
  humidity=((HUMI1*4.65*31.0)/1023.0)-18.0;
  humidity_1=humidity;
*/
  for(i=0;i<100;i++)
  {
   delay_ms(3);
   HUMI1 = read_adc();
//   humidity=((HUMI1*4.95*30.0)/1023.0)-16.0;
//   humidity=((HUMI1*4.95*29.07)/1023.0)-14.042;
     humidity=((HUMI1*4.9)/1023.0);
//     humidity*=pow(humidity,0.9727);
   humidity_1+=humidity;
  }
  humidity_1/=100;
  expo1=0.7377*humidity_1;
  expo1=7.8534*exp(expo1);
/*
   humidity_1/=100;
   humidity=0.7377*humidity_1;
   expo1=exp(humidity);
   expo1*=7.8534;
*/
//  humidity_1=7.8534*exp(0.7377*humidity_1);
  return expo1;
}

void Read_eeprm_MAX_MIN_TEMP(unsigned char hu_temp)
{
 if (hu_temp==_max_temp)
 {
  max_temp1[0]=EEPROM_Read(21);
  max_temp1[1]=EEPROM_Read(22);
  max_temp1[2]=EEPROM_Read(23);
 }
 else if (hu_temp==_min_temp)
 {
  min_temp1[0]=EEPROM_Read(11);
  min_temp1[1]=EEPROM_Read(12);
  min_temp1[2]=EEPROM_Read(13);
 }
 else if (hu_temp==_max_humi)
 {
//  max_humi[0]=EEPROM_Read(41);
//  max_humi[1]=EEPROM_Read(42);
//  max_humi[2]='.';
//  max_humi[3]=EEPROM_Read(43);
  max_humi1[0]=EEPROM_Read(41);
  max_humi1[1]=EEPROM_Read(42);
  max_humi1[2]=EEPROM_Read(43);
 }
 else if (hu_temp==_min_humi)
 {
//  min_humi[0]=EEPROM_Read(31);
//  min_humi[1]=EEPROM_Read(32);
//  min_humi[2]='.';
//  min_humi[3]=EEPROM_Read(33);
  min_humi1[0]=EEPROM_Read(31);
  min_humi1[1]=EEPROM_Read(32);
  min_humi1[2]=EEPROM_Read(33);
 }
}


//******************************************************************************
// unsigned char chk_min_max_set_value(unsigned char minmax)"chking temperature"
//******************************************************************************
unsigned char chk_min_max_set_value(unsigned char minmax)
 {
 unsigned char value_chk[3];
 
 if (minmax==0)
 {
  value_chk[0]=min_temp1[0];
  value_chk[1]=min_temp1[1];
  value_chk[2]=min_temp1[2];
 }
 else if (minmax==1)
 {
  value_chk[0]=max_temp1[0];
  value_chk[1]=max_temp1[1];
  value_chk[2]=max_temp1[2];
 }
 
 if (TEXT_COMPARE[0]== value_chk[0])          //thou
 {
  if (TEXT_COMPARE[1]== value_chk[1])         //ten
  {
    if (TEXT_COMPARE[3]>= value_chk[2])        //after '.'
    {
     return hi_from_min_set_value;
    }
    else if (TEXT_COMPARE[3]<= value_chk[2])
    {
  //   portc.b0=1;
       return low_from_min_set_value;
    }
    else if (TEXT_COMPARE[3]== value_chk[2])
    {
     return equal;
    }
  }
  else if (TEXT_COMPARE[1]> value_chk[1])
  {
//   portc.b0=0;
   return hi_from_min_set_value;
  }
   else if (TEXT_COMPARE[1]< value_chk[1])
  {
//   portc.b0=1;
     return low_from_min_set_value;
  }
 }
 else if (TEXT_COMPARE[0]> value_chk[0])
 {
//  portc.b0=0;
    return hi_from_min_set_value;
 }
 else if (TEXT_COMPARE[0]< value_chk[0])
 {
//  portc.b0=1;
    return low_from_min_set_value;
 }
}
//******************************************************************************
// chk_temp()
//******************************************************************************
void chk_temp()
{

 Read_eeprm_MAX_MIN_TEMP (_min_temp);
 hi_lo=chk_min_max_set_value(_min);
 if (hi_lo==low_from_min_set_value)
 {
  on_off=1;
  relay1=1;
 }
 
 else if (hi_lo==HI_from_min_set_value)
 {
  Read_eeprm_MAX_MIN_TEMP (_max_temp);
  hi_lo=chk_min_max_set_value(_max);
  if (hi_lo==low_from_min_set_value && on_off==1)
  {
//   relay1=1;
  }
  else if (hi_lo==hi_from_min_set_value)
  {
   on_off=0;
   relay1=0;
  }
 }
}
//******************************************************************************
// unsigned char min_max_humi(unsigned char minmax)
//******************************************************************************
unsigned char min_max_humi(unsigned char minmax)
{
  unsigned char value_chk[3];

 if (minmax==0)
 {
  value_chk[0]=min_humi1[0];
  value_chk[1]=min_humi1[1];
  value_chk[2]=min_humi1[2];
 }
 else if (minmax==1)
 {
  value_chk[0]=max_humi1[0];
  value_chk[1]=max_humi1[1];
  value_chk[2]=max_humi1[2];
 }

 if (Humidity_buff[0]== value_chk[0])          //thou
 {
  if (Humidity_buff[1]== value_chk[1])         //ten
  {
    if (Humidity_buff[3]>= value_chk[2])        //after '.'
    {
     return hi_from_min_set_value;
    }
    else if (Humidity_buff[3]<= value_chk[2])
    {
  //   portc.b0=1;
       return low_from_min_set_value;
    }
    else if (Humidity_buff[3]== value_chk[2])
    {
     return equal;
    }
  }
  else if (Humidity_buff[1]> value_chk[1])
  {
//   portc.b0=0;
   return hi_from_min_set_value;
  }
   else if (Humidity_buff[1]< value_chk[1])
  {
//   portc.b0=1;
     return low_from_min_set_value;
  }
 }
 else if (Humidity_buff[0]> value_chk[0])
 {
//  portc.b0=0;
    return hi_from_min_set_value;
 }
 else if (Humidity_buff[0]< value_chk[0])
 {
//  portc.b0=1;
    return low_from_min_set_value;
 }
}

//******************************************************************************
// chk_humi()
//******************************************************************************
void chk_humi()
{
 Read_eeprm_MAX_MIN_TEMP(_min_humi);
 hi_lo_h=min_max_humi(_min);
// shorttostr(hi_lo_h,trt);
// lcd_out(2,1,trt);
 if (hi_lo_h==low_from_min_set_value)
 {
//  on_off_h=1;
//  lcd_out(2,10,"r2=1");
  relay2=1;
 }
else if (hi_lo_h==HI_from_min_set_value)
 {
  Read_eeprm_MAX_MIN_TEMP (_max_humi);
  hi_lo_h=min_max_humi(_max);
  if (hi_lo_h==low_from_min_set_value && on_off_h==1)
  {
//   relay2=1;
  }
  else if (hi_lo_h==hi_from_min_set_value)
  {
   on_off_h=0;
   relay2=0;
  }
 }

/*
  Read_eeprm_MAX_MIN_TEMP (_max_humi);
  hi_lo_h=min_max_humi(_max);
  if (hi_lo_h==low_from_min_set_value && on_off_h==1)
  {
   relay2=1;
  }
  else if (hi_lo_h==hi_from_min_set_value)
  {
   relay2=0;
  }
*/
}

#include "DS18S20.C"
#include "timer1.C"
#include "Keypad.C"


void main()
{
  disable_intr();
  adcon1=2;
  porta=0;
  trisb=255;
  portb=255;
  latb=255;
  trisa=255;
  TRISC=0;
  PORTC=0;
  LATC=0;
  TRISE=0;
  PORTE=0;
  LATE=0;
//  while(1);
  disable_intr();
  Timer1_OFF();
//  while(1);
  Lcd_Init();
  Keypad_Init();
  Lcd_Cmd(_LCD_CURSOR_OFF);
  Lcd_Out(1, 3, "TOUSEF AWAN");
  Lcd_Out(2, 1, "PH==03214777528");
  Delay_1sec();
  Delay_1sec();
  Lcd_Cmd(_LCD_CLEAR);

/*
  res = strcmp(txt,txt_sub);
  inttostr(res, textr);
  lcd_out(1,1,textr);while(1);
*/

/*
  while(1)
  {
   get_temp();
  }
*/
 TIMER_RUN();
  while(1)
 {
   humidity=get_humidity();
   new_humidity=humidity;
   Lcd_Out(1, 10,"RH ");
   floatToStr(new_humidity, Humidity_buff);
   Humidity_buff[2]='%';
   Humidity_buff[3]=0;
   Lcd_Out(1,13, Humidity_buff);
   chk_humi();
   get_temp();
   chk_temp();

   down_time();
   
   if (key_pad_digit()=='M')
   {
     CLS();
     Lcd_Out(1, 1, "ENTER PASSWORD");
     LCD_CMD(_LCD_SECOND_ROW);
     DELAY_MS(500);
     underline_on();
   do
  {
     while(1)
    {
        for (pp=0;pp<3;pp++)
        {
         password[pp]=key_pad();
         if (password[pp]=='C')
         {
          CLS();
          password[0]=0;password[1]=0;password[2]=0;
          exit1=1;
          break;
         }
         Lcd_Out_CP("*");
        }
      if (exit1!=1)
      {
        if (password[0]=='7'&& password[1]=='8'&& password[2]=='6')
        {
          CLS();
          Lcd_Out(1,1,"PASSWORD OK");
          DELAY_MS(1000);
          break;
        }
        else
        {
          CLS();
          Lcd_Out(1, 1, "ENTER PASSWORD");
          LCD_CMD(_LCD_SECOND_ROW);
          pp=0;
        }
      }
      else break;
     }
    if (exit1!=1)
    {
     disable_intr();
     Timer1_OFF();
     relay1=0;
     relay2=0;
     relay3=0;
     cls();
     Lcd_Out(1, 1, msg1);
     Lcd_Out(2, 1, msg2);
     Lcd_Out(2, 10,msg3);
     Keypad_Key_CLICK();
//******************************************************************************
       do{
       if (key_pad_digit()=='1')
       {
        Keypad_Key_CLICK();
        min_temperature_set();
        max_temperature_set();
        Lcd_Out(1, 1, msg1);
        Lcd_Out(2, 1, msg2);
        Lcd_Out(2, 10,msg3);
        back_bit=0;
       }
       if (key_pad_digit()=='2')
       {
        Keypad_Key_CLICK();
        min_humidity_set();
        max_humidity_set();
        Lcd_Out(1, 1, msg1);
        Lcd_Out(2, 1, msg2);
        Lcd_Out(2, 10,msg3);
        back_bit=0;
       }
       if (key_pad_digit()=='3')
       {
        Keypad_Key_CLICK();
        Time_setting();
        Lcd_Out(1, 1, msg1);
        Lcd_Out(2, 1, msg2);
        Lcd_Out(2, 10,msg3);
        back_bit=0;
       }
      }while(key_pad_digit()!='C');

//******************************************************************************
//     Get_on_first_off_first();
     TIMER_RUN();
     Timer1_ON();
     ii=0;
     break;
    }
    else
    {
     exit1=0;
     break;
    }
   }while(1);
   underline_oFF();
  }
 }
}
//******************************************************************************
// void interrupt() iv 0x000008
//******************************************************************************
void interrupt()
{

//************************************ Timer1 initial **************************
  if (PIE1.TMR1IE==1)
  {
    if (PIR1.TMR1IF==1)
    {
     PIR1.TMR1IF=0;
     if (mode==1)
     {
      if (on_time!=0)
       {
       relay3=1;
       if (ii==on_time)
       {
        mode=0;
        relay3=0;
        ii=0;
       }
       else 
       {
        ii++;
       }
      }
     }
     else if (mode==0)
     {
      if (off_time!=0)
      {
       relay3=0;
       if (ii==off_time)
       {
        mode=1;
        relay3=~relay3;
        ii=0;
       }
       else
       {
        ii++;
       }
      }
     }
     TMR1H = 0xB;     // preset for timer1 MSB register
     TMR1L = 0xDC;     // preset for timer1 LSB register
    }
  }
}