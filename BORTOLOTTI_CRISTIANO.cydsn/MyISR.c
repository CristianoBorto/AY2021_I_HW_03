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
#include "Timer.h"

extern uint8 control_timer;
extern uint8 byte_number;

CY_ISR(Custom_UART_RX_ISR)
{
    
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        byte_number++;
    }
}

CY_ISR(Custom_Timer_ISR)
{
    control_timer++;
    Timer_ReadStatusRegister();
}

/* [] END OF FILE */
