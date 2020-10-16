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
#include "stdio.h"

extern uint8 control_timer;
extern uint8 byte_number;
char message[20]={"\0"};


CY_ISR(Custom_UART_RX_ISR)
{
    
    if (UART_ReadRxStatus() == UART_RX_STS_FIFO_NOTEMPTY)
    {
        byte_number++;
//        switch(byte_number)
//        {
//            case 0:
//                byte_number=1;
//                break;
//            case 1:
//                byte_number=2;
//                break;
//            case 2:
//                byte_number=3;
//                break;
//            case 3:
//                byte_number=4;
//                break;
//            case 4:
//                byte_number=5;
//                break;
//        }
        
        
        
//        char received=UART_ReadRxData();
//        sprintf(message, "Received: %c\r\n", received);
//        UART_PutString(message);
//        Timer_Start();
    }
}

CY_ISR(Custom_Timer_ISR)
{
    control_timer++;
    Timer_ReadStatusRegister();
}



/* [] END OF FILE */
