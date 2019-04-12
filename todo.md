``
FLASH_ARRAY (boolean, SCEIData, 1,0,0,1,1,0,1,0,1,0,0,1,0,0,1,1,1,1,0,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,1,1,0,1,1,0,1,0,0);      //SCEI: 1 00110101 00, 1 00111101 00, 1 01011101 00, 1 01101101 00

int bit_counter;
  
  for (bit_counter = 0; bit_counter < 44; bit_counter = bit_counter + 1)
  {
      if (SCEIData[bit_counter] == 0)
      {
          pinMode(data, OUTPUT);
          digitalWrite(data, 0);
          delay(delay_between_bits);
      }
      else
      {
          pinMode(data, INPUT);                //We make the data pin high-impedance to let the pull-up of the Playstation motherboard make a 1
          delay(delay_between_bits);
      }
  }
  
  ``
