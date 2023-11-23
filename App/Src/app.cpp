/* Include section */
#include "app.hpp"

    /* FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"



/* Function that we call in main.c 
   Don't touch it
*/
extern "C" void app_c(void)
{
    app();
}


uint16_t pause = 1;


void vTaskCode( void * pvParameters )
{
    configASSERT( ( ( uint32_t ) pvParameters ) == 1 );

    for( ;; )
    {
    	HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    	vTaskDelay(pause);
        pause++;
    }
}

void app(void)
{
    xTaskCreate(vTaskCode,
		  	    "TestFunc",
			    24,
			    (void *) 1,
			    2,
			    NULL);


    vTaskStartScheduler();

    while (1)
    {

    }
}







