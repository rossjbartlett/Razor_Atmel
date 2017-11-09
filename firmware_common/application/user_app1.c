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

  LedOff(WHITE);
  LedOff(PURPLE);
  LedOff(BLUE);
  LedOff(CYAN);
  LedOff(GREEN);
  LedOff(YELLOW);
  LedOff(ORANGE);
  LedOff(RED);
  
  LedOff(LCD_GREEN);
  LedOff(LCD_BLUE); // LCD is red to start 
  
 
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
bool check(u32 input[],  u32 password[], u16 passwordLength);

bool check(u32 input[], u32 password[], u16 passwordLength)
{
  for (int i = 0; i < passwordLength; i++)
    {
      if (input[i] != password[i]) return FALSE;
    }
  return TRUE;
}

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  /* Program: Password with buttons. 
              Flash Red LED if entered wrong.
              Blink Green LED if right.
  */
  
  
    u32 password[] = {BUTTON0,BUTTON1,BUTTON2,BUTTON1};
   u16 passwordLength = 4;
  
   static u32 input[]={-1,-1,-1,-1};
  static u16 u16passwordIndex=0;
  
  static bool rightpw=FALSE;
  static bool wrongpw=FALSE;
  
  if(WasButtonPressed(BUTTON0))
  {
    ButtonAcknowledge(BUTTON0);
    input[u16passwordIndex] = BUTTON0;
    u16passwordIndex++;
  }
  
   if(WasButtonPressed(BUTTON1))
  {
    ButtonAcknowledge(BUTTON1);
    input[u16passwordIndex] = BUTTON1;
    u16passwordIndex++;
  }
  
   if(WasButtonPressed(BUTTON2))
  {
    ButtonAcknowledge(BUTTON2);
    input[u16passwordIndex] = BUTTON2;
    u16passwordIndex++;
  }
  
  
  if(u16passwordIndex>10) //if entered >10 buttons reset
  {
    LedBlink(RED,LED_2HZ);
    u16passwordIndex=0;
    
  }
  
  if(WasButtonPressed(BUTTON3)) // check entry
  {
    ButtonAcknowledge(BUTTON3);
    u16passwordIndex=0;

    if(check(input,password,passwordLength))
    {
      LedBlink(GREEN,LED_2HZ); //right password entered
      LedOff(LCD_RED);
      LedOff(RED);
      LedOn(LCD_GREEN);
    }
    else // wrong password entered
    {
      LedBlink(RED,LED_2HZ);
      for (int i = 0; i < passwordLength; i++)
      {
        input[i]=-1; // clear input array 
      }
    }
      
  }
  
  
  
  //right password entered: blink green for 2sec, then reset
  if (rightpw)
  {
    //for 2 seconds...
      LedBlink(GREEN,LED_2HZ); //right password entered
      LedOff(LCD_RED);
      LedOff(RED);
      LedOn(LCD_GREEN);
      
     //then turn all lights off, reset
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
