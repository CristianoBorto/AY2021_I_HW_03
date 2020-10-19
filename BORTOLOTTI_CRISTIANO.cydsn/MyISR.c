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

//global flag statement
extern uint8 control_timer;
extern uint8 byte_number;

CY_ISR(Custom_UART_RX_ISR) //UART ISR
{
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY) //control over UART receiver line to verify the presence of a new byte
    {
        byte_number++; //flag increment
    }
}

CY_ISR(Custom_Timer_ISR) //Timer ISR
{
    control_timer++; //flag increment
    Timer_ReadStatusRegister(); //it sets down interrupt line in order to "exit"
}

/* [] END OF FILE */
