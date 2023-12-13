/* Includes ------------------------------------------------------------------*/
#include "app.hpp"

/* FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

/* Peripheral*/
#include "mg996r_hal.hpp"


/* Function that we call in main.c 
   Don't touch it
*/
extern "C" void app_c(void)
{
    app();
}


/* Variables ------------------------------------------------------------------*/
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;

uint16_t pause = 100;





void app(void)
{

    /* Tasks creation -----------*/

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


    /* Start FreeRTOS kernel */
    vTaskStartScheduler();

    while (1)
    {

    }
}





/* Tasks --------------------------------------------------------- */

/* Servo task */
void vTaskServo( void * pvParameters )
{
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
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

    mg996r_hal servo5(&htim4, &htim4.Instance->CCR1, TIM_CHANNEL_1);
    servo5.setAngRange(180, 0);
    servo5.setCCRRange(2435, 465);

    mg996r_hal servo6(&htim4, &htim4.Instance->CCR2, TIM_CHANNEL_2);
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

    for( ;; ){
        
    }
}