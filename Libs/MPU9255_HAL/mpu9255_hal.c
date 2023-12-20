/* Includes ------------------------------------------------------------------*/
#include "mpu9255_hal.h"






mpu9255_status MPU9255_readRegs(mpu9255_HandleTypeDef *dev, mpu9255_registers reg_addr, uint8_t *buff, uint16_t len){
    HAL_I2C_Mem_Read(dev->i2c_ptr, MPU_I2C_ADDR_AD0_LOW << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, buff, len, 100);
    return MPU_OK;
}





mpu9255_status MPU9255_writeRegs(mpu9255_HandleTypeDef *dev, mpu9255_registers reg_addr, uint8_t *buff, uint16_t len){

}


