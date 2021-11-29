// Set TEMP_RESOLUTION to the corresponding resolution of your DS18x20 sensor:
//  18S20: 9
//  18B20: 12 (default setting; can be 9,10,11,or 12)
const unsigned short TEMP_RESOLUTION = 12;

const int RES_FACTOR_1[4] = {5000, 2500, 1250, 625};
const unsigned int RES_FACTOR_2[4] = {0x0001, 0x0003, 0x0007, 0x000F};
const unsigned int RES_FACTOR_3[4] = {0x8000, 0xC000, 0xE000, 0xF000};

unsigned  temp;
unsigned short  j, RES_SHIFT;

void Display_Temperature(unsigned int temp) {
  const unsigned short RES_SHIFT = TEMP_RESOLUTION - 8;
  unsigned int temp_whole, temp_fraction;
  unsigned short i;
  char text[3];

//  temp+=20;
  // Isolate the fraction and make it a 4-digit decimal integer (for display)
  temp_fraction = temp & RES_FACTOR_2[RES_SHIFT - 1];
  temp_fraction = temp_fraction * RES_FACTOR_1[RES_SHIFT - 1];
  // Handle the whole part of temperature value
  temp_whole = temp;

  // Is temperature negative?
  if ((temp_whole & 0x8000) != 0u) i = 1;  // Yes, i = 1
  else i = 0;                              // No,  i = 0
  // Remove the fractional part
  temp_whole >>= RES_SHIFT;

  // Correct the sign if necessary
  if (i) temp_whole |= RES_FACTOR_3[RES_SHIFT - 1];

  new_temp=temp_whole;
  
  text[0] = (temp_whole/10)%10 + 48;             // Extract tens digit
  text[1] =  temp_whole%10     + 48;             // Extract ones digit
  text[2] =0;
  LCD_Out_CP( text);         // Print whole part on LCD
  LCD_Chr_CP('.');             // Print dot to separate fractional part

  TEXT_COMPARE[0]=TEXT[0];
  TEXT_COMPARE[1]=TEXT[1];
  TEXT_COMPARE[2]='.';
  text[0] =  temp_fraction/1000    + 48;         // Extract thousands digit
  text[1] =0;
  TEXT_COMPARE[3]=TEXT[0];
  
  LCD_Out_CP(text);            // Print fractional part on LCD

  LCD_Chr_CP(223);             // Print degree character
  LCD_Chr_CP('C');             // Print 'C' for Centigrades
}//~



void get_temp() 
{
  // Initialize LCD on PORTB and prepare for output
  LCD_Out(1, 1, "T ");
    OW_Reset(&PORTD,1);        // Onewire reset signal
    OW_Write(&PORTD,1,0xCC);   // Issue command SKIP_ROM
    OW_Write(&PORTD,1,0x44);   // Issue command CONVERT_T
    Delay_us(120);

    OW_Reset(&PORTD,1);
    OW_Write(&PORTD,1,0xCC);   // Issue command SKIP_ROM
    OW_Write(&PORTD,1,0xBE);   // Issue command READ_SCRATCHPAD
    Delay_ms(100);

    j = OW_Read(&PORTD,1);     // Get temperature LSB
    Delay_ms(100);
    temp = OW_Read(&PORTD,1);  // Get temperature MSB
    temp <<= 8; temp += j;     // Form the result
    Display_Temperature(temp); // Format and display result on LCD
    Delay_ms(400);
}