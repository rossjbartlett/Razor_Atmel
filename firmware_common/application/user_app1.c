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

 static u32 password[MAX_PW_LENGTH] = {BUTTON0,BUTTON1,BUTTON2,BUTTON1}; //default PW
 static u16 passwordLength = 4; //default 
  
 static u32 input[MAX_PW_LENGTH]; //input attempted PW 


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
    UserApp1_StateMachine = UserApp1SM_myIdle; // changed it to myIdle
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
  
  LedOn(LCD_GREEN);
  LedOn(LCD_BLUE); // LCD is white to start 
  LedOn(LCD_RED); 
 
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


bool check(u32 input[],u16 inputIndex)
{
  if (inputIndex!=passwordLength) return FALSE;
  for (int i = 0; i < passwordLength; i++)
    {
      if (input[i] != password[i]) return FALSE;
    }
  return TRUE;
}

void WasAnyButtonPressed(void)
{
  for (u32 i = BUTTON0 ; i<=BUTTON3 ; i++)//check if any of the buttons  pressed
  {
    if (WasButtonPressed(i))
    {
      ButtonAcknowledge(i);
      UserApp1_StateMachine = UserApp1SM_locked;
      LedOn(RED);
      LedOff(GREEN);
    }
  }
}


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/


static void UserApp1SM_myIdle(void) //////myIdle state 
{
  static u32 u32timer =0;
  u32timer++;
  
  if (IsButtonHeld(BUTTON3,1000)) //enter setPW state
  {
    UserApp1_StateMachine = UserApp1SM_setPW;
    LedBlink(RED,LED_2HZ);
    LedBlink(GREEN,LED_2HZ);
  }


  else if (u32timer>5000) //enter locked state w/ default PW
  {
    UserApp1_StateMachine = UserApp1SM_locked;
    LedOn(RED);
  }
}




static void UserApp1SM_setPW(void)    //////set password  state 
{
  u16 u16pwIndex=0;
  
  for (u32 i = BUTTON0 ; i<=BUTTON2 ; i++)//check if any of the buttons 0-2 were pressed
  {
    if (WasButtonPressed(i))
    {
      ButtonAcknowledge(i);
      if (u16pwIndex<MAX_PW_LENGTH)
      {
        password[u16pwIndex]=i;
        u16pwIndex++;
        passwordLength=u16pwIndex; //set the PW length to how many buttons u pressed
      }
      
    }
    
  }
  
  
  
  if (WasButtonPressed(BUTTON3))
  {
    ButtonAcknowledge(BUTTON3);
    UserApp1_StateMachine = UserApp1SM_locked;
    LedOn(RED);
    LedOff(GREEN);
  }
  
  
  
}


static void UserApp1SM_locked(void)//locked state
{
  static u16 u16inputIndex=0;
   for (u32 i = BUTTON0 ; i<=BUTTON2 ; i++)//check if any of the buttons 0-2 were pressed
  {
    if (WasButtonPressed(i))
    {
      ButtonAcknowledge(i);
      if (u16inputIndex<MAX_PW_LENGTH) 
      {
        input[u16inputIndex]=i;
        u16inputIndex++;
      }
      
    }
    
  }

  //should have a check for if you enter >10 buttons 
  
  
  //check answer
  if (WasButtonPressed(BUTTON3))
  {
    ButtonAcknowledge(BUTTON3);
    if (check(input,u16inputIndex)==TRUE)//pw correct
    {
        UserApp1_StateMachine = UserApp1SM_unlocked;
        LedBlink(GREEN,LED_2HZ);
        LedOff(RED);

    }
    else
    {
        UserApp1_StateMachine = UserApp1SM_wrongPW;
        LedBlink(RED,LED_2HZ);
        LedOff(GREEN);
    }
      
    
  }
  
}



static void UserApp1SM_unlocked(void)
{
  WasAnyButtonPressed();
}


static void UserApp1SM_wrongPW(void)
{
   WasAnyButtonPressed();
}















/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */
static void UserApp1SM_Idle(void)
{
  
} /* end UserApp1SM_Idle() */
    

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
