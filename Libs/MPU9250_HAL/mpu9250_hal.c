/* Includes ------------------------------------------------------------------*/
#include "mpu9250_hal.h"






mpu9250_status mpu9250_readRegs(mpu9250_HandleTypeDef *dev, mpu9250_registers reg_addr, uint8_t *buff, uint8_t len){
    return HAL_I2C_Mem_Read(dev->i2c_ptr, MPU_I2C_ADDR_AD0_HIGH << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, buff, len, 100);
}





mpu9250_status mpu9250_writeRegs(mpu9250_HandleTypeDef *dev, mpu9250_registers reg_addr, uint8_t *buff, uint8_t len){

}


