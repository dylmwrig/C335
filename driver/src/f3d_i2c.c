/* f3d_i2c.c --- 
 * 
 * Filename: f3d_i2c.c
 * Description: 
 * Author: Bryce Himebaugh
 * Maintainer: 
 * Created: Thu Oct 31 09:10:53 2013
 * Last-Updated: 
 *           By: 
 *     Update #: 0
 * Keywords: 
 * Compatibility: 
 * 
 */

/* Commentary: 
 * 
 * 
 * 
 */

/* Change log:
 * 
 * 
 */

/* Copyright (c) 2004-2007 The Trustees of Indiana University and 
 * Indiana University Research and Technology Corporation.  
 * 
 * All rights reserved. 
 * 
 * Additional copyrights may follow 
 */

/* Code: */

#include <f3d_i2c.h>
#include <f3d_delay.h>

void f3d_i2c1_init() {

}

void f3d_i2c1_read(uint8_t device, uint8_t reg, uint8_t* buffer, uint16_t numbytes) {

  while (I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET);                                   // Wait for I2C to become free

  I2C_TransferHandling(I2C1, device, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write);        // Send start and device address 
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET);                                   // Confirm that the transmitter empty

  if (numbytes>1) {
    reg |=0x80;                                                                             // indicate that the transfer will involve multiple bytes
  }
  I2C_SendData(I2C1,reg);                                                                   // Send the register address
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_TC) == RESET);                                   

  I2C_TransferHandling(I2C1, device, numbytes, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
  while (numbytes--) {
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_RXNE) == RESET);
    *buffer++ = I2C_ReceiveData(I2C1);
  }

  while (I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET);                                   // Wait for stop flag generation

  I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
}

void f3d_i2c1_write(uint8_t device, uint8_t reg, uint8_t* value) {
  
   while (I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET);

   I2C_TransferHandling(I2C1, device, 1, I2C_Reload_Mode, I2C_Generate_Start_Write);
   while (I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET); 

   I2C_SendData(I2C1,reg);
   while(I2C_GetFlagStatus(I2C1, I2C_ISR_TCR) == RESET);

   I2C_TransferHandling(I2C1, device, 1, I2C_AutoEnd_Mode, I2C_No_StartStop);
   while(I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET);

   I2C_SendData(I2C1, *value);
   while(I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET);

   I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
}

void f3d_i2c1_read_nunchuk (uint8_t device, uint8_t* buffer, uint16_t numbytes) {

  while (I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET);                                   
  I2C_TransferHandling(I2C1, 0xA4, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);          
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET);                                   
  I2C_SendData(I2C1,0x00);                                                                  
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET);
  I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
  delay(1);
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET);                                   
  I2C_TransferHandling(I2C1, 0xA4, 6, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
  while (numbytes--) {
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_RXNE) == RESET);
    *buffer++ = I2C_ReceiveData(I2C1);
  }
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET);                                  
  I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
}

/* f3d_i2c.c ends here */
