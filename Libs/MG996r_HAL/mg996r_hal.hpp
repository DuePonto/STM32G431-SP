#ifndef __MG996R_HAL
#define __MG996R_HAL


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "math.h"

typedef enum{
    mg_ok,
    mg_error,
    mg_out_of_range,
}mg996r_status;


/* Declarations and definitions ----------------------------------------------*/
class mg996r_hal {
private:
    TIM_HandleTypeDef   *tim;
    uint32_t            tim_channel;

    float ang_max;
    float ang_min;
    float ang_range;
    uint16_t ang_max_ccr;
    uint16_t ang_min_ccr;
    uint16_t ang_range_ccr;
    float curr_ang;
public:
    mg996r_hal(TIM_HandleTypeDef *tim, uint32_t tim_channel){
        this->tim = tim;
        this->tim_channel = tim_channel;
    };

    mg996r_status setAngRange(float ang_max, float ang_min);
    mg996r_status setCCRRange(uint16_t ang_max_ccr, uint16_t ang_min_ccr);
    mg996r_status turnTo(float ang);
};


#endif /* __MG996R_HAL */