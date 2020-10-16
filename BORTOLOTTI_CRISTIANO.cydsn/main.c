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

uint8 control_timer=0;
uint8 byte_number=0;
int received;
int received2;
uint8 Red_Value;
uint8 Green_Value;

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
                    UART_PutString("Insert Red value:\r\n");
                    Timer_Start();
                    control_timer=0;
                    while(control_timer<5)
                    {
                        if(byte_number==2)
                        {
                            received2 = UART_ReadRxData();
                            if(received2>0 && received2<255) //se è giusto
                            {
                                Red_Value=received2; //salvo rosso
                                Timer_Init(); //ri-inizializzo il timer
                                control_timer=0; //azzero contatore
                                while(control_timer<5) //comincio a contare 5s
                                {
                                    if(byte_number==3) //è arrivato il terzo codice
                                    {
                                        UART_PutString("Insert Green value:\r\n");
                                        received = UART_ReadRxData(); //salvo terzo codice
                                        if(received>0 && received<255) //è giusto?
                                        {
                                            Green_Value=received; //salvo verde
                                            Debug_LED_Write(1);
                                            Timer_Stop();
                                            byte_number=0;
                                            control_timer=0;
                                            break;
                                        }
                                        else
                                        {
                                            error(0);
                                            byte_number=0;
                                            Timer_Stop();
                                            control_timer=5;
                                        }
                                    }
                                }
     
                            }
                            else //if(received<0 || received>255) //se è sbagliato
                            {
                                Debug_LED_Write(1);
                                UART_PutString("dio cane");
                                byte_number=0;
                                //Timer_Stop();
                                control_timer=6;
                                error(0);
                                break;
                                 //6 per non stampare il doppio errore
                            }
                            
                        }
                    }
                    
                    byte_number=0;
                    error(1);
                    Timer_Stop();
                    control_timer=0;
                    break;
                    
                default:
                    error(0);
                    byte_number=0;
                    UART_ClearRxBuffer();
                    break;
            
            }
        }
        
        
    }
}

/* [] END OF FILE */
