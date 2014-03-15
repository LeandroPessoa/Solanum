#include <msp430.h>



void initFlash()
{

FCTL2 = FWKEY + FSSEL1 + FN2; 

}
unsigned char data_buffer[64] = "teste!";

unsigned char data_dump[64] = "teste!";

void writeSegC(char *value)
{
_DINT();                             // Disable interrupts(IAR workbench).
 char *Flash_ptr;                          // Flash pointer
  unsigned int i;

  Flash_ptr = (char *) 0x1040;              // Initialize Flash pointer
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash segment

  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptr++ = *value++;                   // Write value to flash
   
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;   
  _EINT();
}

void writeSegD(char *value)
{
_DINT();                             // Disable interrupts(IAR workbench).
 char *Flash_ptr;                          // Flash pointer
  unsigned int i;

  Flash_ptr = (char *) 0x1000;              // Initialize Flash pointer
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash segment

  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptr++ = *value++;                   // Write value to flash
   
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;   
  _EINT();
}

void writeFlag(char *value)
{
_DINT();                             // Disable interrupts(IAR workbench).
 char *Flash_ptr;                          // Flash pointer
  unsigned int i;

  Flash_ptr = (char *) 0x1080;              // Initialize Flash pointer
  FCTL1 = FWKEY + ERASE;                    // Set Erase bit
  FCTL3 = FWKEY;                            // Clear Lock bit
  *Flash_ptr = 0;                           // Dummy write to erase Flash segment

  FCTL1 = FWKEY + WRT;                      // Set WRT bit for write operation

  for (i=0; i<64; i++)
  {
    *Flash_ptr++ = *value;                   // Write value to flash
   
  }

  FCTL1 = FWKEY;                            // Clear WRT bit
  FCTL3 = FWKEY + LOCK;   
  _EINT();
}

char readFlag()
{
  char *Flash_ptr;
  Flash_ptr = (char *) 0x1080;

  
  return *Flash_ptr;
  
}

char readAddress(unsigned int address)
{
  char *Flash_ptr;
  Flash_ptr = (char *) 0x1000+address;

  
  return *Flash_ptr;
  
}