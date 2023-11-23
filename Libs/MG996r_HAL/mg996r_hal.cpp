/* Includes ------------------------------------------------------------------*/
#include "mg996r_hal.hpp"
#include <stdio.h>

/* Functions  ----------------------------------------------------------------*/
mg996r_status mg996r_hal::setAngRange(float ang_max, float ang_min){
    if(ang_max < ang_min){
        return mg_error;
    }

    this->ang_max = ang_max;
    this->ang_min = ang_min;
    this->ang_range = this->ang_max - this->ang_min;

    return mg_ok;
}



mg996r_status mg996r_hal::setCCRRange(uint16_t ang_max_ccr, uint16_t ang_min_ccr){
    if(ang_max_ccr < ang_min_ccr){
        return mg_error;
    }

    this->ang_max_ccr = ang_max_ccr;
    this->ang_min_ccr = ang_min_ccr;
    this->ang_range_ccr = this->ang_max_ccr - this->ang_min_ccr;
}



mg996r_status mg996r_hal::turnTo(float ang){
    // Check for range
    if(ang < this->ang_min || ang > this->ang_max){
        return mg_out_of_range;
    }

    float temp_ang;
    temp_ang = ang - this->ang_min;
    temp_ang = temp_ang/this->ang_range;

    float temp_ccr;
    temp_ccr = temp_ang * this->ang_range_ccr;

    this->tim->Instance->CCR1 = temp_ccr;
}