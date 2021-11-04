
#define STUART_TEST


#include <stdbool.h> // booleans, i.e. true and false
#include <stdio.h>   // sprintf() function
#include <stdlib.h>  // srand() and random() functions

#include "ece198.h"

int main(void)
{
    HAL_Init(); // initialize the Hardware Abstraction Layer

    // Peripherals (including GPIOs) are disabled by default to save power, so we
    // use the Reset and Clock Control registers to enable the GPIO peripherals that we're using.

    __HAL_RCC_GPIOA_CLK_ENABLE(); // enable port A (for the on-board LED, for example)
    __HAL_RCC_GPIOB_CLK_ENABLE(); // enable port B (for the rotary encoder inputs, for example)
    __HAL_RCC_GPIOC_CLK_ENABLE(); // enable port C (for the on-board blue pushbutton, for example)

    // initialize the pins to be input, output, alternate function, etc...

    InitializePin(GPIOA, GPIO_PIN_5, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // on-board LED

    // note: the on-board pushbutton is fine with the default values (no internal pull-up resistor
    // is required, since there's one on the board)

    // set up for serial communication to the host computer
    // (anything we write to the serial port will appear in the terminal (i.e. serial monitor) in VSCode)

    SerialSetup(9600);

    // as mentioned above, only one of the following code sections will be used
    // (depending on which of the #define statements at the top of this file has been uncommented)

#ifdef STUART_TEST
uint32_t my_time = 0;
uint32_t bpm = 0;
uint32_t bpm_2 = 0;
uint32_t enter_time = 0;
uint32_t i = 0;
InitializePin(GPIOA, GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_MODE_OUTPUT_PP, GPIO_NOPULL, 0);  // initialize i LED output pins


const uint32_t blink_time = 50; //blink time(ms)
const int margin_of_error = 100; //margin of error(ms)
bool pressed = false;
bool failed = false;
char buff[200];
while (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)){

};
while (!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)); //start the game after first click

sprintf(buff, "Try to press the BLUE button to match the [[7TH]] BEAT! (These are test lines) \r\n");
    SerialPuts(buff);

while(true){
    bool pressed_in_a_round = false;
    uint32_t seed = HAL_GetTick();
    bpm = seed*random()%180;
    while(bpm<100){
    bpm = seed*random()%180;
    }                   //get random BPM 100-180.
    bpm_2 = 60000/bpm;//convert to (ms).


    enter_time = HAL_GetTick();

    sprintf(buff, "BPM: %lu, %lu ms per beat, Round %lu.\r\n", bpm, bpm_2,i+1);
    SerialPuts(buff);

    

    while(true){


        if(!HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)){
            pressed = true;
        }
        if(HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)&&pressed == true){
            pressed_in_a_round = true;
            pressed = false; //Activated when released 
            int my_error = my_time - 6*bpm_2; //Calculation of error
            if(-margin_of_error < my_error && my_error < margin_of_error){
                char result[200];
                if(my_error > 0){
                    sprintf(result, "Success! Your hit is %dms late.\r\n", my_error);
                }else{
                    sprintf(result, "Success! Your hit is %dms early.\r\n", -my_error);
                }
                SerialPuts(result);
            }else{
                char result[200];
                sprintf(result, "Failed! The error is %dms.\r\n", my_error);
                SerialPuts(result);
                failed = true;
                break;
            }

            
        }  

         my_time= HAL_GetTick()-enter_time; //Continuously upgrading time after the game starts
        
        if(my_time%bpm_2<blink_time){
            if(i == 0){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true);
            }
            if(i == 1){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
            }
            if(i == 2){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
            }
            if(i == 3){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, true);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, true);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, true);
            }
            
            
        }else{
            if(i == 0){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false);
            }
            if(i == 1){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
            }
            if(i == 2){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
            }
            if(i == 3){
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false);
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
            }
            
        }
        
        if(failed){
            break;
        }
        if(my_time == 8*bpm_2){
            if(!pressed_in_a_round){
                failed = true;
                
            }
            break;
            
        }
    }
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, false);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, false);
    i++;
    if(failed){
        break;
    }

    if(i==4){
        sprintf(buff, "Congratulations! You finished all 4 rounds!\r\n");
    SerialPuts(buff);
        break; //Green light 3 times
    }
}



if(failed){
    for(int j = 0;j<6;j++){
        HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_5);
        HAL_Delay(150);
    }
    
}else{
    for(int j = 0;j<6;j++){
    HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_7);
    HAL_Delay(150);
    }
}

//Good Job, Stuart!

//np lol
#endif
    return 0;
}

void SysTick_Handler(void)
{
    HAL_IncTick();
}
