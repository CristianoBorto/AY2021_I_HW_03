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

#include "MyFunction.h"
#include "project.h"


void error(uint8 type)
{
    PWM_B_WriteCompare(0);
    PWM_RG_WriteCompare1(255);
    PWM_RG_WriteCompare2(0);
    switch(type)
    {
        case 0:
            UART_PutString("Error, please enter right values\r\n");
            break;
        case 1:
            UART_PutString("Error, timeout\r\n");
            break;
    }
    
    CyDelay(50); //questo tempo permette un lempeggiio percepibile senza creare problemi se si spamma una 
    // lettera
    // reimposta config in memoria
    PWM_B_WriteCompare(255);                
    PWM_RG_WriteCompare2(255);
    UART_ClearRxBuffer();
}

/* [] END OF FILE */
