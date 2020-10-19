/* ========================================
 *
 * Assignment 03
 * Editor: Cristiano Bortolotti
 * File: MyFunction.h
 * Date: 15/10/2020 - 20/10/2020
 *
 * ========================================
*/

#include "project.h"

typedef struct { //statemente of color struct
    uint8_t red_value;
    uint8_t green_value;
    uint8_t blue_value;
} Color;

void start_peripherls(void); // statement of the function used to start peripherals

void start_ISR(void); // statement of the function used to enable and to start ISR

void v_response(void); // statement of the funtion used to group 'v' case

void error(uint8 type); // statement of error function

void LED_WriteColor (Color c); // statement

void correct_tail(void); // statement

void stop_Timer(void); // statement

void reset_Timer(void); // statement

/* [] END OF FILE */
