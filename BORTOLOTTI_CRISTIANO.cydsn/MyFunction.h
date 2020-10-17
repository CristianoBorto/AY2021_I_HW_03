/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "project.h"

typedef struct {
    uint8_t red_value;
    uint8_t green_value;
    uint8_t blue_value;
} Color;

void start_peripherls(void);

void start_ISR(void);

void error(uint8 type);

void LED_WriteColor (Color c);

void v_response(void);

void correct_tail(void);

void stop_Timer(void);

void reset_Timer(void);

/* [] END OF FILE */
