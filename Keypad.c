//unsigned short hms_pos[]={1,2,3,4,5,6,7,8};

//******************************************************************************
// key_pad()
//******************************************************************************
unsigned short key_pad()
{
 unsigned short kp;
// Wait for key to be pressed and released
 do
// kp = Keypad_Key_Press();           // Store key code in kp variable
   kp = Keypad_Key_Click();           // Store key code in kp variable
 while(!kp);
// Prepare value for output, transform key to it's ASCII value
 switch (kp)
 {
  case  1: kp = 49; break; //
  case  2: kp = 52; break; //
  case  3: kp = 55; break; //
  case  4: kp = 83; break; //
  case  5: kp = 50; break; //
  case  6: kp = 53; break; //
  case  7: kp = 56; break; //
  case  8: kp = 48; break; //
  case  9: kp = 51; break; //
  case 10: kp = 54; break; //
  case 11: kp = 57; break; //
  case 12: kp = 67; break; //
  case 13: kp = 85; break; //
  case 14: kp = 68; break; //
  case 15: kp = 77; break; //
  case 16: kp = 69; break; //
 }
 return kp;
}
//******************************************************************************
// key_pad_digit()
//******************************************************************************
unsigned char key_pad_digit()
{
 unsigned kp;
kp = Keypad_Key_Press();
 switch (kp)
 {
  case  1: kp = 49; break; //
  case  2: kp = 52; break; //
  case  3: kp = 55; break; //
  case  4: kp = 83; break; //
  case  5: kp = 50; break; //
  case  6: kp = 53; break; //
  case  7: kp = 56; break; //
  case  8: kp = 48; break; //
  case  9: kp = 51; break; //
  case 10: kp = 54; break; //
  case 11: kp = 57; break; //
  case 12: kp = 67; break; //
  case 13: kp = 85; break; //
  case 14: kp = 68; break; //
  case 15: kp = 77; break; //
  case 16: kp = 69; break; //
 }
 return kp;
}
//******************************************************************************
// max
//******************************************************************************
void max_temperature_set()
{
 if (back_bit!=exit)
 {
  Digit_position=0;
  cls();
  lcd_out(1,1,"Max TEMP");

  max_temp[0]=EEPROM_Read(21);
  max_temp[1]=EEPROM_Read(22);
  max_temp[2]='.';
  max_temp[3]=EEPROM_Read(23);
  max_temp[4]=0;
  max_temp1[0]=max_temp[0];
  max_temp1[1]=max_temp[1];
  max_temp1[2]=max_temp[3];

  lcd_out(2,1,max_temp);
  lcd_cmd(_LCD_SECOND_ROW);
    do
   {
    key_pad_data=key_pad();
    edit_key_pad_data=key_pad_data;
    edit_key_pad_data &=0xf0;
    if (edit_key_pad_data==0x30)
    {
     max_temp1[Digit_position]=key_pad_data;
     lcd_chr_cp(key_pad_data);
     Digit_position+=1;
    }
    if (Digit_position==2)
    {
     move_right();
    }
    if (Digit_position==3)
    {
     Digit_position=0;
     lcd_cmd(_LCD_SECOND_ROW);
    }
    if (key_pad_data=='E')
    {
     lcd_out(1,1,"     SET value");
     max_temp1[3]=0;
     lcd_out(1,1,max_temp1);
     Digit_position=0;
     EEPROM_Write(21, max_temp1[0]);
     EEPROM_Write(22, max_temp1[1]);
     EEPROM_Write(23, max_temp1[2]);
     delay_ms(1000);
     cls();
     break;
    }
    if (key_pad_data=='C')
    {
     cls();
     lcd_out(1,1,"Cancle");
     delay_ms(500);
     cls();
  //   underline_off();
     break;
    }
    if (key_pad_data=='M')
    {
     cls();
     lcd_out(1,1,"Back");
     delay_ms(500);
     cls();
     back_bit=exit;
     break;
    }
   }while(1);
 }
}

//******************************************************************************
// Min
//******************************************************************************

void min_temperature_set()
{
 if (back_bit!=exit)
 {
  Digit_position=0;
  cls();
  lcd_out(1,1,"Min TEMP");

  min_temp[0]=EEPROM_Read(11);
  min_temp[1]=EEPROM_Read(12);
  min_temp[2]='.';
  min_temp[3]=EEPROM_Read(13);
  min_temp[4]=0;
  min_temp1[0]=min_temp[0];
  min_temp1[1]=min_temp[1];
  min_temp1[2]=min_temp[3];
/*
  min_temp[0]='0';
  min_temp[1]='0';
  min_temp[2]='.';
  min_temp[3]='0';
  min_temp[4]=0;
*/
  lcd_out(2,1,min_temp);
  lcd_cmd(_LCD_SECOND_ROW);
    do
   {
    key_pad_data=key_pad();
    edit_key_pad_data=key_pad_data;
    edit_key_pad_data &=0xf0;
    if (edit_key_pad_data==0x30)
    {
     min_temp1[Digit_position]=key_pad_data;
     lcd_chr_cp(key_pad_data);
     Digit_position+=1;
    }
    if (Digit_position==2)
    {
     move_right();
    }
    if (Digit_position==3)
    {
     Digit_position=0;
     lcd_cmd(_LCD_SECOND_ROW);
    }
    if (key_pad_data=='E')
    {
     lcd_out(1,1,"     SET value");
     min_temp1[3]=0;
     lcd_out(1,1,min_temp1);
  ///   Delay_1sec();
     Digit_position=0;
     EEPROM_Write(11, min_temp1[0]);
     EEPROM_Write(12, min_temp1[1]);
     EEPROM_Write(13, min_temp1[2]);
     delay_ms(1000);
     cls();
     break;
    }
    if (key_pad_data=='C')
    {
     cls();
     lcd_out(1,1,"Cancle");
     delay_ms(400);
     cls();
  //   underline_off();
     break;
    }
      if (key_pad_data=='M')
    {
     cls();
     lcd_out(1,1,"Back");
     delay_ms(500);
     cls();
     back_bit=1;
     break;
    }
   }while(1);
 }
}
//******************************************************************************
// min_humidity_set();
//******************************************************************************
void min_humidity_set()
{
 if(back_bit!=exit)
 {
  Digit_position=0;
  cls();
  lcd_out(1,1,"Min Humidity");

  min_humi[0]=EEPROM_Read(31);
  min_humi[1]=EEPROM_Read(32);
  min_humi[2]='.';
  min_humi[3]=EEPROM_Read(33);
  min_humi[4]=0;
  min_humi1[0]=min_humi[0];
  min_humi1[1]=min_humi[1];
  min_humi1[2]=min_humi[3];
  lcd_out(2,1,min_humi);
  lcd_cmd(_LCD_SECOND_ROW);
    do
   {
    key_pad_data=key_pad();
    edit_key_pad_data=key_pad_data;
    edit_key_pad_data &=0xf0;
    if (edit_key_pad_data==0x30)
    {
     min_humi1[Digit_position]=key_pad_data;
     lcd_chr_cp(key_pad_data);
     Digit_position+=1;
    }
    if (Digit_position==2)
    {
     move_right();
    }
    if (Digit_position==3)
    {
     Digit_position=0;
     lcd_cmd(_LCD_SECOND_ROW);
    }
    if (key_pad_data=='E')
    {
     lcd_out(1,1,"     SET value");
     min_humi1[3]=0;
     lcd_out(1,1,min_humi1);
  ///   Delay_1sec();
     Digit_position=0;
     EEPROM_Write(31, min_humi1[0]);
     EEPROM_Write(32, min_humi1[1]);
     EEPROM_Write(33, min_humi1[2]);
     delay_ms(1000);
     cls();
     break;
    }
    if (key_pad_data=='C')
    {
     cls();
     lcd_out(1,1,"Cancle");
     delay_ms(400);
     cls();
     break;
    }
      if (key_pad_data=='M')
    {
     cls();
     lcd_out(1,1,"Back");
     delay_ms(500);
     cls();
     back_bit=1;
     break;
    }
   }while(1);
 }
}
//******************************************************************************
// max_humidity_set();
//******************************************************************************
void max_humidity_set()
{
  if (back_bit!=exit)
  {
    Digit_position=0;
    cls();
    lcd_out(1,1,"Max Humidity");

    max_humi[0]=EEPROM_Read(41);
    max_humi[1]=EEPROM_Read(42);
    max_humi[2]='.';
    max_humi[3]=EEPROM_Read(43);
    max_humi[4]=0;
    max_humi1[0]=max_humi[0];
    max_humi1[1]=max_humi[1];
    max_humi1[2]=max_humi[3];
  /*
    max_humi[0]='0';
    max_humi[1]='0';
    max_humi[2]='.';
    max_humi[3]='0';
    max_humi[4]=0;
  */
    lcd_out(2,1,max_humi);
    lcd_cmd(_LCD_SECOND_ROW);
    do
   {
    key_pad_data=key_pad();
    edit_key_pad_data=key_pad_data;
    edit_key_pad_data &=0xf0;
    if (edit_key_pad_data==0x30)
    {
     max_humi1[Digit_position]=key_pad_data;
     lcd_chr_cp(key_pad_data);
     Digit_position+=1;
    }
    if (Digit_position==2)
    {
     move_right();
    }
    if (Digit_position==3)
    {
     Digit_position=0;
     lcd_cmd(_LCD_SECOND_ROW);
    }
    if (key_pad_data=='E')
    {
     lcd_out(1,1,"     SET value");
     max_humi1[3]=0;
     lcd_out(1,1,max_humi1);
     Digit_position=0;
     EEPROM_Write(41, max_humi1[0]);
     EEPROM_Write(42, max_humi1[1]);
     EEPROM_Write(43, max_humi1[2]);
     delay_ms(1000);
     cls();
     break;
    }
    if (key_pad_data=='C')
    {
     cls();
     lcd_out(1,1,"Cancle");
     delay_ms(400);
     cls();
     break;
    }
    if (key_pad_data=='M')
    {
     cls();
     lcd_out(1,1,"Back");
     delay_ms(500);
     cls();
     back_bit=1;
     break;
    }
   }while(1);
 }
}

//******************************************************************************
void  read_eeprom_on_time(char red_on)
{
 if (red_on==_read_on)
 {
  Save_time[0]=EEPROM_Read(51);
  Save_time[1]=EEPROM_Read(52);
  Save_time[2]=EEPROM_Read(53);
  Save_time[3]=EEPROM_Read(54);
  Save_time[4]=EEPROM_Read(55);
  Save_time[5]=EEPROM_Read(56);
  save_time[6]=0;
 }
 if (red_on==_read_off)
 {
  Save_time[0]=EEPROM_Read(61);
  Save_time[1]=EEPROM_Read(62);
  Save_time[2]=EEPROM_Read(63);
  Save_time[3]=EEPROM_Read(64);
  Save_time[4]=EEPROM_Read(65);
  Save_time[5]=EEPROM_Read(66);
  save_time[6]=0;
 }
}

void display_time( char on_off_time)
{
 if (on_off_time==_read_on)
 {
  lcd_out(1,1,"TURNER ON TIME");
  read_eeprom_on_time(_read_on);
  SAV_Display_time[0]=Save_time[0];
  SAV_Display_time[1]=Save_time[1];
  SAV_Display_time[2]=':';
  SAV_Display_time[3]=Save_time[2];
  SAV_Display_time[4]=Save_time[3];
  SAV_Display_time[5]=':';
  SAV_Display_time[6]=Save_time[4];
  SAV_Display_time[7]=Save_time[5];
  SAV_Display_time[8]=0;
  lcd_out(2,1,SAV_Display_time);
 }
 if (on_off_time==_read_off)
 {
  lcd_out(1,1,"TURNER OFF TIME");
  read_eeprom_on_time(_read_off);
  SAV_Display_time[0]=Save_time[0];
  SAV_Display_time[1]=Save_time[1];
  SAV_Display_time[2]=':';
  SAV_Display_time[3]=Save_time[2];
  SAV_Display_time[4]=Save_time[3];
  SAV_Display_time[5]=':';
  SAV_Display_time[6]=Save_time[4];
  SAV_Display_time[7]=Save_time[5];
  SAV_Display_time[8]=0;
  lcd_out(2,1,SAV_Display_time);
 }
}
//******************************************************************************
// void input_data(short _save ) TIMER SETTING
//******************************************************************************

void input_data(short _save )
{
 if (back_bit!=exit)
 {
  lcd_cmd(_LCD_SECOND_ROW);
  Digit_position=0;
   do
   {
    key_pad_data=key_pad();
    edit_key_pad_data=key_pad_data;
    edit_key_pad_data &=0xf0;
    if (edit_key_pad_data==0x30)
    {
     save_time[Digit_position]=key_pad_data;
     lcd_chr_cp(key_pad_data);
     Digit_position++;
    }
    if (Digit_position==2 || Digit_position==4)
    {
     lcd_chr_cp(':');
    }
    if (Digit_position==6)
    {
     Digit_position=0;
     lcd_cmd(_LCD_SECOND_ROW);
    }
    if (key_pad_data=='E')
    {
     lcd_out(1,1,"       SET value");
     SAVE_TIME[8]=0;
     lcd_out(1,1,save_time);
     Digit_position=0;
     if (_save==_save_on)
     {
      EEPROM_Write(51, SAVE_TIME[0]);
      EEPROM_Write(52, SAVE_TIME[1]);
      EEPROM_Write(53, SAVE_TIME[2]);
      EEPROM_Write(54, SAVE_TIME[3]);
      EEPROM_Write(55, SAVE_TIME[4]);
      EEPROM_Write(56, SAVE_TIME[5]);
     }
     else if (_save==_save_off)
     {
      EEPROM_Write(61, SAVE_TIME[0]);
      EEPROM_Write(62, SAVE_TIME[1]);
      EEPROM_Write(63, SAVE_TIME[2]);
      EEPROM_Write(64, SAVE_TIME[3]);
      EEPROM_Write(65, SAVE_TIME[4]);
      EEPROM_Write(66, SAVE_TIME[5]);
     }
     delay_ms(2000);
     cls();
     break;
    }
    if (key_pad_data=='C')
    {
     cls();
     lcd_out(1,1,"Cancle");
     delay_ms(500);
     cls();
     break;
    }
    if (key_pad_data=='M')
    {
     cls();
     lcd_out(1,1,"Back");
     delay_ms(500);
     cls();
     back_bit=1;
     break;
    }
   }while(1);
 }
}
//******************************************************************************
// Time_setting();
//******************************************************************************
void Time_setting()
{
 cls();
 display_time(_read_on);
 input_data(_save_on);

 DISPLAY_TIME(_read_oFF);
 input_data(_save_oFF);
}

// long strtochr_timer(unsigned char read_on_off_timer)
long strtochr_timer(unsigned char read_on_off_timer)
{
 if (read_on_off_timer==_read_on_timer)
 {
  read_eeprom_on_time(_read_on);
  se=0;
  se=Save_time[4]&0x0f;
  se<<=4;
  se|=Save_time[5]&0x0f;
  se=Bcd2Dec(se);
//  shorttostr(sec,trt);
//  lcd_out(1,8,trt);

  mi=0;
  mi=Save_time[2]&0x0f;
  mi<<=4;
  mi|=Save_time[3]&0x0f;
  mi=Bcd2Dec(mi);
//  horttostr(min,trt);
//  lcd_out(1,5,trt);

  hor=0;
  hor=Save_time[0]&0x0f;
  hor<<=4;
  hor|=Save_time[1]&0x0f;
  hor=Bcd2Dec(hor);
//  shorttostr(hr,trt);
//  lcd_out(1,1,trt);
  sec_coverted=hor*60;
  sec_coverted*=60;
  sec_coverted+=mi*60;
  sec_coverted+=se;
  cls();
  longtostr(sec_coverted,trt);
  lcd_out(2,1,trt);
  lcd_out(1,1,"TURNER ON TIME");
  delay_ms(1000);
  cls();
  return sec_coverted;
 }
 
 if (read_on_off_timer==_read_off_timer)
 {
  read_eeprom_on_time(_read_off);
  se=0;
  se=Save_time[4]&0x0f;
  se<<=4;
  se|=Save_time[5]&0x0f;
  se=Bcd2Dec(se);
//  shorttostr(sec,trt);
//  lcd_out(1,8,trt);

  mi=0;
  mi=Save_time[2]&0x0f;
  mi<<=4;
  mi|=Save_time[3]&0x0f;
  mi=Bcd2Dec(mi);
//  shorttostr(min,trt);
//  lcd_out(1,5,trt);

  hor=0;
  hor=Save_time[0]&0x0f;
  hor<<=4;
  hor|=Save_time[1]&0x0f;
  hor=Bcd2Dec(hor);
//  shorttostr(hr,trt);
//  lcd_out(1,1,trt);
  sec_coverted=hor*60;
  sec_coverted*=60;
  sec_coverted+=mi*60;
  sec_coverted+=se;

  cls();
  longtostr(sec_coverted,trt);
  lcd_out(2,1,trt);
  lcd_out(1,1,"TURNER OFF TIMER");
  delay_ms(1000);
  cls();
  return sec_coverted;
 }
}
void TIMER_RUN()
{
 cls();
 on_time=strtochr_timer(_read_on_timer);
 off_time=strtochr_timer(_read_off_timer);
 on_time/=.10;
 off_time/=.10;
 Timer1_init();
 Timer1_Enable();
 Enable_intr();
 Timer1_ON();

}

void down_time()
{
 if (relay3==0)
 {
  lcd_out(2,1,"TURNER OFF");
 }
 else if(relay3==1)
 {
  lcd_out(2,1,"TURNER ON ");
 }
 if (relay2==0)
 {
//  lcd_out(2,7,"R2Of");
 }
 else if (relay2==1)

 {
//  lcd_out(2,7,"R2On");
 }
 if (relay1==0)
 {
//  lcd_out(2,13,"R1Of");
 }
 else if (relay1==1)
 {
//  lcd_out(2,13,"R1On");
 }
}

void Get_on_first_off_first()
{
 /*
 if (first_onfirst_off==1)
 {
  mode=1;
 }
 else if (first_onfirst_off==0)
 {
  mode=0;
 }
 */
}
 void TIMER1_START()
{
  Timer1_ON();
  Enable_intr();
}