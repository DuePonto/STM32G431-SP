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

uint16_t pause = 100;


void vTaskCode( void * pvParameters )
{
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );
    // htim3.Instance->CCR1 = 1000;
    htim3.Instance->CCR1 = 1500;
    htim3.Instance->CCR2 = 1500;
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);


    for( ;; )
    {
        if(htim3.Instance->CCR1 > 3000){
            htim3.Instance->CCR1 = 00;
        }
        if(htim3.Instance->CCR2 > 3000){
            htim3.Instance->CCR2 = 00;
        }

        htim3.Instance->CCR1 += 1;
        htim3.Instance->CCR2 += 1;
    	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    	vTaskDelay(1);
        pause++;
    }
}

// void TaskMG996 ( void * pvParameters )
// {
//     // configASSERT( ( ( uint32_t ) pvParameters ) == 2 );

//     float angle = 0; 
//     HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
//     mg996r_hal servo_1(&htim3, TIM_CHANNEL_1);
//     servo_1.setAngRange(280, 0);
//     servo_1.setCCRRange(1000, 500);

//     for( ;; )
//     {
//         angle += 10;
//         if(angle > 280){
//             angle = 0;
//         }
//         servo_1.turnTo(angle);
//     	vTaskDelay(100);
//     }
// }

void app(void)
{

    /* Task creation -----------*/
    xTaskCreate(vTaskCode,
		  	    "TestFunc",
			    24,
			    (void *) 1,
			    2,
			    NULL);

    // xTaskCreate(TaskMG996,
    //             "MG996_Func",
    //             128,
    //             (void *) 2,
    //             1,
    //             NULL);


    // HAL_TIM_PWM_Start();

    vTaskStartScheduler();

    while (1)
    {

    }
}







