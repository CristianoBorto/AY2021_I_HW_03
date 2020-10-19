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

#define timeout 5 //definition of the available interval to submit values

//flag statement
uint8 control_timer = 0; //timer counter
uint8 byte_number = 0; //flag of received bytes
uint8 Change_LEDs = 0; //new colors code correctly received
uint8 exit_flag  =0; //it allows to exit from the internal condition with a correct and wrong tail

int received; //support variable to save incoming byte

//color struct
Color c = {0,0,0}; //it memorizes the correct color
Color c_partial = {0,0,0}; //it saves partial new color codes. It is required in order to do not overwrite the stored colors when an
                           //error occurs

int main(void)
{
    //initialization phase
    start_ISR();
    start_peripherls();
    
    while(1)
    {
        if(byte_number == 1) //condition to verify wheter the first byte is arrived
        {
            received = UART_ReadRxData(); //save incoming byte
            switch(received) //3 possible case: 'v', 'A0' or any other value(error condition)
            {
                case 'v':
                    v_response(); //print the required string and reset the system
                    break;
                    
                case 0xA0: //correct detection of the start header code
                    exit_flag = 0;
                    Confirm_LED_Write(1);
                    Timer_Start(); //start of the timer used to count 5s
                    while(control_timer < timeout && exit_flag == 0) // controll timeout
                    {
                        if(byte_number==2) //second byte arrived
                        {
                            received = UART_ReadRxData(); //read value from UART
                            c_partial.red_value=received; //save red
                            reset_Timer();
                            Confirm_LED_Write(0);
                            while(control_timer<timeout && exit_flag==0) // controll timeout
                                {
                                    if(byte_number==3) //third byte arrived
                                    {
                                        received = UART_ReadRxData(); //read value from UART
                                        c_partial.green_value=received; //save green
                                        reset_Timer();
                                        Confirm_LED_Write(1);
                                        while(control_timer<timeout && exit_flag==0) // controll timeout
                                        {
                                            if(byte_number==4) //fourth byte arrived
                                            {
                                                received = UART_ReadRxData(); //read value from UART
                                                c_partial.blue_value=received; //save blue
                                                reset_Timer();
                                                Confirm_LED_Write(0);
                                                while(control_timer<timeout && exit_flag==0) // controll timeout
                                                {
                                                    if(byte_number==5) //fifth byte arrived
                                                    {
                                                        received = UART_ReadRxData(); //read value from UART
                                                        if(received==0xC0)
                                                        {
                                                            correct_tail();
                                                        }
                                                        else
                                                        { // wrong tail
                                                            stop_Timer();
                                                            error(0); 
                                                            exit_flag=1;
                                                        }
                                                    } //end if(byte_number==5)
                                                } //end fourth timeout
                                            } // end if(byte_number==4)
                                        } //end third timeout
                                    } //end if(byte_number==3)
                                }  //end second timeout
                        } // end if(byte_number==2)
                    } //end first timeout
                    if(exit_flag==0)
                    {
                        error(1);
                        stop_Timer();
                        break;
                    }
                    break; //end of the case A0
                    
                default:
                    error(0);
                    break;
            } //end switch
        } //end if(byte_number == 1)
        
        if(Change_LEDs==1)
        {
            c=c_partial; //update of colors
            LED_WriteColor (c);
        }
        
    } //end while(1)
} //end main

/* [] END OF FILE */
