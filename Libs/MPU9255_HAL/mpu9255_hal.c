/* Includes ------------------------------------------------------------------*/
#include "mpu9255_hal.h"




/* ---------------------------- */
/* ----- PUBLIC FUNCTIONS ----- */
/* ---------------------------- */

MPU_StatusTypeDef MPU9255_check(MPU_HandleTypeDef *dev){
    volatile MPU_StatusTypeDef mpu_status = MPU_ERROR;
    uint8_t dev_id = 0;

    mpu_status = MPU9255_readRegs(dev, WHO_AM_I, &dev_id, 1);

    /* Check if I2C reading failed */
    if(mpu_status != MPU_OK){
        return mpu_status;
    }

    /* Check if device addres is different */
    if(dev_id != MPU9255_ADDR){
        return MPU_ERROR;
    } else {
        return MPU_OK;
    }
}




/* ----------------------------- */
/* ----- PRIVATE FUNCTIONS ----- */
/* ----------------------------- */

MPU_StatusTypeDef MPU9255_readRegs(MPU_HandleTypeDef *dev, mpu9255_registers reg_addr, uint8_t *buff, uint16_t len){
    return HAL_I2C_Mem_Read(dev->i2c_ptr, MPU_I2C_ADDR_CURRENT << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, buff, len, 100);
}





MPU_StatusTypeDef MPU9255_writeRegs(MPU_HandleTypeDef *dev, mpu9255_registers reg_addr, uint8_t *buff, uint16_t len){
    return HAL_I2C_Mem_Write(dev->i2c_ptr, MPU_I2C_ADDR_CURRENT << 1, reg_addr, I2C_MEMADD_SIZE_8BIT, buff, len, 100);
}


