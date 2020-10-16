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
#include "MyFunction.h"

#define timeout 10 //definition of the available interval to submit values

uint8 control_timer=0;
uint8 byte_number=0;
uint8 Change_LEDs=0;
int received;
uint8 Red_Value;
uint8 Green_Value;
uint8 Blue_Value;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    ISR_UART_StartEx(Custom_UART_RX_ISR);
    ISR_Timer_StartEx(Custom_Timer_ISR);
    
    UART_Start();
    PWM_B_Start();
    PWM_RG_Start();
    UART_PutString("Start\r\n");
    
    while(1)
    {
        if(byte_number==1){
            received = UART_ReadRxData();
            switch(received) 
            {
                case 'v':
                    UART_PutString("RGB LED Program $$$\r\n");
                    byte_number=0;
                    UART_ClearRxBuffer();
                    break;
                case 0xA0:
                    Change_LEDs=0;
                    control_timer=0;
                    UART_PutString("Insert Red value:\r\n");
                    Timer_Start();
                    UART_ClearRxBuffer();
                    while(control_timer<timeout && Change_LEDs==0)
                    {
                        if(byte_number==2)
                        {
                            received = UART_ReadRxData();
                            UART_ClearRxBuffer();
                            UART_PutString("Insert Green value:\r\n");
                            Red_Value=received; //salvo rosso
                            Timer_Init(); //ri-inizializzo il timer
                            control_timer=0; //azzero contatore
                            while(control_timer<timeout && Change_LEDs==0) //comincio a contare 5s
                                {
                                    if(byte_number==3) //è arrivato il terzo codice
                                    {
                                        received = UART_ReadRxData();
                                        UART_ClearRxBuffer();
                                        UART_PutString("Insert Blue value:\r\n");
                                        Green_Value=received;
                                        Timer_Init(); //ri-inizializzo il timer
                                        control_timer=0; //azzero contatore
                                        while(control_timer<timeout && Change_LEDs==0)
                                        {
                                            if(byte_number==4)
                                            {
                                                received = UART_ReadRxData();
                                                UART_ClearRxBuffer();
                                                UART_PutString("Insert '0xC0' or 192 to confirm\r\n");
                                                Blue_Value=received;
                                                Timer_Init(); //ri-inizializzo il timer
                                                control_timer=0;
                                                while(control_timer<timeout && Change_LEDs==0)
                                                {
                                                    if(byte_number==5)
                                                    {
                                                        received = UART_ReadRxData();
                                                        UART_ClearRxBuffer();
                                                        if(received==0xC0)
                                                        {
                                                            UART_PutString("Thanks for submitting your request!\r\n");
                                                            byte_number=0;
                                                            Timer_Stop();
                                                            control_timer=0;
                                                            Change_LEDs=1;
                                                            break;
                                                        }
                                                        else
                                                        {
                                                            error(0);
                                                            Timer_Stop();
                                                            byte_number=0;
                                                            UART_ClearRxBuffer();
                                                            Change_LEDs=1;
                                                            control_timer=5;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }  
                        }
                    }
                    if(Change_LEDs==0)
                    {
                        byte_number=0;
                        error(1);
                        Timer_Stop();
                        control_timer=0;
                        break;
                    }
                    break;
                    
                default:
                    error(0);
                    byte_number=0;
                    UART_ClearRxBuffer();
                    break;
            
            }
        }
      
        if(Change_LEDs==1)
        {
            PWM_RG_WriteCompare1(Red_Value);
            PWM_RG_WriteCompare2(Green_Value);
            PWM_B_WriteCompare(Blue_Value);
            Change_LEDs=0;
        }
        
    }
}

/* [] END OF FILE */
