/* ========================================
 *
 * Assignment 03
 * Editor: Cristiano Bortolotti
 * File: main.c
 * Date: 15/10/2020 - 20/10/2020
 * 
 * ========================================
*/
#include "project.h"
#include "MyISR.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    ISR_UART_StartEx(Custom_UART_RX_ISR);
    ISR_Timer_StartEx(Custom_Timer_ISR);
    
    while(1)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
