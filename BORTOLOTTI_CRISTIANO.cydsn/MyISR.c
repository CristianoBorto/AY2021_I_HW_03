/* ========================================
 *
 Assignment 03
 * Editor: Cristiano Bortolotti
 * File: MyISR.c
 * Date: 15/10/2020 - 20/10/2020
 *
 * ========================================
*/

#include "MyISR.h"
#include "UART.h"
#include "stdio.h"

CY_ISR(Custom_UART_RX_ISR)
{
    
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        
    }
}

CY_ISR(Custom_Timer_ISR)
{
    
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        
    }
}



/* [] END OF FILE */
