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
  
  
  
  PWMAudioSetFrequency(BUZZER1, 500);//neccessary?
  
  //puple LCD
  LedOn(LCD_RED);
  LedOff(LCD_GREEN);
  LedOn(LCD_BLUE);
  
  u8 au8SongTitle[] = "Hello ATB!";
  
  LCDCommand(LCD_CLEAR_CMD);
  LCDMessage(LINE1_START_ADDR, au8SongTitle);
  
  
  
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
  /* my song program 
  *GOT
  *USING "FN" full notes made errors because song is in 3/4. instead just make 3 quarter notes.
  */
  
  
  //right hand
  const static u16 au16NotesRight[]    = {G5, C5, D5S, F5, G5, C5, D5S, F5,G5, C5, D5S, F5,G5, C5, D5S, F5,D5,D5,D5,D5,D5,D5,D5,D5,D5,D5,D5,D5,F5,F5,F5,A5S,A5S,A5S,F5,F5,F5,A5S,A5S,A5S,D5S,D5,G6, C6, D6S, F6, G6, C6, D6S, F6,G6, C6, D6S, F6,G6, C6, D6S, F6}; 
  const static u16 au16DurationRight[] = {QN, QN,   EN, EN, QN, QN, EN,  EN,QN, QN, EN, EN, QN, QN, EN, EN, QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN, QN, QN, QN,QN,QN,QN,  QN,QN, EN , EN,QN, QN, EN,  EN,  QN,QN, EN,  EN, QN,QN, EN,  EN, QN,QN, EN,  EN};
  const static u16 au16NoteTypeRight[] = {RT, RT,   RT, RT, RT, RT,  RT, RT,RT, RT, RT, RT, RT, RT, RT, RT, HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT,HT, HT, HT, HT,HT,HT,HT,  HT,HT, RT, RT, RT, RT,  RT,  RT, RT, RT, RT, RT, RT, RT, RT, RT, RT, RT, RT, RT};
  static u8 u8IndexRight = 0;
  static u32 u32RightTimer = 0;
  static u16 u16CurrentDurationRight = 0;
  static u16 u16NoteSilentDurationRight = 0;
  static bool bNoteActiveNextRight = TRUE;
  //left hand
  const static u16 au16NotesLeft[]    = {G4,G4,G4,C4,C4,C4,G4,G4,G4,C4,C4,C4,D4, G3, A3S, C4,D4, G3, A3S, C4,D4, G3, A3S, C4,D4, G3, A3S, C4,F4,F4,F4,A3S,A3S,D4,D4S,F4,F4,F4,A3S,A3S,A3S,D4S,D4,C4,C4,C4,C4,C4,C4,C4,C4,C4,C4,C4,C4};
  const static u16 au16DurationLeft[] = {QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN,QN ,QN, EN,  EN,QN ,QN, EN,  EN,QN ,QN, EN,  EN,QN ,QN, EN, EN, QN,QN,QN, QN,QN,  EN,EN,QN,QN,QN,QN, QN, QN, EN,EN,QN, QN, QN,QN,QN,QN,QN,QN,QN,QN,QN,QN};    
  const  static u16 au16NoteTypeLeft[] = {HT,HT,HT, HT,HT,HT,HT,HT,HT,HT,HT,HT,RT, RT, RT,  RT,RT, RT, RT,  RT, RT, RT, RT, RT,RT, RT, RT, RT, HT,HT,HT, HT,RT, RT,RT, HT,HT,HT, HT,HT,HT,  RT,RT,HT, HT, HT,HT,HT,HT,HT,HT,HT,HT,HT,HT};
  static u16 u8IndexLeft = 0; //made this u16 instead of u8. shouldnt matter tho
  static u32 u32LeftTimer = 0;
  static u16 u16CurrentDurationLeft = 0;
  static u16 u16NoteSilentDurationLeft = 0;
  static bool bNoteActiveNextLeft = TRUE;
  
  u8 u8CurrentIndex;
  
#if 1
  //RIGHT HAND 
  if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight))
  {
    u32RightTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexRight;
    if (u8CurrentIndex ==0) 
    {
      DebugPrintf("starting RIGHT");
    }
    /* Set up to play current note */
    if(bNoteActiveNextRight)
    {
      if(au16NoteTypeRight[u8CurrentIndex] == RT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationRight = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextRight = FALSE;
      } /* end RT case */
      
      else if(au16NoteTypeRight[u8CurrentIndex] == ST)
      {
        u16CurrentDurationRight = STACCATO_NOTE_TIME;
        u16NoteSilentDurationRight = au16DurationRight[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextRight = FALSE;
      } /* end ST case */
      
      else if(au16NoteTypeRight[u8CurrentIndex] == HT)
      {
        u16CurrentDurationRight = au16DurationRight[u8CurrentIndex];
        u16NoteSilentDurationRight = 0;
        bNoteActiveNextRight = TRUE;
        
        u8IndexRight++;
        if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
        {
          u8IndexRight = 0;
        }
      } /* end HT case */
      
      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesRight[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER1, au16NotesRight[u8CurrentIndex]);
        PWMAudioOn(BUZZER1);
        /* LED control */
        
        LedOff(GREEN);//turn off first to make only 1 bright at a time for each hand
        LedOff(YELLOW);
        LedOff(ORANGE);
        LedOff(RED);
        switch(au16NotesRight[u8CurrentIndex])
        {
        case C6:
        case C5:
          LedOn(GREEN);
          break;
          
        case D6S:
        case D5S:
          LedOn(YELLOW);
          break;
          
        case F6:
        case F5:
          LedOn(ORANGE);
          break;
          
        case G6:
        case G5:
        case A5S:
          LedOn(RED);
          break;
          
        default:
          break;
          
        } /* end switch */
      }
      else
      {                
        PWMAudioOff(BUZZER1);
        
        LedOff(GREEN);
        LedOff(YELLOW);
        LedOff(ORANGE);
        LedOff(RED);
      }
    } /* end if(bNoteActiveNextRight) */
    else
    {
      /* No active note */
      PWMAudioOff(BUZZER1);
      u32RightTimer = G_u32SystemTime1ms;
      u16CurrentDurationRight = u16NoteSilentDurationRight;
      bNoteActiveNextRight = TRUE;
      
      
      LedOff(GREEN);
      LedOff(YELLOW);
      LedOff(ORANGE);
      LedOff(RED);
      
      u8IndexRight++;
      if(u8IndexRight == sizeof(au16NotesRight) / sizeof(u16) )
      {
        u8IndexRight = 0;
      }
    } /* end else if(bNoteActiveNextRight) */
  } /* end if(IsTimeUp(&u32RightTimer, (u32)u16CurrentDurationRight)) */
#endif
  
  
#if 1
  /* Left Hand */
  if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft))
  {
    u32LeftTimer = G_u32SystemTime1ms;
    u8CurrentIndex = u8IndexLeft;
    if (u8CurrentIndex ==0) 
    {
      DebugPrintf("starting LEFT");
    }
    /* Set up to play current note */
    if(bNoteActiveNextLeft)
    {
      if(au16NoteTypeLeft[u8CurrentIndex] == RT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex] - REGULAR_NOTE_ADJUSTMENT;
        u16NoteSilentDurationLeft = REGULAR_NOTE_ADJUSTMENT;
        bNoteActiveNextLeft = FALSE;
      }
      
      else if(au16NoteTypeLeft[u8CurrentIndex] == ST)
      {
        u16CurrentDurationLeft = STACCATO_NOTE_TIME;
        u16NoteSilentDurationLeft = au16DurationLeft[u8CurrentIndex] - STACCATO_NOTE_TIME;
        bNoteActiveNextLeft = FALSE;
      }
      
      else if(au16NoteTypeLeft[u8CurrentIndex] == HT)
      {
        u16CurrentDurationLeft = au16DurationLeft[u8CurrentIndex];
        u16NoteSilentDurationLeft = 0;
        bNoteActiveNextLeft = TRUE;
        
        u8IndexLeft++;
        if( u8IndexLeft>40)
        {
          u8IndexLeft=u8IndexLeft;
        }
        if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
        {
          u8IndexLeft = 0;
        }
      }
      
      /* Set the buzzer frequency for the note (handle NO special case) */
      if(au16NotesLeft[u8CurrentIndex] != NO)
      {
        PWMAudioSetFrequency(BUZZER2, au16NotesLeft[u8CurrentIndex]);
        PWMAudioOn(BUZZER2);
        /* LED control */
        
        LedOff(WHITE); //turn off first to make only 1 bright at a time for each hand
        LedOff(PURPLE);
        LedOff(BLUE);
        LedOff(CYAN);
        switch(au16NotesLeft[u8CurrentIndex])
        {
        case G3:
          LedOn(WHITE);
          break;
          
        case A3S:
          LedOn(PURPLE);
          break;
          
        case C4:
          LedOn(BLUE);
          break;
          
        case D4:
        case G4:
          LedOn(CYAN);
          break;
          
        default:
          break;
          
        } /* end switch */
      }
      else
      {                
        PWMAudioOff(BUZZER2);
        LedOff(WHITE);
        LedOff(PURPLE);
        LedOff(BLUE);
        LedOff(CYAN);
        
      }
    }
    else
    {
      PWMAudioOff(BUZZER2);
      u32LeftTimer = G_u32SystemTime1ms;
      u16CurrentDurationLeft = u16NoteSilentDurationLeft;
      bNoteActiveNextLeft = TRUE;
      
      LedOff(WHITE);
      LedOff(PURPLE);
      LedOff(BLUE);
      LedOff(CYAN);
      
      u8IndexLeft++;
      if( u8IndexLeft>40)
      {
        u8IndexLeft=u8IndexLeft;
      }
      if(u8IndexLeft == sizeof(au16NotesLeft) / sizeof(u16) )
      {
        u8IndexLeft = 0;
      }
    } /* end else if(bNoteActiveNextLeft) */
  } /* end if(IsTimeUp(&u32LeftTimer, (u32)u16CurrentDurationLeft)) */
#endif
  
} /* end UserApp1SM_Idle() */


/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
