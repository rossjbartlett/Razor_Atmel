/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
 
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

  //Binary Counter (multi-bit)
  
  
     /* All discrete LEDs to off */
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
  /* Backlight to white (R+G+B = W). */  
  //if not doing white, must turn off all first bc they default on
  LedOff(LCD_RED);
  LedOff(LCD_GREEN);
  LedOff(LCD_BLUE);

  //LedOn(LCD_RED);
  //LedOn(LCD_GREEN);
  LedOn(LCD_BLUE);
  
  
  
} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
    static u16 u16BlinkCount = 0;
    static u8 u8Counter = 0;
    const u16 u16bitAmount = 8; // x-bit counter.
    u32 u32highestNum =1; //ex. 4-bit's highestNum is 15
    
    //pow() function to set highest num = 2^bitAmount -1
    for(int i=0 ; i<u16bitAmount ; i++)
    {
      u32highestNum*=2;
    }
    u32highestNum-=1;
    
    
    
    u16BlinkCount++;
    if(u16BlinkCount == 500)//change every .5s
    {
      u16BlinkCount = 0;
      
      /* Update the counter and roll at 16 */
      u8Counter++;
      if(u8Counter > u32highestNum)//ex. binary count up to 15 (4bit)
      {
        u8Counter = 0;
      }
      
    }
  
     /* Parse the current count to set the LEDs.  
      RED is bit 0, ORANGE is bit 1, 
      YELLOW is bit 2, GREEN is bit 3, CYAN,BLUE,PURPLE,WHITE. */
    
    if(u8Counter & 0x01)
    {
      LedOn(RED);
    }
    else
    {
      LedOff(RED);
    }

    if(u8Counter & 0x02)
    {
      LedOn(ORANGE);
    }
    else
    {
      LedOff(ORANGE);
    }

    if(u8Counter & 0x04)
    {
      LedOn(YELLOW);
    }
    else
    {
      LedOff(YELLOW);
    }

    if(u8Counter & 0x08)
    {
      LedOn(GREEN);
    }
    else
    {
      LedOff(GREEN);
    }
    //more
    if(u8Counter & 0x10) // 0x10 in hex= 16 in decimal 
    {
      LedOn(CYAN);
    }
    else
    {
      LedOff(CYAN);
    }

    if(u8Counter & 0x20) // 32 decimal
    {
      LedOn(BLUE);
    }
    else
    {
      LedOff(BLUE);
    }

    if(u8Counter & 0x40) //64 decimal
    {
      LedOn(PURPLE);
    }
    else
    {
      LedOff(PURPLE);
    }

    if(u8Counter & 0x80) //128 decimal
    {
      LedOn(WHITE);
    }
    else
    {
      LedOff(WHITE);
    }
    
} /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
