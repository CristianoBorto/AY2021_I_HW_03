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
#include "MyISR.h"

uint8 byte_number;
uint8 control_timer;
extern uint8 exit_flag;
extern uint8 Change_LEDs; 
extern Color c;
Color black = {0,0,0};
Color red = {255,0,0};

void start_peripherls()
{
    PWM_B_Start();
    PWM_RG_Start();
    UART_Start();
    UART_PutString("Insert '0xA0' or '160' to start or 'v' for info\r\n");
}

void start_ISR()
{
    CyGlobalIntEnable; 
    ISR_UART_StartEx(Custom_UART_RX_ISR);
    ISR_Timer_StartEx(Custom_Timer_ISR); 
}

void error(uint8 type)
{
    LED_WriteColor (black);
    CyDelay(50);
    LED_WriteColor (red);
    switch(type)
    {
        case 0:
            UART_PutString("Error, please enter right values\r\n");
            break;
        case 1:
            UART_PutString("Error, timeout\r\n");
            break;
    }
    
    CyDelay(50); //questo tempo permette un lempeggiio percepibile senza creare problemi se si spamma una lettera
    // reimposta config in memoria
    LED_WriteColor (c);
    Confirm_LED_Write(0);
    UART_ClearRxBuffer();
    byte_number=0;
}

void LED_WriteColor (Color c)
{
    PWM_RG_WriteCompare1(c.red_value);
    PWM_RG_WriteCompare2(c.green_value);
    PWM_B_WriteCompare(c.blue_value);
    Change_LEDs=0;
}

void v_response(void)
{
    UART_PutString("RGB LED Program $$$\r\n");
    byte_number=0;
    UART_ClearRxBuffer(); 
}

void correct_tail(void)
{
    UART_PutString("Thanks for submitting your request!\r\n");
    byte_number=0;
    stop_Timer();
    exit_flag=1;
    Change_LEDs=1;   
}

void stop_Timer(void)
{
    Timer_Stop();
    control_timer=0;  
}

void reset_Timer(void)
{
    Timer_Init(); //ri-inizializzo il timer
    control_timer=0; //azzero contatore 
}
/* [] END OF FILE */
