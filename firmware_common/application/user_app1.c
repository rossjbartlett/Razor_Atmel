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

  
  
  
   /* Initialize all unused LEDs to off */
  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
 
  
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
  /* Program: LEDs alternate between 2 fade patterns:
   * 1. Alternate Brightening LED, Dimming LED. Red Backlight
  *  2. Half LEDs brightening, Half LEDs dimming. Blue Backlight
  */
  
    static u16 u16BlinkCount = 0;
    static u16 u16patternTimer = 0;
    const u16 u16patternLength = 5000;//switch patterns every 5s
    
    //group 1 of LEDs start dim, brighten up
    static LedRateType brightness = 0;
    static bool goingUp = TRUE;
    //group 2 of LEDs start bright, dim down
    static LedRateType brightness2 = 20;
    static bool goingUp2 = FALSE;
    
    u16BlinkCount++;
    u16patternTimer++;
    
    if(u16BlinkCount == 40)//speed of blinking 
    {
      u16BlinkCount = 0;
      
      if (goingUp) brightness++;
      else brightness--;
      if (goingUp2) brightness2++;
      else brightness2--;
      
      if (brightness>=20) //20 steps from 0 to 100 (step=5)
      {
        goingUp=FALSE;
      }
      else if (brightness<=0)
      {
        goingUp=TRUE;
      }
      
       if (brightness2>=20) //20 steps from 0 to 100 (step=5)
      {
        goingUp2=FALSE;
      }
      else if (brightness2<=0)
      {
        goingUp2=TRUE;
      }
      
      if(u16patternTimer< u16patternLength) 
      {
        //Red Backlight
        LedOff(LCD_GREEN);
        LedOff(LCD_BLUE);
        LedOn(LCD_RED);
        // pattern1: Alternate Brightening LED, Dimming LED
        for(LedNumberType ledNum = 0; ledNum<8 ; ledNum++)
        {
         if (ledNum%2==0) LedPWM(ledNum,brightness); //even LEDs brighten
         else LedPWM(ledNum,brightness2); // odd LEDs dim
        }
      }
      else
      {
        //BLUE Backlight
        LedOff(LCD_RED);
        LedOff(LCD_GREEN);
        LedOn(LCD_BLUE);
        // pattern2: Half LEDs brightening, Half LEDs dimming
       for(LedNumberType ledNum = 0; ledNum<8 ; ledNum++)
        {
         if (ledNum<4) LedPWM(ledNum,brightness);//left LEDs brighten
         else LedPWM(ledNum,brightness2);//right LEDs dim
        }
      }
      
      if(u16patternTimer > 2*u16patternLength) u16patternTimer=0;
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
