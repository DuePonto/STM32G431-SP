/* Includes ------------------------------------------------------------------ */
#include "app.hpp"

/* FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Peripherals*/
#include "mg996r_hal.hpp"
#include "mpu9255_hal.h"



/* Function that we call in main.c 
   Don't touch it
*/
extern "C" void app_c(void)
{
    app();
}


/* Variables ----------------------------------------------------------------- */
/* Externed structures from CubeMX */
extern ADC_HandleTypeDef hadc1;

extern I2C_HandleTypeDef hi2c2;

extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim15;

extern UART_HandleTypeDef huart2;



/* Global */
uint16_t pause = 100;
GPIO_PinState adc_x_state;
GPIO_PinState adc_y_state;
uint8_t who_am_i_mpu = 0;




/* Function prototypes ------------------------------------------------------- */
/* Tasks prototypes */

void vTaskServo( void * pvParameters );

void vTaskTouch( void * pvParameters );

void vTaskAccel( void * pvParameters );

void vTaskUART( void * pvParameters );




void app(void)
{

    /* Tasks creation ---------------------------- */

    /* Servo task */
    xTaskCreate(vTaskServo,
		  	    "ServoFunc",
			    180,
			    (void *) 1,
			    2,
			    NULL);

    /* Touch task */
    xTaskCreate(vTaskTouch,
                "TouchFunc",
                60,
                (void *) 1,
                2,
                NULL);

    /* Accelerometer task */
    xTaskCreate(vTaskAccel,
                "AccelFunc",
                60,
                (void *) 1,
                2,
                NULL);

    /* UART task */
    xTaskCreate(vTaskUART,
                "UARTFunc",
                60,
                (void *) 1,
                2,
                NULL);



    /* Start FreeRTOS kernel --------------------- */
    vTaskStartScheduler();

    while (1)
    {
        // Never should go here
    }
}





/* Tasks --------------------------------------------------------- */

/* Servo task */
void vTaskServo( void * pvParameters )
{
    // configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    // htim3.Instance->CCR1 = 1000;
    uint16_t ccr_min = 1000;

    float curr_ang = 0;

    mg996r_hal servo1(&htim3, &htim3.Instance->CCR1, TIM_CHANNEL_1);
    servo1.setAngRange(180, 0);
    servo1.setCCRRange(2350, 360);
    
    mg996r_hal servo2(&htim3, &htim3.Instance->CCR2, TIM_CHANNEL_2);
    servo2.setAngRange(180, 0);
    servo2.setCCRRange(2435, 450);

    mg996r_hal servo3(&htim3, &htim3.Instance->CCR3, TIM_CHANNEL_3);
    servo3.setAngRange(180, 0);
    servo3.setCCRRange(2400, 430);

    mg996r_hal servo4(&htim3, &htim3.Instance->CCR4, TIM_CHANNEL_4);
    servo4.setAngRange(180, 0);
    servo4.setCCRRange(2400, 430);

    mg996r_hal servo5(&htim15, &htim15.Instance->CCR1, TIM_CHANNEL_1);
    servo5.setAngRange(180, 0);
    servo5.setCCRRange(2435, 465);

    mg996r_hal servo6(&htim15, &htim15.Instance->CCR2, TIM_CHANNEL_2);
    servo6.setAngRange(180, 0);
    servo6.setCCRRange(2480, 490);

    servo1.start();
    servo2.start();
    servo3.start();
    servo4.start();
    servo5.start();
    servo6.start();

    for( ;; ){

        curr_ang += 10;
        if(curr_ang > 180){
            curr_ang = 0;
        }
        servo1.turnTo(curr_ang);
        servo2.turnTo(curr_ang);
        servo3.turnTo(curr_ang);
        servo4.turnTo(curr_ang);
        servo5.turnTo(curr_ang);
        servo6.turnTo(curr_ang);

        HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    	vTaskDelay(100);
    }
}



/* Touch task */
void vTaskTouch ( void * pvParameters ){

    // configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    HAL_GPIO_ReadPin(ADC_X_GPIO_Port, ADC_X_Pin);

    // HAL_ADCEx_Calibration_Start(&hadc1, );

    for( ;; ){

        adc_x_state = HAL_GPIO_ReadPin(ADC_X_GPIO_Port, ADC_X_Pin);
        adc_y_state = HAL_GPIO_ReadPin(ADC_Y_GPIO_Port, ADC_Y_Pin);
        vTaskDelay(100);

    }
}



/* Accelerometer task */
void vTaskAccel ( void * pvParameters ){

    volatile MPU_StatusTypeDef mpu_status = MPU_ERROR;
    MPU_HandleTypeDef mpu;
    mpu.i2c_ptr = &hi2c2;
    // uint8_t who_am_i_mpu = 0;

    HAL_I2C_Mem_Read(&hi2c2, MPU_I2C_ADDR_AD0_LOW << 1, WHO_AM_I, I2C_MEMADD_SIZE_8BIT, &who_am_i_mpu, 1, 100);
    mpu_status = MPU9255_check(&mpu);

    for( ;; ){
       
        mpu_status = MPU9255_check(&mpu);
        vTaskDelay(500);
        who_am_i_mpu = 5;
        vTaskDelay(500);
        
    }
}



/* UART task */
void vTaskUART ( void * pvParameters ){

    /* Enable IDLE interrupt for uart2 */

    __HAL_UART_ENABLE_IT(&huart2, UART_IT_IDLE);

    for( ;; ){



    }
}




/* Callbacks */

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
    if(huart->Instance == huart2.Instance){
        if(__HAL_UART_GET_IT(huart, UART_IT_IDLE)){
            
        }
    }
}