#ifndef __MG996R_HAL
#define __MG996R_HAL


/* Includes ------------------------------------------------------------------*/
#include "main.h"
// #include "math.h"

typedef enum{
    mg_ok,
    mg_error,
    mg_out_of_range,
}mg996r_status;


/* Declarations and definitions ----------------------------------------------*/
class mg996r_hal {
private:
    TIM_HandleTypeDef   *tim;
    volatile uint32_t            *tim_ccr;
    uint32_t            tim_channel;

    float ang_max = 0;
    float ang_min = 0;
    float ang_range = 0;
    uint16_t ang_max_ccr = 0;
    uint16_t ang_min_ccr = 0;
    uint16_t ang_range_ccr = 0;
    float curr_ang = 0;
public:
    

    mg996r_hal(TIM_HandleTypeDef *tim, volatile uint32_t *ccr, uint32_t tim_channel){
        this->tim = tim;
        this->tim_channel = tim_channel;
        this->tim_ccr = ccr;
    };

    void start(){
        HAL_TIM_PWM_Start(this->tim, this->tim_channel);
    }

    void stop(){
        HAL_TIM_PWM_Stop(this->tim, this->tim_channel);
    }
    mg996r_status setAngRange(float ang_max, float ang_min);
    mg996r_status setCCRRange(uint16_t ang_max_ccr, uint16_t ang_min_ccr);
    mg996r_status turnTo(float ang);
};


#endif /* __MG996R_HAL */