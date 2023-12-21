#ifndef __MPU9255_HAL
#define __MPU9255_HAL

#ifdef __cplusplus
    extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Defines -------------------------------------------------------------------*/
#define MPU_I2C_ADDR_AD0_HIGH 0b01101001
#define MPU_I2C_ADDR_AD0_LOW 0b01101000
#define MPU_I2C_ADDR_CURRENT  MPU_I2C_ADDR_AD0_LOW

#define MPU9255_ADDR 0x73U


/* Typedefs ------------------------------------------------------------------*/

typedef enum{
    SELF_TEST_X_GYRO = 0x00,
    SELF_TEST_Y_GYRO = 0x01,
    SELF_TEST_Z_GYRO = 0x02,
    SELF_TEST_X_ACCEL = 0x0D,
    SELF_TEST_Y_ACCEL = 0x0E,
    SELF_TEST_Z_ACCEL = 0x0F,
    XG_OFFSET_H = 0x13,
    XG_OFFSET_L = 0x14,
    YG_OFFSET_H = 0x15,
    YG_OFFSET_L = 0x16,
    ZG_OFFSET_H = 0x17,
    ZG_OFFSET_L = 0x18,
    SMPLRT_DIV = 0x19,
    CONFIG = 0x1A,
    GYRO_CONFIG = 0x1B,
    ACCEL_CONFIG = 0x1C,
    ACCEL_CONFIG_2 = 0x1D,
    LP_ACCEL_ODR = 0x1E,
    WOM_THR = 0x1F,
    FIFO_EN = 0x23,
    I2C_MST_CTRL = 0x24,
    I2C_SLV0_ADDR = 0x25,
    I2C_SLV0_REG = 0x26,
    I2C_SLV0_CTRL = 0x27,
    I2C_SLV1_ADDR = 0x28,
    I2C_SLV1_REG = 0x29,
    I2C_SLV1_CTRL = 0x2A,
    I2C_SLV2_ADDR = 0x2B,
    I2C_SLV2_REG = 0x2C,
    I2C_SLV2_CTRL = 0x2D,
    I2C_SLV3_ADDR = 0x2E,
    I2C_SLV3_REG = 0x2F,
    I2C_SLV3_CTRL = 0x30,
    I2C_SLV4_ADDR = 0x31,
    I2C_SLV4_REG = 0x32,
    I2C_SLV4_DO = 0x33,
    I2C_SLV4_CTRL = 0x34,
    I2C_SLV4_DI = 0x35,
    I2C_MST_STATUS = 0x36,
    INT_PIN_CFG = 0x37,
    INT_ENABLE = 0x38,
    INT_STATUS = 0x3A,
    ACCEL_XOUT_H = 0x3B,
    ACCEL_XOUT_L = 0x3C,
    ACCEL_YOUT_H = 0x3D,
    ACCEL_YOUT_L = 0x3E,
    ACCEL_ZOUT_H = 0x3F,
    ACCEL_ZOUT_L = 0x40,
    TEMP_OUT_H = 0x41,
    TEMP_OUT_L = 0x42,
    GYRO_XOUT_H = 0x43,
    GYRO_XOUT_L = 0x44,
    GYRO_YOUT_H = 0x45,
    GYRO_YOUT_L = 0x46,
    GYRO_ZOUT_H = 0x47,
    GYRO_ZOUT_L = 0x48,
    /* EXT_SENS_DATA regs [0x49;0x60] */
    I2C_SLV0_DO = 0x63,
    I2C_SLV1_DO = 0x64,
    I2C_SLV2_DO = 0x65,
    I2C_SLV3_DO = 0x66,
    I2C_MST_DELAY_CTRL = 0x67,
    SIGNAL_PATH_RESET = 0x68,
    MOT_DETECT_CTRL = 0x69,
    USER_CTRL = 0x6A,
    PWR_MGMT_1 = 0x6B,
    PWR_MGMT_2 = 0x6C,
    FIFO_COUNTH = 0x72,
    FIFO_COUNTL = 0x73,
    FIFO_R_W = 0x74,
    WHO_AM_I = 0x75,
    XA_OFFSET_H = 0x77,
    XA_OFFSET_L = 0x78,
    YA_OFFSET_H = 0x7A,
    YA_OFFSET_L = 0x7B,
    ZA_OFFSET_H = 0x7D,
    ZA_OFFSET_L = 0x7E
}mpu9255_registers;

typedef enum{
    MPU_OK          = 0x00U,
    MPU_ERROR       = 0x01U,
    MPU_BUSY        = 0x02U,
    MPU_TIMEOUT     = 0x03U,
    // ANOTHER_DEVICE  = 0xFFU
}MPU_StatusTypeDef;

typedef struct{
    I2C_HandleTypeDef   *i2c_ptr;
}MPU_HandleTypeDef;



/* Functions -----------------------------------------------------------------*/
/* Public */
MPU_StatusTypeDef MPU9255_check(MPU_HandleTypeDef *dev);

/* Private */
MPU_StatusTypeDef MPU9255_readRegs(MPU_HandleTypeDef *dev, mpu9255_registers reg_addr, uint8_t *buff, uint16_t len);
MPU_StatusTypeDef MPU9255_writeRegs(MPU_HandleTypeDef *dev, mpu9255_registers reg_addr, uint8_t *buff, uint16_t len);


#ifdef __cplusplus
    }
#endif

#endif /* __MPU9255_HAL */