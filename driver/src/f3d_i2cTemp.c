
void f3d_i2c1_init() {
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;

  GPIO_PinAFConfig(GPIOB, 6, GPIO_AF_4);
  GPIO_PinAFConfig(GPIOB, 7, GPIO_AF_4);

  GPIO_Init(GPIOB, &GPIO_InitStructure);


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

