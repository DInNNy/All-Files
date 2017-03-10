/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "stm32l476xx.h"
#include <string.h>
#include <stdio.h>

#define POINT 96 // jumpts to the point assigned in the receipe
#define MOV 32
#define WAIT 64
#define LOOP 128
#define END_LOOP 160
#define RECIPE_END 0


uint8_t recipecode1[] = {
	
		MOV+0,
		MOV+5,
		MOV+0,
		MOV+3,
		LOOP+0,
		MOV+1,
		MOV+4,
		END_LOOP,
		MOV+0,
		MOV+2,
		WAIT+0,
		MOV+3,
		WAIT+0,
		MOV+2,
		MOV+3,
		WAIT+31,
		WAIT+31,
		WAIT+31,
		MOV+4,
		MOV+4,
		MOV+2,
                MOV+10
	};
uint8_t recipecode2[] = {
		MOV+2,
		MOV+1,
		MOV+5,
		MOV+3,
		LOOP+3,
		MOV+1,
		MOV+4,
		POINT+3
	};



struct state_machine
{
	uint32_t code_counter;
        uint32_t wait_counter;
	uint32_t code_pause;
        uint32_t code_finished;
	uint32_t code_error;
	uint32_t loop;
	uint32_t loog_begin;	
	uint32_t unexecuted_loop;
        uint32_t fault; 
	
	uint8_t * recipe_pointer;
	void((uint8_t *motor_position);
};

struct state_machine s1_state_machine;    //recipe state for motor 1 and 2
struct state_machine s2_state_machine;	


        
        struct state_machine     s1_state;    //code state for the servo motor 1 and 2 
        struct state_machine     s2_state;	


void init_state_machine(struct state_machine* state_machine, uint8_t * recipe_to_load, void((uint8_t *motor_position))
	state_machine ->code_pause = 1;
	state_machine->code_error = 0;
	state_machine->code_finished = 0;
	state_machine->code_counter = 0;
	state_machine->wait_counter = 0;
	state_machine->loop = 0;
	state_machine->loog_begin = 0;
	state_machine->lunexecuted_loop = 0;
	state_machine->recipe_pointer = recipe_to_load;
	state_machine->motor_position = motor_position;



        
        
        
     
              
        
        void step(struct State_machine* x)
        
        uint8_t opcode;                // first 3 bits  
	uint8_t parameter;             // last 5 bits 
        uint8_t bit_holder              // character to hold the bits
        

        
        {
            if(x-> code_counter != 0)                         // delay is executed here and added later in program 
            {
                x-> code_counter -- ; 
            }
            
            else(x-> !code_pause && x-> ! code_finished && x-> ! code_error)
                    
            {
              bit_holder= x-> recipe_pointer[x-> code_counter];
              x -> code_counter ++;
              opcode = bit_holder & 0xE0;           // opcode gets first 3 bits from bit holder
              parameter = bit_holder & 0x1F;       // parameter gets last 5 bits from bit holder
            }
            
            
            
            switch (opcode)
            {
                case MOV:
                    if(paramter > 5)
                    {
                        x-> motor_position(paramter);
                        x-> code_counter = 6;   // delay is added here
                    }
                    break;
                    
                
                case WAIT: 
                
                    x-> wait_counter = paramter ; 
                    break;
                
                    
                case LOOP: 
                    
                    if( x-> loop)         // loop_value is 0 ; no nested loop
                    {
                      x -> fault = 1 ; 
                      break; 
                    }
                    
                    x-> loop = 1; 
                    x-> loop_begin = x-> code_counter; 
                    x->unexecuted_loop = parameter;
                    break; 
                    
                case LOOP_END:
                    
                    if(!x-> loop_value)
                    {
                        x-> error =1 ; 
                        break; 
                    }
                    if ( x-> unexecuted_loop !0)
                    {
                        x-> code_counter = rs -> loop_begin; 
                        x-> unexecuted_loop -- ; 
                    }
                    
                    break;
                    
                case RECIPE_END:
                    
                    x-> code_finished =1; 
                    break; 
            }       
            
        }
        
        
        
        /* LED display  */
        
        
        
   
       /* struct state_machine     s1_state;    //code state for the servo motor 1 and 2 
        struct state_machine     s2_state; */
        
        
        /* This part is for LED control*/
        
        Void ledcontrol(void)
                
        step(&s1_state_machine);
        step(&s2_state_machine);
        
        
        Red_LED_Off(); // initially red led is off
        
        	if(s1_recipe_state.code_error || s2_recipe_state.code_error)
                {
		Red_LED_On();
                Green_LED_Off();
                } 
	
	Green_LED_Off(); //green is off until it is called 
        
	if((!s1_recipe_state.code_paused && !s1_recipe_state.code_finished && !s1_recipe_state.code_error) 
	|| (!s2_recipe_state.code_paused && !s2_recipe_state.code_finished && !s2_recipe_state.code_error))
        {
		Green_LED_On();
                Red_LED_Off();
	}

