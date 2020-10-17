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

//flag statement
uint8 control_timer = 0;
uint8 byte_number = 0;
uint8 Change_LEDs = 0;
uint8 exit_flag=0;

int received; //variabile di appoggio per salvare il byte in arrivo

Color c={0,0,0}; //color struct
Color c_partial={0,0,0};

int main(void)
{
    //initialization phase
    
    start_ISR();
    start_peripherls();
    LED_WriteColor (c);
    
    while(1)
    {
        if(byte_number==1){
            received = UART_ReadRxData();
            switch(received) 
            {
                case 'v':
                    v_response();
                    break;
                    
                case 0xA0:
                    exit_flag=0;
                    Confirm_LED_Write(1);
                    Timer_Start();
                    while(control_timer<timeout && exit_flag==0) //
                    {
                        if(byte_number==2)
                        {
                            received = UART_ReadRxData();
                            c_partial.red_value=received; //salvo rosso
                            reset_Timer();
                            Confirm_LED_Write(0);
                            while(control_timer<timeout && exit_flag==0) //comincio a contare 5s
                                {
                                    if(byte_number==3) //è arrivato il terzo codice
                                    {
                                        received = UART_ReadRxData();
                                        c_partial.green_value=received;
                                        reset_Timer();
                                        Confirm_LED_Write(1);
                                        while(control_timer<timeout && exit_flag==0)
                                        {
                                            if(byte_number==4)
                                            {
                                                received = UART_ReadRxData();
                                                c_partial.blue_value=received;
                                                reset_Timer();
                                                Confirm_LED_Write(0);
                                                while(control_timer<timeout && exit_flag==0)
                                                {
                                                    if(byte_number==5)
                                                    {
                                                        received = UART_ReadRxData();
                                                        if(received==0xC0)
                                                        {
                                                            correct_tail();
                                                            break;
                                                        }
                                                        else
                                                        {
                                                            stop_Timer();
                                                            error(0); 
                                                            exit_flag=1;
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }  
                        }
                    }
                    if(exit_flag==0)
                    {
                        error(1);
                        stop_Timer();
                        break;
                    }
                    break;
                    
                default:
                    error(0);
                    break;
            }
        }
        if(Change_LEDs==1)
        {
            c=c_partial; //update of colors
            LED_WriteColor (c);
        }
        
    }
}

/* [] END OF FILE */
